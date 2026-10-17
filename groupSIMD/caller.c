#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

extern void vector_asm(float* arrA, float* arrB, float* arrC, float* arrD, int n);
extern void vector_xmm(float* arrA, float* arrB, float* arrC, float* arrD, int n);
extern void vector_ymm(float* arrA, float* arrB, float* arrC, float* arrD, int n);

void vector_c(float* arrA, const float* arrB, const float* arrC, const float* arrD, int n) {
	for (int i = 0; i < n; i++) {
		arrA[i] = arrB[i] + arrC[i] * arrD[i];
	}
}

double get_time(LARGE_INTEGER start, LARGE_INTEGER end,
	LARGE_INTEGER frequency)
{
	return (double)(end.QuadPart - start.QuadPart)
		/ frequency.QuadPart;
}

int main() {
	int n = 13;
	float* arrA_c = (float*)malloc(n * sizeof(float));
	float* arrA_asm = (float*)malloc(n * sizeof(float));
	float* arrA_xmm = (float*)malloc(n * sizeof(float));
	float* arrA_ymm = (float*)malloc(n * sizeof(float));
	float* arrB = (float*)malloc(n * sizeof(float));
	float* arrC = (float*)malloc(n * sizeof(float));
	float* arrD = (float*)malloc(n * sizeof(float));

	if (arrA_c == NULL || arrA_asm == NULL || arrA_xmm == NULL || arrA_ymm == NULL || arrB == NULL || arrC == NULL || arrD == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

	for (int i = 0; i < n; i++) {
		arrB[i] = (float)sin(i * 0.001);
		arrC[i] = (float)cos(i * 0.002);
		arrD[i] = (float)sin(i * 0.003);
	}

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	vector_c(arrA_c, arrB, arrC, arrD, n);
	QueryPerformanceCounter(&end);
	double time_c = get_time(start, end, frequency);
	printf("Time taken by C implementation: %f seconds\n", time_c);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arrA_c[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 4; i >= 0; i--) {
		printf("%f ", arrA_c[n - 1 - i]);
	}
	printf("\n\n");
	
	QueryPerformanceCounter(&start);
	vector_asm(arrA_asm, arrB, arrC, arrD, n);
	QueryPerformanceCounter(&end);
	double time_asm = get_time(start, end, frequency);
	printf("Time taken by ASM implementation: %f seconds\n", time_asm);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arrA_asm[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 4; i >= 0; i--) {
		printf("%f ", arrA_asm[n - 1 - i]);
	}
	printf("\n\n");
	
	QueryPerformanceCounter(&start);
	vector_xmm(arrA_xmm, arrB, arrC, arrD, n);
	QueryPerformanceCounter(&end);
	double time_xmm = get_time(start, end, frequency);
	printf("Time taken by XMM implementation: %f seconds\n", time_xmm);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arrA_xmm[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 4; i >= 0; i--) {
		printf("%f ", arrA_xmm[n - 1 - i]);
	}
	printf("\n\n");
	
	QueryPerformanceCounter(&start);
	vector_ymm(arrA_ymm, arrB, arrC, arrD, n);
	QueryPerformanceCounter(&end);
	double time_ymm = get_time(start, end, frequency);
	printf("Time taken by YMM implementation: %f seconds\n", time_ymm);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arrA_ymm[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 4; i >= 0; i--) {
		printf("%f ", arrA_ymm[n - 1 - i]);
	}
	printf("\n\n");

	free(arrA_c);
	free(arrA_asm);
	free(arrA_xmm);
	free(arrA_ymm);
	free(arrB);
	free(arrC);
	free(arrD);

	return 0;
}