#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>
#include <cstring>

using namespace std;

// Función para realizar Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Inicializa el mayor como la raíz
    int left = 2 * i + 1; // Índice del hijo izquierdo
    int right = 2 * i + 2; // Índice del hijo derecho

    // Si el hijo izquierdo es mayor que la raíz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Si el hijo derecho es mayor que el mayor hasta ahora
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Si el mayor no es la raíz
    if (largest != i) {
        swap(arr[i], arr[largest]); // Intercambiar
        heapify(arr, n, largest); // Recursivamente heapificar el subárbol afectado
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Construir el heap (reorganizar el arreglo)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extraer elementos uno a uno del heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Intercambiar el primer elemento con el último
        heapify(arr, i, 0); // Restaurar el heap
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

// Función para medir el tiempo de ordenamiento de Heap Sort
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
                    // Medir el tiempo de Heap Sort
                    auto start = chrono::high_resolution_clock::now();
                    heapSort(data);
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


