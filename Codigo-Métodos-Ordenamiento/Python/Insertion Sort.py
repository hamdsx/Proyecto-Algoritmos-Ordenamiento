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
def insertion_sort(array):
    for i in range(len(array)):
        pos = i
        aux = array[i]

        while pos > 0 and array[pos - 1] > aux:
            array[pos] = array[pos - 1]
            pos -= 1
        array[pos] = aux
rangos = [100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000,
          8000, 9000, 10000, 20000, 30000, 40000, 50000, 
          60000, 70000, 80000, 90000, 100000]
tiempos = []
for rango in rangos:
    array = leer_archivo(rango)
    
    start_time = time.perf_counter()
    insertion_sort(array)
    end_time = time.perf_counter()
    duration = end_time - start_time
    tiempos.append(duration)
    print(f"Duración para {rango} elementos: {duration:.10f} segundos")
print("\nTiempos de ordenamiento:")
for rango, tiempo in zip(rangos, tiempos):
    print(f"{rango} elementos: {tiempo:.10f} segundos")
