#include <stdlib.h>
#include <time.h>
#include <stdio.h>


void m_fill_random(int **A, int n, int m, unsigned int seed);
void m_print(int **A, int n, int m, int direct);
void m_antidiag_sort(int **A, int n, int m);
int min(int a, int b);


int main() 
{
  int N, M;
  printf("\n\n");
  printf("Enter number of matrix rows: "); scanf("%ud", &N);            // Считывани с клавиатуры размеров матрицы
  printf("Enter number of matrix columns: "); scanf("%ud", &M);
  printf("\n\n");

  int **A = (int**) malloc(N*sizeof(int*));                             // Выделение памяти под матрицу
  for(int i=0; i<N; i++) { A[i] = (int*) malloc(M*sizeof(int)); }

  m_fill_random(A, N, M, time(NULL));                                   // Заполнение матрицы рандомными числами

  printf("INITIAL matrix:\n");                                          // Печать исходной матрицы в двух видах
  m_print(A, N, M, 0);
  printf("INITIAL matrix (antidiagonals):\n");
  m_print(A, N, M, -1);

  m_antidiag_sort(A, N, M);                                             // Сортировка матрицы

  printf("SORTED matrix (antidiagonals):\n");                           // Печать отсортированной матрицы в двух видах
  m_print(A, N, M, -1);
  printf("SORTED matrix:\n");
  m_print(A, N, M, 0);

  for(int i = 0; i<N; i++) { free(A[i]); }                              // Отчистка памяти, выделенной под матрицу
  free(A);

  return 0;
}

///////////////////////////////////////////////////////////////////

int min(int a, int b) 
{
  return a<b ? a : b;
}

// функция для заполнения матрицы рандомными числами, A - указатель на матрицу, n - число строк, m - число столбцов, seed - число для генерации псевдослучайных чисел
void m_fill_random(int **A, int n, int m, unsigned int seed) 
{
  srand(seed);
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      A[i][j] = rand()%201-100;
    }
  }
}

// функция для вывода (печати) матрицы на экран. A - указатель на матрицу, n - число строк, m - число столбцов, direct - способ печати: если direct=0, то печать построчная, если direct=-1, то печать идет по диагоналям параллельным побочной диагонали
void m_print(int **A, int n, int m, int direct) 
{
  switch(direct) {

    case 0:
      for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
          printf("%4d\t", A[i][j]);
        }
        printf("\n");
      }
      printf("\n");
    break;

    case -1:
      for(int k=0; k<n+m-1; k++) {                                // Цикл по всем диагоналям, параллельным побочной, всего их m+n-1
        int min_kn = min(k,n-1), min_km = min(k,m-1);
        for(int i=0 ; i < min_kn + min_km - k + 1; i++) {         // Цикл по элементам диагонали, всего их min(k,n)+min(k,m)-k+1
            printf("%4d\t", A[min_kn-i][k-min_kn+i]);
        }
        printf("\n");
      }
      printf("\n");
    break;

  }
}

// функция выполняющая сортировку диагоналей, параллельных побочной по возрастанию.  A - указатель на матрицу, n - число строк, m - число столбцов
void m_antidiag_sort(int **A, int n, int m) {

  int j, min_kn, min_km, cur, irow, icol;

  for(int k=0; k<n+m-1; k++) {                                    // Цикл по всем диагоналям, параллельным побочной, всего их m+n-1
    min_kn = min(k,n-1);
    min_km = min(k,m-1);

    for(int i=1 ; i < min_kn + min_km - k + 1; i++) {             // Цикл по элементам диагонали, всего их min(k,n)+min(k,m)-k+1

      // СОРТИРОВКА МЕТОДОМ ВСТАВКИ
      j = i;
      irow = min_kn-j;                                            // Координаты текущего элемента
      icol = k-min_kn+j;
      cur = A[irow][icol];

      while(j>0 && A[irow+1][icol-1] > cur) {
        A[irow][icol] = A[irow+1][icol-1];
        j--;
        irow = min_kn-j;
        icol = k-min_kn+j;
      }

      A[irow][icol] = cur;

    }

  }
}

