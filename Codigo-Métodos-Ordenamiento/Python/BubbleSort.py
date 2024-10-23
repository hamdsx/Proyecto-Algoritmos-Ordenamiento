import random
import time
import os
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

def read_file(file_path):
    with open(file_path, 'r') as file:
        return [int(line.strip()) for line in file.readlines()]

directory = 'C:/Users/hamdsx/Documents/VScodeExerc/'

execution_times = []

file_names = ['100.txt', '500.txt', '1000.txt', '2000.txt', '3000.txt', 
              '4000.txt', '5000.txt', '6000.txt', '7000.txt', '8000.txt', 
              '9000.txt', '10000.txt', '20000.txt', '30000.txt', 
              '40000.txt', '50000.txt', '60000.txt', '70000.txt', 
              '80000.txt', '90000.txt', '100000.txt']

for file_name in file_names:
    file_path = os.path.join(directory, file_name)
    
    array = read_file(file_path)
    start_time = time.time()
    bubble_sort(array)
    end_time = time.time()
    execution_time = end_time - start_time
    execution_times.append(execution_time)
    print(f"Duración para {file_name}: {execution_time:.10f} segundos.")

print("\nTiempos de ejecución para todos los archivos:")
print(execution_times)