

#include "MatrixMath1.h"

#define NR_END 1

MatrixMath1 Matrix1;			// Pre-instantiate

// Matrix Printing Routine
// Uses tabs to separate numbers under assumption printed double width won't cause problems
void MatrixMath1::Print(double* A, int m, int n, String label, int precision){
	// A = input matrix (m x n)
	int i,j;
	Serial.println();
	Serial.println(label);
	for (i=0; i<m; i++){
		for (j=0;j<n;j++){
			Serial.print(A[n*i+j], precision);
			Serial.print(" ");
		}
		Serial.println();
	}
	
}

void MatrixMath1::Copy(double* A, int n, int m, double* B)
{
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			B[n*i+j] = A[n*i+j];
		}
}

//highest number in an entered matrix
float MatrixMath1::Maximum(double* A, int m, int n, float maximum1)
{
	/*int i=0;
	int j=0;
	int maximum;
	int k;
    k=A[n*i+j];
	maximum = max(k,A[n*(i+1)+(j)]);
	maximum1=max(maximum,A[n*(i+2)+(j)]);
	return maximum1;*/	
	maximum1=0;
	 for(int i=0; i<m ; i++)
    {
    for(int j=0; j<n; j++)
    {
       (maximum1)=max(maximum1,abs(A[n*i+j]));
    }
   }
   return abs(maximum1);
	
	
	
    
    
}

void MatrixMath1::Identity(int m, int n,double* A)
{
	
	
	int i, j;
	for (i=0;i<m;i++)
	{
	
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
				A[n*i+j] = 1.0f;
			}
			else
			{
				A[n*i+j] =0;
			}
			
		}
	
	}
}



//Matrix Multiplication Routine
// C = A*B
void MatrixMath1::Multiply(double* A, double* B, int m, int p, int n, double* C)
{
	// A = input matrix (m x p)
	// B = input matrix (p x n)
	// m = number of rows in A
	// p = number of columns in A = number of rows in B
	// n = number of columns in B
	// C = output matrix = A*B (m x n)
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			C[n*i+j]=0;
			for (k=0;k<p;k++)
				C[n*i+j]= C[n*i+j]+A[p*i+k]*B[n*k+j];
		}
}


//Matrix Addition Routine
void MatrixMath1::Add(double* A, double* B, int m, int n, double* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A+B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]+B[n*i+j];
}


//Matrix Subtraction Routine
void MatrixMath1::Subtract(double* A, double* B, int m, int n, double* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A-B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]-B[n*i+j];
}


//Matrix Transpose Routine
void MatrixMath1::Transpose(double* A, int m, int n, double* C)
{
	// A = input matrix (m x n)
	// m = number of rows in A
	// n = number of columns in A
	// C = output matrix = the transpose of A (n x m)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[m*j+i]=A[n*i+j];
}

void MatrixMath1::Scale(double* A, int m, int n, double k)
{
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			A[n*i+j] = A[n*i+j]*k;
}


//Matrix Inversion Routine
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in 
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
int MatrixMath1::Invert(double* A, int n)
{
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	double tmp;		// used for finding max value and making column swaps

	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs(A[i*n+k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(A[i*n+k]);
				pivrow = i;
			}
		}

		// check for singular matrix
		if (A[pivrow*n+k] == 0.0f)
		{
			Serial.println("Inversion failed due to singular matrix");
			return 0;
		}

		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k*n+j];
				A[k*n+j] = A[pivrow*n+j];
				A[pivrow*n+j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)

		tmp = 1.0f/A[k*n+k];	// invert pivot element
		A[k*n+k] = 1.0f;		// This element of input matrix becomes result matrix

		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k*n+j] = A[k*n+j]*tmp;
		}

		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i*n+k];
				A[i*n+k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i*n+j] = A[i*n+j] - A[k*n+j]*tmp;
				}
			}
		}
	}

	// Done, now need to undo pivot row swaps by doing column swaps in reverse order
	for (k = n-1; k >= 0; k--)
	{
		if (pivrows[k] != k)
		{
			for (i = 0; i < n; i++)
			{
				tmp = A[i*n+k];
				A[i*n+k] = A[i*n+pivrows[k]];
				A[i*n+pivrows[k]] = tmp;
			}
		}
	}
	return 1;
	
}

