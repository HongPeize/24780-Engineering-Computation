#pragma once
#include <fstream>
#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>
#include <iomanip>

template <class T, const int NR, const int NC>
class Matrix2D {
private:

	// T content[NR][NC];  // not what I want because I need dynamic allocation on heap
	T* content = nullptr;  // will use NC to get the 2D location
public:
	// Class constructor and destructor
	Matrix2D() {
		// allocate space for array
        content = new T[NR * NC];
	};

	// copy constructor (copy all values from original to the one being created)
	Matrix2D(const Matrix2D<T, NR, NC>& original);

	~Matrix2D() {
		// delete/release all the memory
        delete [] content;
	};

	// Sets value at given location, rows and columns are numbered 1 to whatever
	// Use the following if row or col are out-of-range
	// ->> throw std::out_of_range("Bad matrix operation");
	void set(int row, int col, const T& incoming);

	// Gets value at given location, throwing error similar to set()
	const T& value(int row, int col) const;

	// Loads matrix data from the file given. Returns false if unable to read.
	bool readFile(const std::string& fileName);

	// Prints the whole array to output, defaulting to cout.
	// If positive limit is given, only the first printLimit rows and columns
	// are printed rather than whole matrix (useful for checking big matrices).
	void print(std::ostream& output = std::cout, int printLimit = -1) const;

	// assignment operator
	Matrix2D<T, NR, NC>& operator=(const Matrix2D<T, NR, NC>& original);

	// Transposes the matrix in place.
	void transpose();

	// multiply the matrix by a scalar
	void scalarMultiply(const T& factor);

	// Multiplies the matrix with otherMatrix and stores the result in the
	// resultMatrix. Note that otherMatrix is the right-hand operand (since matrix
	// multiplication is NOT commutative)
	void matrixMultiply(Matrix2D<T, NC, NR>& otherMatrix, Matrix2D <T, NR, NC>& resultMatrix,
		int startRow = 1, int endRow = NR, int startCol = 1, int endCol = NC);

	// similar to matrixMultiply, but uses multi-threading
	void matrixMultiplyParallel(Matrix2D<T, NC, NR>& otherMatrix,
		Matrix2D <T, NR, NR>& resultMatrix);

	// thread entry static function
public: static void threadEntry(Matrix2D<T, NR, NC>* thisPtr);

	  Matrix2D<T, NR, NC>* rightHandMatrixPtr;
	  Matrix2D<T, NR, NC>* resultMatrixPtr;
	  int numbThreads = 4;
	  int currThread;

	  // fast algorithms (not needed for PS11, but thought you'd like to have them for matrices in general)
	  // using method given in https://en.wikipedia.org/wiki/LU_decomposition
protected:
	bool decomposeLUP();
	T* decomposed = nullptr;
	int* permutation = nullptr;
	bool needToRecalcDecomposed;  // used to avoid having to decompose if it's already done

public: const T& determinant();
public: void invert();

};

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::set(int row, int col, const T& incoming)
{
	// matrices go from 1 to whatever
	// arrays go from zero to whatever
    if (1<= row && row<= NR && 1<=col && col <= NC)
        content[(row-1)*NC + (col-1)] = incoming;
    else
        throw std::out_of_range("Bad row or col number on set function");
}

template<class T, int NR, int NC>
inline const T& Matrix2D<T, NR, NC>::value(int row, int col) const
{
	// matrices go from 1 to whatever
	// arrays go from zero to whatever
    if (1<= row && row<= NR && 1<=col && col <= NC)
        return content[(row-1)*NC + (col-1)];
    else
        throw std::out_of_range("Bad row or col number on set function");
}

template<class T, int NR, int NC>
inline bool Matrix2D<T, NR, NC>::readFile(const std::string& fileName)
{
	using namespace std;

	ifstream inFile(fileName);
	if (inFile.is_open()) {
		for (int i = 0; i < NR; i++)
			for (int j = 0; j < NC; j++)
				inFile >> content[i * NC + j];
		inFile.close();
		return true;
	}
	else
		return false;
}

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::print(std::ostream& output, int printLimit) const
{
	using namespace std;

	int rowLimit = NR, colLimit = NC;
	if (printLimit > 0) {
		rowLimit = min(NR, printLimit);
		colLimit = min(NC, printLimit);
	}

	for (int i = 0; i < rowLimit; i++) {
		for (int j = 0; j < colLimit; j++) {
			output << setw(10) << setprecision(3) << content[i * NC + j] << " ";
		}
		output << endl;
	}
}

