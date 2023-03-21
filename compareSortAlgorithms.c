#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int extraMemoryAllocated;
void merge(int pData[], int l, int m, int r, int* temp) {
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (pData[i] <= pData[j]) {
            temp[k] = pData[i];
            i++;
        }
        else {
            temp[k] = pData[j];
            j++;
        }
        k++;
        extraMemoryAllocated += sizeof(int);
    }
    while (i <= m) {
        temp[k] = pData[i];
        i++;
        k++;
        extraMemoryAllocated += sizeof(int);
    }
    while (j <= r) {
        temp[k] = pData[j];
        j++;
        k++;
        extraMemoryAllocated += sizeof(int);
    }
    for (i = l, k = 0; i <= r; i++, k++) {
        pData[i] = temp[k];
    }
}

void mergeSortHelper(int pData[], int l, int r, int* temp) {
    if (l < r) {
        int i = l + (r - l) / 2;
        mergeSortHelper(pData, l, i, temp);
        mergeSortHelper(pData, i + 1, r, temp);
        merge(pData, l, i, r, temp);
    }
}

void mergeSort(int pData[], int l, int r) {
    int* tmp = (int*)malloc(sizeof(int) * (r - l + 1));
    extraMemoryAllocated += sizeof(int) * (r - l + 1);
    mergeSortHelper(pData, l, r, tmp);
    free(tmp);
}

void insertionSort(int* pData, int n) {
    int i, j, keySort;
    for (i = 1; i < n; i++) {
        keySort = pData[i];
        j = i - 1;
        while (j >= 0 && pData[j] > keySort) {
            pData[j + 1] = pData[j];
            j--;
            extraMemoryAllocated += sizeof(int);
        }
        pData[j + 1] = keySort;
    }
}

void bubbleSort(int* pData, int n) {
    int i, j, tmp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pData[j] > pData[j + 1]) {
                tmp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = tmp;
                extraMemoryAllocated += sizeof(int);
            }
        }
    }
}

void selectionSort(int* pData, int n) {
    int i, j, idx;
    for (i = 0; i < n - 1; i++) {
        idx = i;
        for (j = i + 1; j < n; j++) {
            if (pData[j] < pData[idx]) {
                idx = j;
            }
        }
        int temp = pData[idx];
        pData[idx] = pData[i];
        pData[i] = temp;
        extraMemoryAllocated += sizeof(int);
    }
}

int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    *ppData = NULL;
    
    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        for (int i = 0; i < dataSz; ++i)
        {
            fscanf(inFile, "%d", &(*ppData)[i]);
        }
        fclose(inFile);
    }
    
    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}


int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}