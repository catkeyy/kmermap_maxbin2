#include <iostream>
#include <fstream>
#include "kmerMap.h"
#include "Profiler.h"


/*
INPUT: archivo fasta, kmeros (k=4, o 5, etc...), 1 o 0 simetrico
ej: simetrico es si TAC es lo mismo que CAT (0 se tratan como diferentes)

el output es un archivo con vectores para cada read/contig
cada perfil es un vector de frecuencias de casa posible k-mer en la secuencia.
nota: el programa es determinista, es decir, para cada configuracion de entrada va a dar el mismo resultado 
*/


void process(const char* fastaFile, int k, bool symmetric) {
    //si symmetric = 1 trata a un k-mer y su reverso (ej: TAC -reverso-> CAT) como el mismo
    //para el conteo posterior de frecuencias
    kmerMap kmap(k, symmetric);

    ifstream file(fastaFile);
    string line, seq, header;

    //int flag = 0;
    while (getline(file, line)) {
        //flag = 0;
        //if (flag == 0){
        //    cout << "estoy en el while" << endl;
        //}
        
        //por si acaso
        if (line.empty()) continue;

        //si empieza con >, es un header (ej: header: >RL|S1|C0):
        if (line[0] == '>') { 
            if (!seq.empty()) {
                Profiler profiler(k, seq.c_str(), &kmap); //calcula el perfil para cada read
                
                double* profile = profiler.getProfile(); //retorna la variable perfil
                int entry_num = kmap.getEntryNum(); //retorna "entry_num" del kmap que es si k=4 entonces este es 4^4 = 256 (tamano del vector de diferentes kmeros)
                
                //cout << "header: " << header << endl;
                std::cout << header << endl;
                //cout << "perfil: " << endl;
                /*ej:
                    header: >RL|S1|C0
                    perfil: 0 0 0 0 0 0 0.00124069 0 0.00124069 0.00248139 0 0.00248139 0.00992556 ...
                */

                /*
                profile[i] =
                    (número de veces que aparece el k-mer i en la secuencia) / (total de k-mers en la secuencia)
                */
                for (int i = 0; i < entry_num; ++i) {
                    std::cout << profile[i] << " "; // [0.015 0.25 0.35 ....]  un total de entry_num veces
                }
                std::cout << "\n\n";
                seq.clear();
            }
            header = line;
        } else { 
            seq += line;
        }
    }

    //esta es la ultima linea, por alguan razon si no está esto no toma la ultima
    if (!seq.empty()) {
        //flag = 1;
        //if (flag == 1){
        //    cout << "Estoy en el if fuera del while" << endl;
        //
        //es lo mismo que arriba
        Profiler profiler(k, seq.c_str(), &kmap); //calcula el perfil internamente con computeProfile(), lo asigna a la variable profile
        double* profile = profiler.getProfile(); //retorna la variable "profile"
        int entry_num = kmap.getEntryNum(); //retorna el tamano del vector para cada read (perfil)

        std::cout << header << endl;
        for (int i = 0; i < entry_num; ++i) {
            std::cout << profile[i] << " ";
        }
        std::cout << endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <archivo.fasta> <k> <simetrico (0/1)>\n";
        return 1;
    }

    process(argv[1], atoi(argv[2]), atoi(argv[3]) == 1);
    return 0;
}