template<class T, int NR, int NC>
inline Matrix2D<T, NR, NC>::Matrix2D(const Matrix2D<T, NR, NC>& original)
{
	// copy all the member variables 
	if (content != nullptr)
        delete[] content;
	 // create new dynamic stuff
	content = new T[NR * NC];

	// copy into dynamic stuff using loop
	for (int i = 0; i < NR * NC; i++)
		content[i] = original.content[i];

	//for (int i = 1; i <= NR; i++) {
	//	for (int j = 1; j < +NC; j++) {
	//		set(i, j, original.get(i, j));
	//	}
	//}

	// only required for fast algorithms  (so leave it here)
	needToRecalcDecomposed = true;
}

template<class T, int NR, int NC>
inline Matrix2D<T, NR, NC>& Matrix2D<T, NR, NC>::operator=(const Matrix2D<T, NR, NC>& original) {
	// copy original matrix's content into this matrix's content using loop
    for (int i = 0; i < NR * NC; i++)
        content[i] = original.content[i];
    
	needToRecalcDecomposed = true;

	return *this;  // so we could do matA = matB = matC;
}

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::transpose()
{
	if (NR != NC)
		throw std::out_of_range("Cannot transponse a non-square matrix");
	else {
        for (int i = 0; i<NR; i++){
            for (int j = i+1; j<NC; j++){
                T temp = content[i * NC + j];
                content[i*NC +j] = content[j*NC + i];
                content[j*NC+i] = temp;
            }
        }
		// only required for fast algorithms (so leave it here)
		needToRecalcDecomposed = true;
	}
}

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::scalarMultiply(const T& factor)
{
	// only required for fast algorithms (so leave it here)
	needToRecalcDecomposed = true;
}

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::matrixMultiply(Matrix2D<T, NC, NR>& rightHandMatrix, Matrix2D<T, NR, NC>& resultMatrix,
	int startRow, int endRow, int startCol, int endCol)
{
    if (0<startRow && startRow <=endRow && endRow <=NR){
        if (0<startCol && startCol<=endCol && endCol <= NC){
            T tempSum;
            for (int i = startRow; i<=endRow; i++){
                for (int j = startCol; j<=endCol; j++){
                    tempSum = 0;
                    for (int k = 1; k<=NC; k++){
                        tempSum += value(i, k) * rightHandMatrix.value(k,j);
                    }
                    resultMatrix.set(i, j, tempSum);
                }
            }
        }
        else
            throw std::out_of_range("Bad column limits on matrix multiply");
    }
    else
        throw std::out_of_range("Bad row limits on matrix multiply");
}

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::matrixMultiplyParallel(Matrix2D<T, NC, NR>& otherMatrix, Matrix2D<T, NR, NR>& resultMatrix)
{
//start 4 threads (partition the matrix)
    int multiThreadCutoff = 10;
    if (NC<=multiThreadCutoff)
        matrixMultiply(otherMatrix, resultMatrix);
    else{
        int numbThreads = 4;
        currThread = 1;
        rightHandMatrixPtr = &otherMatrix;
        resultMatrixPtr = &resultMatrix;
        std::vector<std::thread> theThreads;
        theThreads.resize(numbThreads); //cannot push_back because threads cannot be copied
        int lastThread;
        for (int i = 0; i<numbThreads;i++){
            lastThread = currThread;
            std::thread aThread(Matrix2D<T, NR, NC>::threadEntry, this);
            theThreads[i].swap(aThread);
            //currThread++;
            while (lastThread == currThread);
        }
        for (int i = 0; i<numbThreads; i++){
            theThreads[i].join();
        }
    }
}

template<class T, int NR, int NC>
inline void Matrix2D<T, NR, NC>::threadEntry(Matrix2D<T, NR, NC>* thisPtr)
{
    switch (thisPtr->currThread) {
    case 1:
    thisPtr->currThread++;
    thisPtr->matrixMultiply(*(thisPtr->rightHandMatrixPtr), *(thisPtr->resultMatrixPtr), 1, NR / 2, 1, NC / 2);
    break;
    case 2:
    thisPtr->currThread++;
    thisPtr->matrixMultiply(*(thisPtr->rightHandMatrixPtr), *(thisPtr->resultMatrixPtr), 1, NR / 2, NC / 2 + 1, NC);
    break;
    case 3:
    thisPtr->currThread++;
    thisPtr->matrixMultiply(*(thisPtr->rightHandMatrixPtr), *(thisPtr->resultMatrixPtr), NR / 2 + 1, NR, 1, NC / 2);
    break;
    case 4:
    thisPtr->currThread++;
    thisPtr->matrixMultiply(*(thisPtr->rightHandMatrixPtr), *(thisPtr->resultMatrixPtr), NR / 2 + 1, NR, NC / 2 + 1, NC);
    break;
    }
}

