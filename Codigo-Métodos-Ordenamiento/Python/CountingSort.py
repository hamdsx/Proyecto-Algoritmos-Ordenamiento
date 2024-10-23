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

def counting_sort(array):
    mx = max(array)
    mn = min(array)
    rng = mx - mn + 1
    conteo = [0] * rng
    salida = [0] * len(array)
    for i in range(len(array)):
        conteo[array[i] - mn] += 1
    
    for i in range(1, rng):
        conteo[i] += conteo[i - 1]

    for i in range(len(array) - 1, -1, -1):
        salida[conteo[array[i] - mn] - 1] = array[i]
        conteo[array[i] - mn] -= 1

    for i in range(len(array)):
        array[i] = salida[i]

rangos = [100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 
          10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000]

tiempos_de_ejecucion = []

for rango in rangos:
    array = leer_archivo(rango)
    print(f"Array Original (tamaño {rango}): ")
    print(array)
    
    start_time = time.perf_counter()
    counting_sort(array)
    end_time = time.perf_counter()
    
    duration = end_time - start_time
    tiempos_de_ejecucion.append(duration)
    
    print(f"Duración para {rango} elementos: {duration:.10f} segundos")
    print("Array Ordenado: ")
    print(array)

print("\nTiempos de ejecución para cada tamaño de archivo:")
for rango, tiempo in zip(rangos, tiempos_de_ejecucion):
    print(f"Tamaño {rango}: {tiempo:.10f} segundos")