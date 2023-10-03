#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int wid;
  int len;
  int *arr;
  int *spiral;
} matrix;

void m_gen(matrix m) {
  for (int i = 0; i < m.len * m.wid; i++) {
    m.arr[i] = 50 + rand() % 951;
  }
}

// void m_sort(matrix m) { return; }

void m_climb(matrix m) {
  int i_beg = 0, i_end = 0, j_beg = 0, j_end = 0, i = 0, j = 0;
  int k = 0;
  while (k < m.len * m.wid) {
    m.spiral[k] = i * m.wid + j;
    if (i == i_beg && j < m.wid - j_end - 1)
      ++j;
    else if (j == m.wid - j_end - 1 && i < m.len - i_end - 1)
      ++i;
    else if (i == m.len - i_end - 1 && j > j_beg)
      --j;
    else
      --i;

    if ((i == i_beg + 1) && (j == j_beg) && (j_beg != m.wid - j_end - 1)) {
      ++i_beg;
      ++i_end;
      ++j_beg;
      ++j_end;
    }
    ++k;
  }
}

void m_print(matrix m) {
  for (int i = 0; i < m.len; i++) {
    for (int j = 0; j < m.wid; j++) {
      printf("%4i ", m.arr[i * m.wid + j]);
    }
    printf("\n");
  }
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// insertion sort on by the spiral
void sort(matrix m) {
  int key, j, i;

  m_climb(m);

  for (i = 1; i < m.len * m.wid; i++) {
    key = m.arr[m.spiral[i]];
    j = i - 1;

    /* Move elements of arr[spiral[0..i-1]], that are
      greater than key, to one position ahead
      of their current position */
    while (j >= 0 && m.arr[m.spiral[j]] > key) {
      m.arr[m.spiral[j + 1]] = m.arr[m.spiral[j]];
      j = j - 1;
    }
    m.arr[m.spiral[j + 1]] = key;
  }
}

int main() {

  matrix m;

  printf("Input matrix size to be generated and sorted as: len/wid\n");
  scanf("%i/%i", &m.len, &m.wid);

  m.arr = malloc(sizeof(int) * m.len * m.wid);
  m.spiral = malloc(sizeof(int) * m.len * m.wid);

  printf("\n");
  printf("size: %i/%i\n", m.len, m.wid);
  m_gen(m);
  printf("random array:\n");
  m_print(m);
  printf("\n");
  printf("\n");
  sort(m);
  printf("sorted array:\n");
  m_print(m);
  printf("\n");

  //  printf("\n");
  //  for (int i = 0; i < m.len; i++) {
  //    for (int j = 0; j < m.wid; j++) {
  //      printf("%4i ", m.spiral[i * m.wid + j]);
  //    }
  //    printf("\n");
  //  }
  //  printf("\n");
  free(m.arr);
  free(m.spiral);
  return 0;
}

// int quick_sort_part(matrix m, int low, int high) {
//   // Choosing the pivot
//   int pivot = m.arr[m.spiral[high]];
//
//   // Index of smaller element and indicates
//   // the right position of pivot found so far
//   int i = (low - 1);
//
//   for (int j = low; j <= high - 1; j++) {
//     // If current element is smaller than the pivot
//     if (m.arr[m.spiral[j]] < pivot) {
//       // Increment index of smaller element
//       i++;
//       swap(&m.arr[m.spiral[i]], &m.arr[m.spiral[j]]);
//     }
//   }
//   swap(&m.arr[m.spiral[i + 1]], &m.arr[m.spiral[high]]);
//   return (i + 1);
// }
//
// void quick_sort(matrix m, int low, int high) {
//   if (low < high) {
//
//     // pi is partitioning index, arr[p]
//     // is now at right place
//     int pi = quick_sort_part(m, low, high);
//
//     // Separately sort elements before
//     // partition and after partition
//     quick_sort(m, low, pi - 1);
//     quick_sort(m, pi + 1, high);
//   }
// }
//
// void m_climb(matrix m) {
//  int b = 0;
//  int k = 0;
//  int x = 0;
//  int y = 0;
//  while (k < m.len * m.wid) {
//    // m.spiral[y * m.wid + x] = k;
//    while (x < m.wid - b) {
//      m.spiral[y * m.len + x] = k;
//      k++;
//      x++;
//    }
//    x--;
//    while (y < m.len - b) {
//      m.spiral[y * m.wid + x] = k;
//      printf("%i * %i + %i : %i\n", y, m.wid, x, k);
//      k++;
//      y++;
//    }
//    y--;
//    x--;
//    while (x >= b) {
//      m.spiral[y * m.wid + x] = k;
//      k++;
//      x--;
//    }
//    b++;
//    x++;
//    y--;
//    while (y >= b) {
//      m.spiral[y * m.wid + x] = k;
//      k++;
//      y--;
//    }
//    y++;
//    x++;
//    break;
//  }
//}
