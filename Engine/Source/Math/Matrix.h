#pragma once

/* made by Yavuz Büyükadalı */

#ifndef FR_MATH_MATRIX
#define FR_MATH_MATRIX

#include "pch.h"

#define MATRIX_SIZE 4

namespace fr {
	class Matrix {
	private:
		float matrix[MATRIX_SIZE][MATRIX_SIZE];
	public:
		Matrix() {
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					matrix[x][y] = 0.0f;
				}
			}
		}

		Matrix(float e00, float e01, float e02, float e03,
			   float e10, float e11, float e12, float e13,
			   float e20, float e21, float e22, float e23,
			   float e30, float e31, float e32, float e33) {
			matrix[0][0] = e00; matrix[0][1] = e01; matrix[0][2] = e02; matrix[0][3] = e03;
			matrix[1][0] = e10; matrix[1][1] = e11; matrix[1][2] = e12; matrix[1][3] = e13;
			matrix[2][0] = e20; matrix[2][1] = e21; matrix[2][2] = e22; matrix[2][3] = e23; 
			matrix[3][0] = e30; matrix[3][1] = e31; matrix[3][2] = e32; matrix[3][3] = e33;
		}

		void Set(int x, int y, float number) {
			matrix[x][y] = number;
		}

		float Get(int x, int y) {
			return matrix[x][y];
		}

		const float Get(int x, int y) const {
			return matrix[x][y];
		}

		float* ToPointer() {
			return &matrix[0][0];
		}

		const float* ToPointer() const {
			return &matrix[0][0];
		}

		void Set(int index, float number) {
			ToPointer()[index] = number;
		}

		float Get(int index) {
			return ToPointer()[index];
		}

		const float Get(int index) const {
			return ToPointer()[index];
		}

		float operator[](int index) {
			return ToPointer()[index];
		}

		const float operator[](int index) const {
			return ToPointer()[index];
		}
	};
}

#endif