template<class T, int NR, int NC>
bool Matrix2D<T, NR, NC>::decomposeLUP()
{
	// using method given in https://en.wikipedia.org/wiki/LU_decomposition
	// although the code given there required that you could copy a whole row of
	// a 2-D array in one assignment operation, so I changed that to a small loop
	int i, j, k, imax, temp;
	T maxA, absA, tempContent;

	// copy original content into decomposed
	if (decomposed == nullptr)
		decomposed = new T[NR * NC];

	for (i = 0; i < NR; i++)
		for (j = 0; j < NC; j++)
			decomposed[i * NC + j] = content[i * NC + j];

	// Unit permutation matrix, P[N] initialized with N
	if (permutation == nullptr)
		permutation = new int[NR + 1];  // last item is used to keep count of permutations (row swaps)
	for (i = 0; i <= NR; i++)
		permutation[i] = i;

	// perform Gausian elimination to create an equivalent version
	// of the matrix, decomposed so that the 

	for (i = 0; i < NR; i++) {  // for each row 

		// find row index of absmax of current column (=i) in lower triangle 
		maxA = 0.0;
		imax = i;
		for (k = i; k < NR; k++)
			if ((absA = fabs(decomposed[k * NC + i])) > maxA) {
				maxA = absA;
				imax = i;
			}

		if (maxA < 1e-20) {  //failure, matrix is degenerate (has all-zeros column)
			needToRecalcDecomposed = true;
			return false;
		}
		else {
			// switch the row that has the max with the current row
			// unless the current row is the one with the max
			if (imax != i) {
				//pivoting rows of decomposed (this swap rows i and imax)
				for (int j = 0; j < NC; j++) {
					std::swap(decomposed[i * NC + j], decomposed[imax * NC + j]);
				}

				// keep track of which rows were switched
				// this will be used to get inverse of original matrix
				std::swap(permutation[i], permutation[imax]);

				//counting pivots starting from NR 
				// (will be used to get final sign of determinant)
				permutation[NR]++;
			}

			// for each row below current row
			for (j = i + 1; j < NR; j++) {

				// divide value below current row and column by factor at 
				// left of upper triangle (which is the absmax of the column)
				decomposed[j * NC + i] /= decomposed[i * NC + i];

				// for other columns, subtract in a factor of current row
				for (k = i + 1; k < NC; k++)
					decomposed[j * NC + k] -= decomposed[j * NC + i] * decomposed[i * NC + k];
			}
		}

	}
	needToRecalcDecomposed = false;  //decomposition done 
	//printDecomp(std::cout, 10);
	return true;
}


template<class T, int NR, int NC>
const T& Matrix2D<T, NR, NC>::determinant()
{
	// using method given in https://en.wikipedia.org/wiki/LU_decomposition
	if (needToRecalcDecomposed)
		decomposeLUP();

	if (needToRecalcDecomposed) // still true after call above
		throw std::out_of_range("Matrix is degenerate.");
	else {

		T det = decomposed[0];

		for (int i = 1; i < NR; i++)
			det *= decomposed[i * NC + i];

		return (permutation[NR] - NR) % 2 == 0 ? det : -det;

		if ((permutation[NR] - NR) % 2 == 0)
			return det;
		else
			return -det;
	}
}

template<class T, int NR, int NC>
void Matrix2D<T, NR, NC>::invert()
{
	// using method given in https://en.wikipedia.org/wiki/LU_decomposition
	// the inverted array will be placed in the content array
	// using information from the decomposed and permutation arrays

	if (needToRecalcDecomposed)
		decomposeLUP();

	if (needToRecalcDecomposed) // still true after call above
		throw std::out_of_range("Matrix is degenerate.");
	else {

		for (int j = 0; j < NC; j++) {
			for (int i = 0; i < NR; i++) {
				content[i * NC + j] = permutation[i] == j ? 1.0 : 0.0;

				for (int k = 0; k < i; k++)
					content[i * NC + j] -= decomposed[i * NC + k] * content[k * NC + j];
			}

			for (int i = NR - 1; i >= 0; i--) {
				for (int k = i + 1; k < NC; k++)
					content[i * NC + j] -= decomposed[i * NC + k] * content[k * NC + j];

				content[i * NC + j] /= decomposed[i * NC + i];
			}
		}

		needToRecalcDecomposed = true;
	}
}
