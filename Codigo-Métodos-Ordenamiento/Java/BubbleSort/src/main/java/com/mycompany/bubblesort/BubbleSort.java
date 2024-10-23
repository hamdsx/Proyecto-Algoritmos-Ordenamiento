package com.mycompany.bubblesort;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class BubbleSort {
    public static void main(String[] args) {
        // Cambiar esta línea para especificar la ruta de los archivos
        String basePath = "C:/Users/hamdsx/Documents/VScodeExerc/";
        int totalArchivos = 22; // Total de archivos a analizar
        double[] tiempos = new double[totalArchivos]; // Array para almacenar los tiempos

        // Iterar a través de los archivos
        for (int i = 1; i <= totalArchivos; i++) {
            int[] array = leerArchivo(basePath + i + ".txt"); // Leer archivo
            System.out.println("Array Original para archivo " + i + ": ");
            imprimir(array);  

            long startTime = System.nanoTime(); // Marcar tiempo de inicio
            bubbleSort(array); // Ordenar usando Bubble Sort
            long endTime = System.nanoTime(); // Marcar tiempo de finalización

            tiempos[i - 1] = (endTime - startTime) / 1_000_000_000.0; // Guardar tiempo en segundos
            System.out.println("Duración para archivo " + i + ": " + tiempos[i - 1] + " segundos.");
            System.out.println("Array Ordenado para archivo " + i + ":");
            imprimir(array);
        }

        // Imprimir todos los tiempos al final
        System.out.println("\nTiempos de ordenamiento con Bubble Sort para cada archivo:");
        for (int j = 0; j < tiempos.length; j++) {
            System.out.printf("Archivo %d: %.10f segundos\n", j + 1, tiempos[j]);
        }
    }

    // Método de Bubble Sort
    public static void bubbleSort(int[] array) {
        int size = array.length;
        boolean cambio;
        for (int i = 0; i < size - 1; i++) {
            cambio = false;
            for (int j = 0; j < size - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
                    // Intercambiar array[j] y array[j + 1]
                    int aux = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = aux;
                    cambio = true;
                }
            }
            if (!cambio) break; // Si no hubo intercambio, el array ya está ordenado
        }
    }

    // Método para imprimir el array
    public static void imprimir(int[] array) {
        for (int num : array) {
            System.out.print(num + " ");
        }
        System.out.println();
    }

    // Método para leer el archivo y devolver un array de enteros
    public static int[] leerArchivo(String ruta) {
        // Leer los números del archivo y devolverlos en un array
        int[] numeros = new int[1000000]; // Asumimos un tamaño máximo, ajusta según lo necesario
        int count = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(ruta))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                String[] numerosComoString = linea.split(" ");
                for (String numStr : numerosComoString) {
                    // Parsear y almacenar el número en el array
                    if (count < numeros.length) {
                        numeros[count++] = Integer.parseInt(numStr);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Crear un nuevo array con el tamaño real
        int[] resultado = new int[count];
        System.arraycopy(numeros, 0, resultado, 0, count);
        return resultado;
    }
}