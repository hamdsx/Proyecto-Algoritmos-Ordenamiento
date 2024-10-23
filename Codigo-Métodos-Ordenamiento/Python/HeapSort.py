import time

def leer_archivo(rango):
    ruta = f"C:/Users/hamdsx/Documents/VScodeExerc/{rango}.txt"
    numeros = []
    try:
        with open(ruta, 'r') as archivo:
            for linea in archivo:
                numeros_como_string = linea.split()
                for num_str in numeros_como_string:
                    if len(numeros) < rango:
                        numeros.append(int(num_str))
    except IOError as e:
        print(f"Error al abrir el archivo: {ruta}")
        print(e)

    return numeros

def heap_sort(array):
    n = len(array)
    for i in range(n // 2 - 1, -1, -1):
        heapify(array, n, i)
    
    for i in range(n - 1, 0, -1):
        array[i], array[0] = array[0], array[i]
        heapify(array, i, 0)

def heapify(array, n, i):
    indice_mayor = i
    hijo_izquierdo = 2 * i + 1
    hijo_derecho = 2 * i + 2

    if hijo_izquierdo < n and array[hijo_izquierdo] > array[indice_mayor]:
        indice_mayor = hijo_izquierdo

    if hijo_derecho < n and array[hijo_derecho] > array[indice_mayor]:
        indice_mayor = hijo_derecho

    if indice_mayor != i:
        array[i], array[indice_mayor] = array[indice_mayor], array[i]
        heapify(array, n, indice_mayor)

# Rango de tamaños para los archivos
rangos = [100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000,
          8000, 9000, 10000, 20000, 30000, 40000, 50000, 
          60000, 70000, 80000, 90000, 100000]

# Lista para almacenar los tiempos de ordenamiento
tiempos = []

for rango in rangos:
    array = leer_archivo(rango)
    
    start_time = time.perf_counter()
    heap_sort(array)
    end_time = time.perf_counter()
    
    duration = end_time - start_time
    tiempos.append(duration)
    print(f"Duración para {rango} elementos: {duration:.10f} segundos")

# Si deseas ver los tiempos después de la ejecución:
print("\nTiempos de ordenamiento:")
for rango, tiempo in zip(rangos, tiempos):
    print(f"{rango} elementos: {tiempo:.10f} segundos")
