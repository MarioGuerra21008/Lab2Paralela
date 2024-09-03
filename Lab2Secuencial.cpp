// Universidad del Valle de Guatemala
// Computación Paralela y Distribuida - Sección: 10
// Mario Guerra - 21008
// Daniel Valdez - 21240
// Programa secuencial que escribe N números aleatorios a un archivo y los clasifica.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Función de QuickSort secuencial
void quickSort(int* data, int lo, int hi) {
    if (lo > hi) return;
    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2]; // Pivote

    while (l <= h) {
        while ((data[l] - p) < 0) l++;
        while ((data[h] - p) > 0) h--;
        if (l <= h) {
            // Intercambia
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++;
            h--;
        }
    }
    // Llamada recursiva
    quickSort(data, lo, h);
    quickSort(data, l, hi);
}

// Función para generar números aleatorios y escribirlos en un archivo CSV
void generarNumerosAleatorios(const std::string& nombreArchivo, int n) {
    std::ofstream archivoSalida(nombreArchivo);
    if (!archivoSalida) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }
    srand(time(0)); // Inicializa la semilla para los números aleatorios
    for (int i = 0; i < n; ++i) {
        archivoSalida << rand() % 1000; // Genera un número aleatorio entre 0 y 999
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
    // Obtener la cantidad de números a generar
    int N;
    if (argc != 2) {
        N = 1000;
    } else {
        N = std::atoi(argv[1]);
    }

    // Tomar tiempo inicial 
    clock_t start = clock();

    std::string archivoEntrada = "numbers.csv";
    std::string archivoSalida = "classifiedNumbers.csv";

    // Generar números aleatorios y escribir en archivo
    generarNumerosAleatorios(archivoEntrada, N);

    // Leer números desde archivo
    std::vector<int> numeros = leerNumeros(archivoEntrada);

    // Ordenar números usando QuickSort
    quickSort(numeros.data(), 0, numeros.size() - 1);

    // Escribir números ordenados en archivo
    escribirNumeros(archivoSalida, numeros);
    // Tomar tiempo final
    clock_t end = clock();
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecución: " << elapsed_time << " segundos." << std::endl;
    
    return 0;
}
