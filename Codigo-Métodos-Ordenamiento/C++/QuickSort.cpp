#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>  // Para acceder a los archivos en un directorio
#include <cstring>   // Para trabajar con cadenas (strcmp)

using namespace std;

// Función para realizar el particionamiento en Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Tomar el último elemento como pivote
    int i = low - 1; // Índice del elemento más pequeño

    for (int j = low; j < high; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++; // Incrementar el índice del elemento más pequeño
            swap(arr[i], arr[j]); // Intercambiar los elementos
        }
    }
    swap(arr[i + 1], arr[high]); // Intercambiar el pivote con el elemento más pequeño
    return (i + 1); // Retornar el índice del pivote
}

// Función principal que implementa Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Particionar el arreglo y obtener el índice del pivote
        int pi = partition(arr, low, high);

        // Ordenar recursivamente los elementos antes y después del pivote
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función para leer los datos de un archivo y almacenarlos en un vector
vector<int> readFile(const string& filePath) {
    vector<int> data;
    ifstream file(filePath);
    int number;

    if (file.is_open()) {
        while (file >> number) {
            data.push_back(number);
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo: " << filePath << endl;
    }
    return data;
}

// Función para medir el tiempo de ordenamiento de Quick Sort
void measureSortTime(const string& directoryPath) {
    DIR* dir;
    struct dirent* entry;

    // Abrir el directorio
    if ((dir = opendir(directoryPath.c_str())) != nullptr) {
        // Leer cada archivo en el directorio
        while ((entry = readdir(dir)) != nullptr) {
            // Ignorar las entradas de "." y ".."
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                string filePath = directoryPath + "/" + entry->d_name;

                // Leer los datos del archivo
                vector<int> data = readFile(filePath);

                if (!data.empty()) {
                    // Medir el tiempo de Quick Sort
                    auto start = chrono::high_resolution_clock::now();
                    quickSort(data, 0, data.size() - 1);
                    auto end = chrono::high_resolution_clock::now();

                    // Calcular la duración en segundos
                    chrono::duration<double> duration = end - start;

                    // Asegurarse de que el tiempo no sea cero
                    if (duration.count() < 0.000001) {
                        duration = chrono::duration<double>(0.000001); // Establecer un límite mínimo
                    }

                    // Mostrar el nombre del archivo y el tiempo que tomó ordenarlo
                    cout << "Archivo: " << entry->d_name << " | Tiempo de ordenamiento: "
                         << duration.count() << " segundos" << endl;
                }
            }
        }
        closedir(dir);  // Cerrar el directorio
    } else {
        cerr << "No se pudo abrir el directorio: " << directoryPath << endl;
    }
}

int main() {
    string directoryPath = "C:/Users/hamdsx/Documents/VScodeExerc";

    // Medir y mostrar el tiempo de ordenamiento de cada archivo en la carpeta
    measureSortTime(directoryPath);

    return 0;
}
