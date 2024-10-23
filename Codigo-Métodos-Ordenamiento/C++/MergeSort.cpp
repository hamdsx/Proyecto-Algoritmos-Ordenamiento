#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>  // Para acceder a los archivos en un directorio
#include <cstring>   // Para trabajar con cadenas (strcmp)

using namespace std;

// Función para combinar dos subarreglos
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales
    vector<int> L(n1);
    vector<int> R(n2);

    // Copiar datos a los arreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Combinar los arreglos temporales de nuevo en arr[left..right]
    int i = 0; // Índice inicial del primer subarreglo
    int j = 0; // Índice inicial del segundo subarreglo
    int k = left; // Índice inicial del subarreglo combinado

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal que implementa Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenar la primera y la segunda mitad
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Combinar las mitades ordenadas
        merge(arr, left, mid, right);
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

// Función para medir el tiempo de ordenamiento de Merge Sort
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
                    // Medir el tiempo de Merge Sort
                    auto start = chrono::high_resolution_clock::now();
                    mergeSort(data, 0, data.size() - 1);
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
