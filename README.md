#Calculo perfiles descriptores de kmeros en reads/contigs extraido de maxbin2

##compilar:
g++ main.cpp kmerMap.cpp Profiler.cpp -o kmer_profile.exe

##Uso:
./kmer_profile.exe <archivo.fasta> <k> <simetrico (0/1)>

##Ejemplo de ejecución:
./kmer_profile.exe /home/abc/experimentos_maxbin/descriptores/reads_gsa_anonymous.fasta 5 1 > frecuencias_kmeros_por_contig_normalizadas.txt


##Ejemplo de archivo de salida (extracto)

----------------------------------
>RL|S1|C0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.00124224 0 0.00124224 ...

>RL|S1|C1
0.00321543 0.011254 0.00482315 0.00482315 0.011254 0.00321543 0.00482315 ....
----------------------------------

##¿Cómo calcula el vector de frecuencias de kmeros en contigs normalizados?

Para cada posición "i" en el vector asociado a cada de cada read:
frecuencia[i] = (número de veces que aparece el k-mer i en la secuencia) / (total de k-mers en la secuencia)

# kmermap_maxbin2
# kmermap_maxbin2
# kmermap_maxbin2
# kmermap_maxbin2
