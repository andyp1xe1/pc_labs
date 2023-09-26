#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int a[], int len, double time) {
  if (time > 0)
    printf("Time taken: %f\n", time);
  for (int i = 0; i < len; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int quick_sort_part(int arr[], int low, int high) {
  // Choosing the pivot
  int pivot = arr[high];

  // Index of smaller element and indicates
  // the right position of pivot found so far
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than the pivot
    if (arr[j] < pivot) {
      // Increment index of smaller element
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

int *copy_arr(int arr[], int len) {
  int *b = (int *)malloc(sizeof(int) * len);
  memcpy(b, arr, sizeof(int) * len);
  return b;
}

int *bubble_sort(int a[], int len, double *cnt) {
  int *a_copy = copy_arr(a, len);

  clock_t t_start = clock();
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len - 1; j++) {
      if (a_copy[j] > a_copy[j + 1]) {
        swap(&a_copy[j], &a_copy[j + 1]);
      }
    }
  }
  clock_t t_end = clock();
  *cnt = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
  return a_copy;
}

int *selection_sort(int a[], int len, double *cnt) {
  int min_idx;
  int *a_copy = copy_arr(a, len);

  clock_t t_start = clock();
  for (int i = 0; i < len - 1; i++) {
    min_idx = i;
    for (int j = i + 1; j < len; j++)
      if (a_copy[j] < a_copy[min_idx])
        min_idx = j;

    if (min_idx != i)
      swap(&a_copy[min_idx], &a_copy[i]);
  }
  clock_t t_end = clock();
  *cnt = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
  return a_copy;
}

int *insertion_sort(int a[], int len, double *cnt) {
  int key, j, i;
  int *a_copy = copy_arr(a, len);

  clock_t t_start = clock();
  for (i = 1; i < len; i++) {
    key = a_copy[i];
    j = i - 1;

    /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
    while (j >= 0 && a_copy[j] > key) {
      a_copy[j + 1] = a_copy[j];
      j = j - 1;
    }
    a_copy[j + 1] = key;
  }
  clock_t t_end = clock();
  *cnt = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
  return a_copy;
}

void quick_sort(int a[], int low, int high) {
  if (low < high) {

    // pi is partitioning index, arr[p]
    // is now at right place
    int pi = quick_sort_part(a, low, high);

    // Separately sort elements before
    // partition and after partition
    quick_sort(a, low, pi - 1);
    quick_sort(a, pi + 1, high);
  }
}

int main() {

  int len;
  double cnt = 0;

  // printf("size: ");
  // scanf("%d", &len);

  len = 100;
  int arr[len];

  for (int i = 0; i < len; i++) {
    scanf("%d", &arr[i]);
  }

  int *bubble_arr = bubble_sort(arr, len, &cnt);
  printf("\nBubble sort\n");
  print_arr(bubble_arr, len, cnt);
  free(bubble_arr);

  int *insertion_arr = insertion_sort(arr, len, &cnt);
  printf("\nInsertion sort\n");
  print_arr(insertion_arr, len, cnt);
  free(insertion_arr);

  int *a_copy = copy_arr(arr, len);

  clock_t t_start = clock();
  quick_sort(a_copy, 0, len - 1);
  clock_t t_end = clock();

  cnt = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
  printf("\nQuick sort\n");
  print_arr(a_copy, len, cnt);
  free(a_copy);

  int *selection_arr = selection_sort(arr, len, &cnt);
  printf("\nSelection sort\n");
  print_arr(selection_arr, len, cnt);
  free(selection_arr);

  return 0;
}
