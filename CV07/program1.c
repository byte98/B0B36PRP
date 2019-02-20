#include <stdio.h>
#include<stdlib.h>

void print_array(float*, int);
float array_avg(float*, int);

int main(int argc, char* argv[])
{
	float array[] = { 1.0, 2.0, 3.0 };
	print_array(array, sizeof(array) / sizeof(float));
	printf("%f\n", array_avg(array, sizeof(array) / sizeof(float)));

	int *ui;
	/* vytvoreni dynamicke promenne */
	if ((ui = (int *)malloc(sizeof(*ui))) == NULL) { /* zadost o prideleni pameti velikost typu int */
		printf("Nedostatek pameti.\n");
		return 1; /* pøípadnì pro ukonceni programu exit(1); */
	}
	free(*ui);

	return 0;
}

void print_array(float* arr, int arr_len)
{
	for (int i = 0; i < arr_len; i++)
	{
		printf(" %f ", arr[i]);
	}
	printf("\n");
}

float array_avg(float* arr, int arr_len)
{
	float sum = 0;
	for (int i = 0; i < arr_len; i++)
	{
		sum += arr[i];
	}
	return (sum / arr_len);
}