#include "Profiler.h"

Profiler::Profiler(int input_kmerlen, const char *seq, kmerMap *input_kmap)
{
	kmerlen = input_kmerlen;
	kmap = input_kmap;
	tempKmer = (char*)malloc(sizeof(char) * (kmerlen + 1));
	memset(tempKmer, '\0', sizeof(char) * (kmerlen + 1));
	profile = (double*)malloc(sizeof(double) * kmap->getEntryNum());//entryNum es el tamano del vector de la secuencia
	memset(profile, '\0', sizeof(double) * kmap->getEntryNum());
	computeProfile(seq);
	total_weight = 1;
}

Profiler::~Profiler()
{
	free(tempKmer);
	free(profile);
}

double* Profiler::getProfile()
{
	return(profile);
}

float Profiler::getPercentN()
{
	return(percent_N);
}

float Profiler::getTargetProfile(char *ch)
{
	return((float)(profile[kmap->getMapping(ch)]));
}

void Profiler::reset()
{
	total_weight = 0;
	memset(profile, '\0', sizeof(double) * kmap->getEntryNum());
}

//parte de get profile
void Profiler::addProfile(Profiler *pf, long double weight)
{
	int i;
	for (i = 0; i < kmap->getEntryNum(); i++)
	{
		profile[i] = profile[i] + (pf->profile[i] * (double)weight);
	}
	total_weight = total_weight + weight;;
}

void Profiler::calcProfile()
{
	int i;
	if (total_weight == 0)
	{
		printf("Total weight is 0! Set all profiles to 0. Nan encountered?\n");
	}
	for (i = 0; i < kmap->getEntryNum(); i++)
	{
		if (total_weight == 0)
		{
			profile[i] = 0;
		}
		else
		{
			profile[i] = profile[i] / (double)total_weight;
		}
	}
	total_weight = 1;
}


//aqui calcula el perfil (el vector para cada read)
/*
profile[i] =
	(número de veces que aparece el k-mer i en la secuencia) / (total de k-mers en la secuencia)
*/
void Profiler::computeProfile(const char *seq)
{
	int len, i, j, N, total;
	N = 0;
	total = 0;
	len = strlen(seq);
	for (i = 0; i < len - kmerlen + 1; i++)
	{
		//nota: N es cuando es una base desconocida (no se pasó bien al archivo)
		if (seq[i] == 'N')
		{
			N++;
		}
		memcpy(tempKmer, seq + i, kmerlen);
		j = kmap->getMapping(tempKmer);
		if (j != -1)
		{
			total++;
			profile[j]++;
			//j = kmap->getReverseMapping(tempKmer);
			//total++;
			//profile[j]++;
		}
	}
	j = kmap->getEntryNum();
	percent_N = (float)N / (float)(len - kmerlen + 1);
	if (percent_N == 1)
	{
		for (i = 0; i < j; i++)
		{
			profile[i] = 0;
		}
	}
	else if (total == 0)
	{
		for (i = 0; i < j; i++)
		{
			profile[i] = 0;
		}
	}
	else
	{
		for (i = 0; i < j; i++)
		{
			profile[i] = profile[i] / total;
		}
	}
}

