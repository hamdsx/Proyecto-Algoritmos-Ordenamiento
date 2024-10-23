#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>  // Para acceder a los archivos en un directorio
#include <cstring>   // Para trabajar con cadenas (strcmp)

using namespace std;

// Función para realizar Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        // Encontrar el índice del elemento mínimo
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Intercambiar el elemento mínimo encontrado con el primer elemento
        swap(arr[minIndex], arr[i]);
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

// Función para medir el tiempo de ordenamiento de Selection Sort
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
                    // Medir el tiempo de Selection Sort
                    auto start = chrono::high_resolution_clock::now();
                    selectionSort(data);
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
