#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

extern void square_asm(float* arr, int n);
extern void square_xmm(float* arr, int n);
extern void square_ymm(float* arr, int n);

void square_c(float* arr, int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = arr[i] * arr[i];
	}
}

double get_time(LARGE_INTEGER start, LARGE_INTEGER end,
	LARGE_INTEGER frequency)
{
	return (double)(end.QuadPart - start.QuadPart)
		/ frequency.QuadPart;
}

int main() {
	int n = 16777216;
	float* arr1 = (float*)malloc(n * sizeof(float));
	float* arr2 = (float*)malloc(n * sizeof(float));
	float* arr3 = (float*)malloc(n * sizeof(float));
	float* arr4 = (float*)malloc(n * sizeof(float));

	if (arr1 == NULL || arr2 == NULL || arr3 == NULL || arr4 == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

	for (int i = 0; i < n; i++) {
		arr1[i] = (float)i;
		arr2[i] = (float)i;
		arr3[i] = (float)i;
		arr4[i] = (float)i;
	}

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	square_c(arr1, n);
	QueryPerformanceCounter(&end);
	double time_c = get_time(start, end, frequency);
	printf("Time taken by C implementation: %f seconds\n", time_c);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr1[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr1[n-1-i]);
	}
	printf("\n\n");

	QueryPerformanceCounter(&start);
	square_asm(arr2, n);
	QueryPerformanceCounter(&end);
	double time_asm = get_time(start, end, frequency);
	printf("Time taken by ASM implementation: %f seconds\n", time_asm);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr2[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr2[n - 1 - i]);
	}
	printf("\n\n");

	QueryPerformanceCounter(&start);
	square_xmm(arr3, n);
	QueryPerformanceCounter(&end);
	double time_xmm = get_time(start, end, frequency);
	printf("Time taken by XMM implementation: %f seconds\n", time_xmm);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr3[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr3[n - 1 - i]);
	}
	printf("\n\n");

	QueryPerformanceCounter(&start);
	square_ymm(arr4, n);
	QueryPerformanceCounter(&end);
	double time_ymm = get_time(start, end, frequency);
	printf("Time taken by YMM implementation: %f seconds\n", time_ymm);
	printf("First 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr4[i]);
	}
	printf("\n");
	printf("Last 5 elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%f ", arr4[n - 1 - i]);
	}
	printf("\n\n");

	int errors_asm = 0;
	int errors_xmm = 0;
	int errors_ymm = 0;
	for (int i = 0; i < n; i++) {
		if (fabs(arr1[i] - arr2[i]) > 1e-5)
			errors_asm++;

		if (fabs(arr1[i] - arr3[i]) > 1e-5)
			errors_xmm++;

		if (fabs(arr1[i] - arr4[i]) > 1e-5)
			errors_ymm++;
	}
	printf("ASM error count: %d\n", errors_asm);
	printf("XMM error count: %d\n", errors_xmm);
	printf("YMM error count: %d\n", errors_ymm);

	free(arr1);
	free(arr2);
	free(arr3);
	free(arr4);

	return 0;
}