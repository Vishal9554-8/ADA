#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 512   // Maximum matrix size (2^9)

// Function to generate random square matrix of order n
void generateMatrix(int n, int A[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = rand() % 10;  // random values 0–9
}

// Function to print matrix (for testing small n)
void printMatrix(int n, int A[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

// ---------- 1️⃣ ITERATIVE MULTIPLICATION ----------
void iterativeMultiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// ---------- 2️⃣ DIVIDE & CONQUER MULTIPLICATION ----------
void addMatrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void divideConquerMultiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int temp1[k][k], temp2[k][k];

    // Divide matrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Compute submatrices recursively
    // C11 = A11*B11 + A12*B21
    divideConquerMultiply(k, A11, B11, temp1);
    divideConquerMultiply(k, A12, B21, temp2);
    addMatrix(k, temp1, temp2, C11);

    // C12 = A11*B12 + A12*B22
    divideConquerMultiply(k, A11, B12, temp1);
    divideConquerMultiply(k, A12, B22, temp2);
    addMatrix(k, temp1, temp2, C12);

    // C21 = A21*B11 + A22*B21
    divideConquerMultiply(k, A21, B11, temp1);
    divideConquerMultiply(k, A22, B21, temp2);
    addMatrix(k, temp1, temp2, C21);

    // C22 = A21*B12 + A22*B22
    divideConquerMultiply(k, A21, B12, temp1);
    divideConquerMultiply(k, A22, B22, temp2);
    addMatrix(k, temp1, temp2, C22);

    // Combine results
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

// ---------- 3️⃣ STRASSEN'S ALGORITHM ----------
void strassenMultiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int temp1[k][k], temp2[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];

    // Divide A and B
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Strassen’s 7 multiplications
    addMatrix(k, A11, A22, temp1);
    addMatrix(k, B11, B22, temp2);
    strassenMultiply(k, temp1, temp2, M1);

    addMatrix(k, A21, A22, temp1);
    strassenMultiply(k, temp1, B11, M2);

    subMatrix(k, B12, B22, temp2);
    strassenMultiply(k, A11, temp2, M3);

    subMatrix(k, B21, B11, temp2);
    strassenMultiply(k, A22, temp2, M4);

    addMatrix(k, A11, A12, temp1);
    strassenMultiply(k, temp1, B22, M5);

    subMatrix(k, A21, A11, temp1);
    addMatrix(k, B11, B12, temp2);
    strassenMultiply(k, temp1, temp2, M6);

    subMatrix(k, A12, A22, temp1);
    addMatrix(k, B21, B22, temp2);
    strassenMultiply(k, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7
    addMatrix(k, M1, M4, temp1);
    subMatrix(k, temp1, M5, temp2);
    addMatrix(k, temp2, M7, C11);

    // C12 = M3 + M5
    addMatrix(k, M3, M5, C12);

    // C21 = M2 + M4
    addMatrix(k, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    subMatrix(k, M1, M2, temp1);
    addMatrix(k, temp1, M3, temp2);
    addMatrix(k, temp2, M6, C22);

    // Combine
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

// ---------- MAIN FUNCTION ----------
int main() {
    srand(time(NULL));

    int n;
    printf("Enter power n (matrix order = 2^n): ");
    scanf("%d", &n);
    int size = pow(2, n);

    int A[size][size], B[size][size], C[size][size];

    generateMatrix(size, A);
    generateMatrix(size, B);

    clock_t start, end;

    // Iterative
    start = clock();
    iterativeMultiply(size, A, B, C);
    end = clock();
    double time_iter = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nIterative Method Time: %lf sec", time_iter);

    // Divide & Conquer
    start = clock();
    divideConquerMultiply(size, A, B, C);
    end = clock();
    double time_divide = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nDivide & Conquer Method Time: %lf sec", time_divide);

    // Strassen
    start = clock();
    strassenMultiply(size, A, B, C);
    end = clock();
    double time_strassen = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nStrassen’s Method Time: %lf sec", time_strassen);

    printf("\n---------------------------------------------\n");
    printf("Matrix Size: %d x %d\n", size, size);
    printf("Iterative O(n^3) | Divide & Conquer O(n^3) | Strassen O(n^2.81)\n");
    printf("---------------------------------------------\n");

    return 0;
}
