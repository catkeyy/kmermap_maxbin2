# kmermap_maxbin2

Cálculo de Perfiles Descriptores de K-mers en Reads/Contigs (extraído de MaxBin2)

---

## Compilación

```bash
g++ main.cpp kmerMap.cpp Profiler.cpp -o kmer_profile.exe
```

---

## Uso

```bash
./kmer_profile.exe <archivo.fasta> <k> <simétrico (0/1)>
```

- `<archivo.fasta>`: Ruta al fichero FASTA de reads o contigs.  
- `<k>`: Longitud de los k-mers.  
- `<simétrico>`:  
  - `0` = no simétrico (distingue k-mer y su reverso complementario)  
  - `1` = simétrico (agrupa k-mer y su reverso complementario)  

---

## Ejemplo de Ejecución

```bash
./kmer_profile.exe \
  /home/abc/experimentos_maxbin/descriptores/reads_gsa_anonymous.fasta \
  5 1 \
> frecuencias_kmeros_por_contig_normalizadas.txt
```

---

## Ejemplo de Salida (extracto)

```
----------------------------------
>RL|S1|C0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.00124224 0 0.00124224 ...

>RL|S1|C1
0.00321543 0.011254 0.00482315 0.00482315 0.011254 0.00321543 0.00482315 ....
----------------------------------
```

---

## ¿Como se calcula el vector de frecuencias de k-mers normalizado?

Para cada contig (o read), se construye un vector cuyos componentes corresponden a cada posible k-mer. El valor de cada componente `i` es:

```
frecuencia[i] = (número de veces que aparece el k-mer i en la secuencia)
               / (total de k-mers en la secuencia)
```

De esta forma, todas las frecuencias suman 1, lo que permite comparar perfiles entre secuencias de distinta longitud.  
