//Lis 2032-01 Emiliano Saucedo Tavitas, Daniel Martinez Macedo, Roberto Carlos Benitez Rizzo, Adriana de Jesús Jerónimo Alarcón

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ARRAY_SIZE 10000

// Funciones de ordenamiento
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void countSort(int arr[], int n, int exp);
void radixSort(int arr[], int n);

// Funciones auxiliares
void printArray(int arr[], int n);

int main() {
    int option, dataType, size;
    clock_t start, end;
    double time_taken;

    printf("Seleccione el tipo de datos a ordenar:\n");
    printf("1. Enteros\n2. Flotantes\n3. Caracteres\n4. Cadenas de texto\n");
    scanf("%d", &dataType);

    printf("Ingrese la cantidad de datos a ordenar: ");
    scanf("%d", &size);

    int arr[MAX_ARRAY_SIZE];

    // Generar números aleatorios
    srand(time(0)); // Semilla para la función rand()
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Generar números aleatorios entre 0 y 999
    }

    printf("Arreglo sin ordenar:\n");
    printArray(arr, size);

    printf("\nSeleccione el metodo de ordenamiento:\n");
    printf("1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n");
    printf("4. Merge Sort\n5. Quick Sort\n6. Radix Sort\n");
    scanf("%d", &option);

    start = clock();

    switch (option) {
        case 1:
            bubbleSort(arr, size);
            printf("\nBubble Sort:\n");
            break;
        case 2:
            selectionSort(arr, size);
            printf("\nSelection Sort:\n");
            break;
        case 3:
            insertionSort(arr, size);
            printf("\nInsertion Sort:\n");
            break;
        case 4:
            mergeSort(arr, 0, size - 1);
            printf("\nMerge Sort:\n");
            break;
        case 5:
            quickSort(arr, 0, size - 1);
            printf("\nQuick Sort:\n");
            break;
        case 6:
            radixSort(arr, size);
            printf("\nRadix Sort:\n");
            break;
        default:
            printf("Opción invalida.\n");
            return 1;
    }

    end = clock();

    printf("Arreglo ordenado:\n");
    printArray(arr, size);

    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %f segundos\n", time_taken);

    return 0;
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    int temp;
    int j;
    for (j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void countSort(int arr[], int n, int exp) {
        int output[n];
    int count[10] = {0};
    int i;

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > m)
            m = arr[i];
    }

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


