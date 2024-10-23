package com.mycompany.quicksort;

import java.io.*;
import java.nio.file.*;
import java.util.*;

public class QuickSort {

    public static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);

            quickSort(arr, low, pi - 1); 
            quickSort(arr, pi + 1, high); 
        }
    }

    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high]; 
        int i = (low - 1); 

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;

                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
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

                        quickSort(data, 0, data.length - 1);

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