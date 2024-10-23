
package com.mycompany.mergesort;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class MergeSort {

    public static void mergeSort(int[] arr) {
        if (arr.length < 2) {
            return;
        }
        int mid = arr.length / 2;
        int[] left = Arrays.copyOfRange(arr, 0, mid);
        int[] right = Arrays.copyOfRange(arr, mid, arr.length);

        mergeSort(left);
        mergeSort(right);

        merge(arr, left, right);
    }

    private static void merge(int[] arr, int[] left, int[] right) {
        int i = 0, j = 0, k = 0;
        while (i < left.length && j < right.length) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }
        while (i < left.length) {
            arr[k++] = left[i++];
        }
        while (j < right.length) {
            arr[k++] = right[j++];
        }
    }

    public static int[] readFile(String filePath) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(filePath));
        int[] numbers = new int[lines.size()];
        for (int i = 0; i < lines.size(); i++) {
            numbers[i] = Integer.parseInt(lines.get(i).trim());
        }
        return numbers;
    }

    public static void main(String[] args) {
        String directoryPath = "C:/Users/hamdsx/Documents/VScodeExerc/";

        List<Map.Entry<String, Double>> timeList = new ArrayList<>();
        List<String> fileNamesAnalyzed = new ArrayList<>();

        try {
            Files.list(Paths.get(directoryPath)).forEach(filePath -> {
                if (Files.isRegularFile(filePath) && filePath.toString().endsWith(".txt")) {
                    try {
                        int[] data = readFile(filePath.toString());

                        long startTime = System.nanoTime();

                        mergeSort(data);

                        long endTime = System.nanoTime();

                        double timeInSeconds = (endTime - startTime) / 1_000_000_000.0;

                        timeList.add(new AbstractMap.SimpleEntry<>(filePath.getFileName().toString(), timeInSeconds));
                        fileNamesAnalyzed.add(filePath.getFileName().toString());

                    } catch (IOException e) {
                        System.out.println("Error al leer el archivo: " + filePath.getFileName());
                    }
                }
            });

            timeList.sort(Comparator.comparing(Map.Entry::getKey));

            System.out.println("Nombres de archivos analizados:");
            for (String fileName : fileNamesAnalyzed) {
                System.out.println(fileName);
            }

            System.out.println("\nResultados de tiempo de ordenamiento:");
            for (Map.Entry<String, Double> entry : timeList) {
                System.out.println("Archivo: " + entry.getKey() + " - Tiempo en ordenar: " + entry.getValue() + " segundos");
            }

            Double[] timesArray = timeList.stream().map(Map.Entry::getValue).toArray(Double[]::new);

            System.out.println("\nTiempos de ordenamiento en segundos (en un array):");
            System.out.println(Arrays.toString(timesArray));

        } catch (IOException e) {
            System.out.println("Error al acceder al directorio: " + e.getMessage());
        }
    }
}
