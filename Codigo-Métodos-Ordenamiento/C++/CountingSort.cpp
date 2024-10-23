#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>
#include <cstring> 
#include <algorithm> 

using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    vector<int> output(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - minVal]++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
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
                    countingSort(data);
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
