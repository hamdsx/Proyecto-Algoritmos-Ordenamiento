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
def merge_sort(array):
    if len(array) < 2:
        return array
    mid = len(array) // 2
    left = merge_sort(array[:mid])
    right = merge_sort(array[mid:]) 
    return merge(left, right)
def merge(left, right):
    merged = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
    merged.extend(left[i:])
    merged.extend(right[j:])
    return merged

rangos = [100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000,
          8000, 9000, 10000, 20000, 30000, 40000, 50000, 
          60000, 70000, 80000, 90000, 100000]

tiempos = []

for rango in rangos:
    array = leer_archivo(rango)
    
    start_time = time.perf_counter()
    array_ordenado = merge_sort(array)
    end_time = time.perf_counter()
    
    duration = end_time - start_time
    tiempos.append(duration)
    print(f"Duración para {rango} elementos: {duration:.10f} segundos")

print("\nTiempos de ordenamiento:")
for rango, tiempo in zip(rangos, tiempos):
    print(f"{rango} elementos: {tiempo:.10f} segundos")