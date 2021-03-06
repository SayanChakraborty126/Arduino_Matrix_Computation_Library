/*
 *  MatrixMath.h Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from 
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 */

#ifndef MatrixMath1_h
#define MatrixMath1_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MatrixMath1
{
public:
	//MatrixMath1();
	void Print(double* A, int m, int n, String label,int precision);
	void Copy(double* A, int n, int m, double* B);
	void Multiply(double* A, double* B, int m, int p, int n, double* C);
	void Add(double* A, double* B, int m, int n, double* C);
	void Subtract(double* A, double* B, int m, int n, double* C);
	void Transpose(double* A, int m, int n, double* C);
	void Scale(double* A, int m, int n, double k);
	int Invert(double* A, int n);
	int Max(double* A,int m,int n,int maximum );
	void Identity(int m, int n,double* A);
};

extern MatrixMath1 Matrix1;
#endif
