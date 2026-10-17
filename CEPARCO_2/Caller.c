
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define RUNS 30
#define TOLERANCE 1e-5

extern void vector_asm(float* arrA, float* arrB, float* arrC, float* arrD, int n);
extern void vector_xmm(float* arrA, float* arrB, float* arrC, float* arrD, int n);
extern void vector_ymm(float* arrA, float* arrB, float* arrC, float* arrD, int n);

typedef void (*Kernel)(float*, float*, float*, float*, int);

void vector_c(float* arrA, float* arrB, float* arrC, float* arrD, int n) {
    for (int i = 0; i < n; i++) {
        arrA[i] = arrB[i] + arrC[i] * arrD[i];
    }
}

double get_time(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER frequency) {
    return ((double)(end.QuadPart - start.QuadPart) / frequency.QuadPart) * 1000.0;
}

double benchmark_kernel(Kernel kernel, float* arrA, float* arrB,
    float* arrC, float* arrD, int n, LARGE_INTEGER frequency) {

    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double total_time = 0.0;

    kernel(arrA, arrB, arrC, arrD, n);

    for (int i = 0; i < RUNS; i++) {
        QueryPerformanceCounter(&start);
        kernel(arrA, arrB, arrC, arrD, n);
        QueryPerformanceCounter(&end);

        total_time += get_time(start, end, frequency);
    }

    return total_time / RUNS;
}

int check_correctness(float* reference, float* result, int n) {
    for (int i = 0; i < n; i++) {
        if (!isfinite(reference[i]) || !isfinite(result[i])) {
            return 0;
        }

        float difference = fabsf(reference[i] - result[i]);
        float allowed_error = TOLERANCE * (1.0f + fabsf(reference[i]));

        if (difference > allowed_error) {
            return 0;
        }
    }

    return 1;
}

void display_results(const char* name, float* arrA, int n,
    double elapsed, int correctness) {

    int count = n < 5 ? n : 5;

    printf("%s\n", name);
    printf("Average time: %.6f ms\n", elapsed);
    printf("Correctness: %s\n", correctness ? "PASS" : "FAIL");

    printf("First %d elements: ", count);
    for (int i = 0; i < count; i++) {
        printf("%.6f ", arrA[i]);
    }

    printf("\nLast %d elements: ", count);
    for (int i = n - count; i < n; i++) {
        printf("%.6f ", arrA[i]);
    }

    printf("\n\n");
}

int main(int argc, char* argv[]) {
    int n = 13;

    if (argc > 1) {
        char* end;
        long parsed = strtol(argv[1], &end, 10);

        if (*argv[1] == '\0' || *end != '\0' ||
            parsed < 1 || parsed >(1L << 30)) {
            printf("Invalid vector size.\n");
            return 1;
        }

        n = (int)parsed;
    }

    size_t bytes = (size_t)n * sizeof(float);

    float* arrA_c = (float*)malloc(bytes);
    float* arrA_asm = (float*)malloc(bytes);
    float* arrA_xmm = (float*)malloc(bytes);
    float* arrA_ymm = (float*)malloc(bytes);
    float* arrB = (float*)malloc(bytes);
    float* arrC = (float*)malloc(bytes);
    float* arrD = (float*)malloc(bytes);

    if (arrA_c == NULL || arrA_asm == NULL || arrA_xmm == NULL ||
        arrA_ymm == NULL || arrB == NULL || arrC == NULL || arrD == NULL) {

        printf("Memory allocation failed for n = %d.\n", n);

        free(arrA_c);
        free(arrA_asm);
        free(arrA_xmm);
        free(arrA_ymm);
        free(arrB);
        free(arrC);
        free(arrD);

        return 1;
    }

    printf("Vector size: %d\n", n);
    printf("Benchmark runs: %d per implementation\n\n", RUNS);

    for (int i = 0; i < n; i++) {
        arrB[i] = (float)sin(i * 0.001);
        arrC[i] = (float)cos(i * 0.002);
        arrD[i] = (float)sin(i * 0.003);
    }

    vector_c(arrA_c, arrB, arrC, arrD, n);

    LARGE_INTEGER frequency;

    if (!QueryPerformanceFrequency(&frequency)) {
        printf("High-resolution timer is unavailable.\n");

        free(arrA_c);
        free(arrA_asm);
        free(arrA_xmm);
        free(arrA_ymm);
        free(arrB);
        free(arrC);
        free(arrD);

        return 1;
    }

    double time_c = benchmark_kernel(
        vector_c, arrA_c, arrB, arrC, arrD, n, frequency);

    double time_asm = benchmark_kernel(
        vector_asm, arrA_asm, arrB, arrC, arrD, n, frequency);

    double time_xmm = benchmark_kernel(
        vector_xmm, arrA_xmm, arrB, arrC, arrD, n, frequency);

    double time_ymm = benchmark_kernel(
        vector_ymm, arrA_ymm, arrB, arrC, arrD, n, frequency);

    int correct_asm = check_correctness(arrA_c, arrA_asm, n);
    int correct_xmm = check_correctness(arrA_c, arrA_xmm, n);
    int correct_ymm = check_correctness(arrA_c, arrA_ymm, n);

    display_results("C implementation", arrA_c, n, time_c, 1);
    display_results("Scalar ASM implementation", arrA_asm, n, time_asm, correct_asm);
    display_results("XMM implementation", arrA_xmm, n, time_xmm, correct_xmm);
    display_results("YMM implementation", arrA_ymm, n, time_ymm, correct_ymm);

    printf("Speedups relative to C:\n");

    if (time_asm > 0.0) {
        printf("Scalar ASM: %.3fx\n", time_c / time_asm);
    }

    if (time_xmm > 0.0) {
        printf("XMM: %.3fx\n", time_c / time_xmm);
    }

    if (time_ymm > 0.0) {
        printf("YMM: %.3fx\n", time_c / time_ymm);
    }

    free(arrA_c);
    free(arrA_asm);
    free(arrA_xmm);
    free(arrA_ymm);
    free(arrB);
    free(arrC);
    free(arrD);

    return (correct_asm && correct_xmm && correct_ymm) ? 0 : 1;
}