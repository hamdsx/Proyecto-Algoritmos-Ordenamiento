#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h> 
#include <cstring> 
using namespace std;
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
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
void measureSortTime(const string& directoryPath) {
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(directoryPath.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                string filePath = directoryPath + "/" + entry->d_name;
                vector<int> data = readFile(filePath);
                if (!data.empty()) {
                    auto start = chrono::high_resolution_clock::now();
                    bubbleSort(data);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    cout << "Archivo: " << entry->d_name << " | Tiempo de ordenamiento: "
                         << duration.count() << " segundos" << endl;
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "No se pudo abrir el directorio: " << directoryPath << endl;
    }
}
int main() {
    string directoryPath = "C:/Users/hamdsx/Documents/VScodeExerc";
    measureSortTime(directoryPath);
    return 0;
}
