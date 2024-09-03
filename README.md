# Laboratorio 2 - Computación Paralela y Distribuida 🖥️🚀

## Descripción del Proyecto 📄

Este proyecto consiste en un programa en C++ que genera números aleatorios, los escribe en un archivo CSV y luego los ordena utilizando el algoritmo QuickSort. Se han implementado tanto una versión secuencial como una versión paralela del programa para comparar los tiempos de ejecución y evaluar el speedup obtenido con la paralelización mediante OpenMP.

## Instrucciones de Compilación y Ejecución ⚙️

### Versión Secuencial
Para compilar y ejecutar la versión secuencial del programa, utiliza los siguientes comandos:

```bash
g++ -o Lab2Secuencial Lab2Secuencial.cpp
./Lab2Secuencial <Número de números aleatorios>
```

### Versión Paralela
Para compilar y ejecutar la versión paralela del programa, usa los siguientes comandos:

```bash
g++ Lab2Paralelo.cpp -o Lab2Paralelo -fopenmp
./Lab2Paralelo <Número de números aleatorios>
```

## Autores ✍️

- [Mario Guerra](https://github.com/MarioGuerra21008)
- [Daniel Valdez](https://github.com/Danval-003)
