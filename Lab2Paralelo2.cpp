#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <omp.h> // Para OpenMP

// Función de QuickSort paralela
void quickSort(int* data, int lo, int hi) {
    if (lo >= hi) return;
    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2]; // Pivote

    while (l <= h) {
        while ((data[l] - p) < 0) l++;
        while ((data[h] - p) > 0) h--;
        if (l <= h) {
            std::swap(data[l], data[h]);
            l++;
            h--;
        }
    }

    #pragma omp task shared(data) if(hi-lo > 10000) mergeable // Umbral más alto para paralelización
    quickSort(data, lo, h);

    #pragma omp task shared(data) if(hi-lo > 10000) mergeable
    quickSort(data, l, hi);

    #pragma omp taskwait // Espera a que las tareas terminen antes de continuar
}

// Función para generar números aleatorios y escribirlos en un archivo CSV
void generarNumerosAleatorios(const std::string& nombreArchivo, int n) {
    std::ofstream archivoSalida(nombreArchivo);
    if (!archivoSalida) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }
    
    std::vector<int> numeros(n);

    // Generación paralela de números aleatorios
    #pragma omp parallel
    {
        unsigned int seed = time(0) ^ omp_get_thread_num();
        #pragma omp for schedule(static)
        for (int i = 0; i < n; ++i) {
            numeros[i] = rand_r(&seed) % 1000;
        }
    }

    // Escritura secuencial de los números al archivo
    for (int i = 0; i < n; ++i) {
        archivoSalida << numeros[i];
        if (i < n - 1) {
            archivoSalida << ",";
        }
    }

    archivoSalida.close();
}

// Función para leer números desde un archivo CSV y almacenarlos en un vector
std::vector<int> leerNumeros(const std::string& nombreArchivo) {
    std::vector<int> numeros;
    std::ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo para lectura." << std::endl;
        return numeros;
    }

    int numero;
    char coma;
    while (archivoEntrada >> numero) {
        numeros.push_back(numero);
        archivoEntrada >> coma; // Leer la coma
    }

    archivoEntrada.close();
    return numeros;
}

// Función para escribir números ordenados en un archivo
void escribirNumeros(const std::string& nombreArchivo, const std::vector<int>& numeros) {
    std::ofstream archivoSalida(nombreArchivo);
    if (!archivoSalida) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }

    for (size_t i = 0; i < numeros.size(); ++i) {
        archivoSalida << numeros[i];
        if (i < numeros.size() - 1) {
            archivoSalida << ",";
        }
    }
    
    archivoSalida.close();
}

int main(int argc, char* argv[]) {
    int N;
    if (argc != 2) {
        N = 1000;
    } else {
        N = std::atoi(argv[1]);
    }

    clock_t start = clock();

    std::string archivoEntrada = "numbers.csv";
    std::string archivoSalida = "classifiedNumbers.csv";
    
    generarNumerosAleatorios(archivoEntrada, N);

    std::vector<int> numeros = leerNumeros(archivoEntrada);

    #pragma omp parallel // Inicia la región paralela
    {
        #pragma omp single // Solo un hilo ejecuta quicksort
        quickSort(numeros.data(), 0, numeros.size() - 1);
    }

    escribirNumeros(archivoSalida, numeros);

    clock_t end = clock();
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecución: " << elapsed_time << " segundos." << std::endl;

    return 0;
}
