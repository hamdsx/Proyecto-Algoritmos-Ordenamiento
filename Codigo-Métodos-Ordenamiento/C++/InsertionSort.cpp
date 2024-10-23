#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>  // Para acceder a los archivos en un directorio
#include <cstring>   // Para trabajar con cadenas (strcmp)

using namespace std;

// Función para realizar Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Mover los elementos de arr[0..i-1], que son mayores que key, a una posición adelante de su posición actual
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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

// Función para medir el tiempo de ordenamiento de Insertion Sort
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
                    // Medir el tiempo de Insertion Sort
                    auto start = chrono::high_resolution_clock::now();
                    insertionSort(data);
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
