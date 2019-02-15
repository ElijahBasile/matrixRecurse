// Program Purpose: finding the maximum value of a matrix recursively

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int* buildNewMatrix(int);
int setMatrixSize();
void displayMatrix(int*,int);
int* findMax(int*, int);
int* findRowCol(int* , int* ,int);

// skeletal structure for code exists in the main

int main() {

	// set the program's seed to the current time
	srand(time(0));

	//required command that makes the scanf and printf work properly
	setvbuf(stdout,  NULL,  _IONBF,  0);

	//set the matrix sideLength

	int sideLength = setMatrixSize();

	// initialize a new matrix

	int* matrix = buildNewMatrix(sideLength);

	// start the timer, find the maximum of the matrix, end the timer

	int timeTaken = clock();

	// Find the maximum number in the matrix

	int* max = findMax(matrix, sideLength);

	int* rowcol = findRowCol(max,matrix,sideLength);

	// end timer

	timeTaken = clock() - timeTaken;

	// report data to user

	printf("Maximum Number in Matrix: %d :: ", *max);
	printf("Row: %d Column: %d\n",*rowcol, *(rowcol+1));
	printf("Time taken to get result: %d milliseconds\n", timeTaken);

	// free memory

	free(matrix);
	free(rowcol);

	return 0;
}

// this function allocates the number of memory for the matrix and initializes each index

int* buildNewMatrix(int sideLength) {
	int* matrix;

	if (!(matrix = malloc(pow(sideLength,2)*sizeof(int*)))) {
		printf("Not enough memory available to create matrix. \n");
		exit(0);
	}
	for (int i = 0; i < pow(sideLength,2); i++) {
		*(matrix+i) = rand();
	}

	displayMatrix(matrix,sideLength);


	return matrix;
}

// this function allows the user to set the matrix sideLength (that must be a power of 2)

int setMatrixSize() {
	int keepGoing = 0;
	int sideLength = 0;

	while (!keepGoing) {
		printf("Please enter the side length of the matrix you want.\n");
		printf("Ensure that it is an integer power of 2: ");

		fflush(stdin);
		scanf("%d",&sideLength);

		int test = pow(2,(int)(.001+log(sideLength)/log(2)));

		if (test==sideLength) {
			keepGoing = 1;
		} else {
			printf("I'm sorry, that number is not a power of 2. Please try again.\n");
		}
	} //end while

	printf("\n\n");

	return sideLength;
}

// this prints out the matrix to the user to see

void displayMatrix(int* matrix, int sideLength) {

	printf(" 		");
	for(int i = 1 ; i <= sideLength ; i++) {
		printf("%d	",i);
	}

	printf("\n");

	for (int i = 1; i <= sideLength ; i++) {
		printf("%d	|	",i);
		for (int j = 0; j < sideLength ; matrix++,j++) {
			printf("%d	",*matrix);
		}
		printf("|\n");
	}
	printf("\n\n");

	return;
}


// findMax function: It's goal is to recursively search the matrix for the maximum value by consistently returning
// the local maximum of four values

int* findMax(int* matrix, int sideLength) {
	int *a,*b,*c,*d;
	int *max1,*max2;

	if (sideLength == 1)
		return matrix;
	else {

		// splitting the matrix into four blocks

		a = findMax(matrix,sideLength/2);
		b = findMax(matrix+sideLength*sideLength/4,sideLength/2);
		c = findMax(matrix+2*sideLength*sideLength/4,sideLength/2);
		d = findMax(matrix+3*sideLength*sideLength/4,sideLength/2);

		// computing the max out of 4 blocks and returning the maximum value

		if (*a > *b)
			max1 = a;
		else
			max1 = b;
		if (*c > *d)
			max2 = c;
		else
			max2 = d;
		if (*max1 > *max2)
			return max1;
		else
			return max2;
	}
}

int* findRowCol(int* max, int* matrix, int sideLength) {
	int* rowcol = (int*)malloc(2*sizeof(int));
	int i = 1;

	int difference = (max - matrix);

	while ((difference -= sideLength) >= 0) {
		i++;
	}
	difference += sideLength;

	*rowcol = i;
	rowcol++;
	*rowcol = 1+difference;
	rowcol--;

	return rowcol;
}














