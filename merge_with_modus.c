#include "stdio.h"
#include "stdlib.h"
//#define DEBUG

//fungsi untuk merge subarrays
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    #ifdef DEBUG
    printf("\nMerging the subarrays:\n");
    printf("Left subarray [%d to %d]: ", left, mid);
    for (i = 0; i < n1; i++)
        printf("%d ", L[i]);
    printf("\nRight subarray [%d to %d]: ", mid + 1, right);
    for (j = 0; j < n2; j++)
        printf("%d ", R[j]);
    printf("\n");
    #endif
    
    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
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
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    #ifdef DEBUG
    printf("Merged result [%d to %d]: ", left, right);
    for (i = left; i <= right; i++)
        printf("%d ", arr[i]);
    printf("\n");
    #endif
    
    // Free the temporary arrays
    free(L);
    free(R);
}

// Main function that implements merge sort
void merge_sort_recursive(int arr[], int left, int right) {
    if (left < right) {
        #ifdef DEBUG
        printf("\nSplitting array [%d to %d]\n", left, right);
        printf("Current subarray: ");
        for (int i = left; i <= right; i++)
            printf("%d ", arr[i]);
        printf("\n");
        #endif
        
        // Find the middle point
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        merge_sort_recursive(arr, left, mid);
        merge_sort_recursive(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Wrapper function for merge sort
int merge_sort(int a[], int size) {
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    merge_sort_recursive(a, 0, size - 1);
    
    printf("\nSorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}


void find_mode(int Array[], int size){
   
    int max_freq = 0;
    int current_freq = 1;
    int mode = Array[0];  // Default to first element
    
    // For an empty array, return without printing
    if (size <= 0) {
        return;
    }
    
    // Find mode in the sorted array
    for (int i = 1; i < size; i++) {
        if (Array[i] == Array[i - 1]) {
            // Count consecutive occurrences
            current_freq++;
        } else {
            // Check if we found a new mode
            if (current_freq > max_freq) {
                max_freq = current_freq;
                mode = Array[i - 1];
            }
            // Reset frequency counter for the new element
            current_freq = 1;
        }
    }
    
    // Check the last sequence as well
    if (current_freq > max_freq) {
        max_freq = current_freq;
        mode = Array[size - 1];
    }
    
    // Print the mode
    printf("MODUS: %d (frequency: %d)\n", mode, max_freq);
    
    // If you want to print all modes (in case of multiple modes)
    printf("All modes with frequency %d: ", max_freq);
    current_freq = 1;
    
    for (int i = 1; i < size; i++) {
        if (Array[i] == Array[i - 1]) {
            current_freq++;
        } else {
            if (current_freq == max_freq) {
                printf("%d ", Array[i - 1]);
            }
            current_freq = 1;
        }
    }
    
    // Check the last sequence for multiple modes
    if (current_freq == max_freq) {
        printf("%d", Array[size - 1]);
    }
    printf("\n");
  
  
         
}

int main() {
    int a;
    printf("masukkan size array: ");
    scanf("%d", &a);
    
    int* a_Processed = malloc(sizeof(int) * a);
    if (a_Processed == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d numbers:\n", a);
    for (int i = 0; i < a; i++) {
        scanf("%d", &a_Processed[i]);
    }
    
    merge_sort(a_Processed, a);
    find_mode(a_Processed, a); 
    free(a_Processed);
    return 0;
}
