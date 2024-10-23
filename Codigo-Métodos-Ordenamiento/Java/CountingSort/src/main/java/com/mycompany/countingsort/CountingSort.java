/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.countingsort;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class CountingSort {
    public static void main(String[] args) {
        String basePath = "C:/Users/hamdsx/Documents/VScodeExerc/";
        int totalArchivos = 22;
        double[] tiempos = new double[totalArchivos];

        for (int i = 1; i <= totalArchivos; i++) {
            int[] array = leerArchivo(basePath + i + ".txt");
            long startTime = System.nanoTime();
            countingSort(array);
            long endTime = System.nanoTime();
            tiempos[i - 1] = (endTime - startTime) / 1_000_000_000.0;
        }

        imprimirTiempos(tiempos, "Counting Sort");
    }

    public static void countingSort(int[] array) {
        int max = Arrays.stream(array).max().getAsInt();
        int[] count = new int[max + 1];
        int[] output = new int[array.length];

        for (int num : array) count[num]++;
        for (int i = 1; i <= max; i++) count[i] += count[i - 1];
        for (int i = array.length - 1; i >= 0; i--) {
            output[count[array[i]] - 1] = array[i];
            count[array[i]]--;
        }
        System.arraycopy(output, 0, array, 0, array.length);
    }

    public static int[] leerArchivo(String ruta) {
        return BubbleSort.leerArchivo(ruta); // Reutilizando método
    }

    public static void imprimirTiempos(double[] tiempos, String metodo) {
        BubbleSort.imprimirTiempos(tiempos, metodo); // Reutilizando método
    }
}