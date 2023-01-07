/*
Nestor Gomez
Carnegie Mellon University
24-780-B Engineering Computation
PS 11: Matrices

Due: Wed, Nov. 30, 2022
     Do or die, finished or not, participation is what really matters!

*/

#include <iostream>
#include <chrono>
#include "ps11_matrix_ng27.h"


int main() {
	using namespace std;
	bool run4 = false;
	bool run500 = true;
	bool run5000 = false;  // don't do this until the end

	cout << " MATRIX TESTER " << endl;

	if (run4) {
		Matrix2D<float, 4, 4> mat4;

		mat4.readFile("matrix4x4.txt");

		cout << "Matrix 4x4 read:" << endl;
		mat4.print();

		Matrix2D<float, 4, 4> mat4Other(mat4);  // using copy constructor
		Matrix2D<float, 4, 4> mat4Again = mat4;  // using copy constructor
		Matrix2D<float, 4, 4> *mat4Last = new Matrix2D<float, 4, 4>(mat4);  // using copy constructor

		auto begin = std::chrono::high_resolution_clock::now();

		mat4.transpose();

		double timeElapsed = chrono::duration_cast<chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - begin).count() / 1e9;

		cout << "Matrix 4x4 transposed:" << endl;
		mat4.print();
		cout << "Transpose of 4x4: elapsed " << timeElapsed << " sec." << endl;

		// deep copy test
		Matrix2D<float, 4, 4> mat4Transp;
		mat4Transp = mat4; // copy the transposed matrix
		mat4.transpose();  // set it back to how it was

		cout << "COPY of Matrix 4x4 transposed:" << endl;
		mat4Transp.print();

		// multiplying
		Matrix2D<float, 4, 4> result4;
		begin = std::chrono::high_resolution_clock::now();

		mat4.matrixMultiply(mat4, result4);

		timeElapsed = chrono::duration_cast<chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - begin).count() / 1e9;

		cout << "Matrix multiply result (squaring):" << endl;
		result4.print();
		cout << "Squaring of 4x4: elapsed " << timeElapsed << " sec." << endl;
	}

	// ==================================

	if (run500) {
		Matrix2D<double, 500, 500> mat500;
		mat500.readFile("matrix500x500.txt");

		// multiplying
		Matrix2D<double, 500, 500> result500;
		auto begin2 = std::chrono::high_resolution_clock::now();

		mat500.matrixMultiply(mat500, result500);

		double timeElapsed2 = chrono::duration_cast<chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - begin2).count() / 1e9;

		cout << "\nMatrix multiply result (squaring):" << endl;
		result500.print(cout, 10);
		cout << "Squaring of 500x500: elapsed " << timeElapsed2 << " sec." << endl;

		begin2 = std::chrono::high_resolution_clock::now();

		mat500.matrixMultiplyParallel(mat500, result500);

		timeElapsed2 = chrono::duration_cast<chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - begin2).count() / 1e9;

		cout << "\nMatrix multiply PARALLEL result (squaring):" << endl;
		result500.print(cout, 10);
		cout << "Squaring of 500x500 PARALLEL: elapsed " << timeElapsed2 << " sec." << endl;
	}

	// =======================================================
	
	if (run5000) {  // set to "true" to run, "false" to skip 
		Matrix2D<double, 5000, 5000> mat5000;
		mat5000.readFile("matrix5000x5000.txt");
		Matrix2D<double, 5000, 5000> result5000;

		auto begin3 = std::chrono::high_resolution_clock::now();

		mat5000.matrixMultiplyParallel(mat5000, result5000);

		double timeElapsed3 = chrono::duration_cast<chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - begin3).count() / 1e9;

		cout << "\nMatrix multiply PARALLEL result (squaring):" << endl;
		result5000.print(cout, 10);
		cout << "Squaring of 5000x5000 PARALLEL: elapsed " << timeElapsed3 << " sec." << endl;

	}
}
