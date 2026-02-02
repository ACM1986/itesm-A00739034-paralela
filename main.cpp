#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void imprimirArreglo(const string& nombre, const vector<int>& arr, int numElementos = 20) {
    cout << nombre << " (primeros " << numElementos << " elementos): ";
    for (int i = 0; i < numElementos && i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "..." << endl;
}

int main() {
    const int N = 1000; // Cantidad de elementos
    vector<int> arregloA(N);
    vector<int> arregloB(N);
    vector<int> arregloResultado(N);
    
    int opcion;
    cout << "=== SUMA PARALELA DE ARREGLOS CON OpenMP ===" << endl;
    cout << "Cantidad de elementos: " << N << endl << endl;
    
    cout << "Seleccione una opcion:" << endl;
    cout << "1. Generar valores aleatorios" << endl;
    cout << "2. Ingresar valores manualmente (solo primeros 10)" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cout << endl;
    
    if (opcion == 1) {
        // Inicializar con valores aleatorios
        srand(time(0));
        
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            arregloA[i] = rand() % 100; // Valores entre 0 y 99
            arregloB[i] = rand() % 100;
        }
        
        cout << "Arreglos inicializados con valores aleatorios entre 0 y 99" << endl;
    }
    else {
        // Ingresar valores manualmente (solo los primeros 10)
        cout << "Ingrese 10 valores para el Arreglo A:" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "A[" << i << "]: ";
            cin >> arregloA[i];
        }
        
        cout << "\nIngrese 10 valores para el Arreglo B:" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "B[" << i << "]: ";
            cin >> arregloB[i];
        }
        
        // Rellenar el resto con valores aleatorios
        srand(time(0));
        for (int i = 10; i < N; i++) {
            arregloA[i] = rand() % 100;
            arregloB[i] = rand() % 100;
        }
        
        cout << "\nLos elementos restantes (10-" << N-1 << ") se llenaron aleatoriamente" << endl;
    }
    
    cout << "\n=== ARREGLOS ORIGINALES ===" << endl;
    imprimirArreglo("Arreglo A", arregloA);
    imprimirArreglo("Arreglo B", arregloB);
    
    // Obtener número de hilos disponibles
    int numHilos;
    #pragma omp parallel
    {
        #pragma omp single
        numHilos = omp_get_num_threads();
    }
    
    cout << "\n=== PROCESAMIENTO PARALELO ===" << endl;
    cout << "Numero de hilos disponibles: " << numHilos << endl;
    
    // Medir tiempo de ejecución
    double tiempoInicio = omp_get_wtime();
    
    // SUMA PARALELA usando OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        arregloResultado[i] = arregloA[i] + arregloB[i];
    }
    
    double tiempoFin = omp_get_wtime();
    double tiempoTotal = tiempoFin - tiempoInicio;
    
    cout << "Suma completada en " << fixed << setprecision(6) << tiempoTotal << " segundos" << endl;
    
    // Imprimir resultados
    cout << "\n=== RESULTADO ===" << endl;
    imprimirArreglo("Arreglo Resultado (A+B)", arregloResultado);
    
    // Verificar algunos resultados manualmente
    cout << "\n=== VERIFICACION (primeros 10 elementos) ===" << endl;
    cout << left << setw(8) << "Indice" << setw(10) << "A[i]" << setw(10) << "B[i]" 
         << setw(15) << "Resultado[i]" << setw(15) << "A[i]+B[i]" << "Correcto?" << endl;
    cout << string(70, '-') << endl;
    
    bool todoCorrecto = true;
    for (int i = 0; i < 10; i++) {
        int suma = arregloA[i] + arregloB[i];
        bool correcto = (arregloResultado[i] == suma);
        todoCorrecto = todoCorrecto && correcto;
        
        cout << left << setw(8) << i 
             << setw(10) << arregloA[i] 
             << setw(10) << arregloB[i] 
             << setw(15) << arregloResultado[i] 
             << setw(15) << suma 
             << (correcto ? "SI" : "NO") << endl;
    }
    
    if (todoCorrecto) {
        cout << "\n¡Verificacion exitosa! Todos los elementos verificados son correctos." << endl;
    } else {
        cout << "\n¡Error! Algunos elementos no son correctos." << endl;
    }
    
    return 0;
}
