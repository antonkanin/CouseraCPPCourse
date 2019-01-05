//#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix
{
public:
	Matrix()
	{};

	Matrix(int num_rows, int num_cols)
	{
		Reset(num_rows, num_cols);
	}

	void Reset(int num_rows, int num_cols)
	{
		if (num_rows < 0 || num_cols < 0)
		{
			throw out_of_range("Index out of range");
		}

		rowCount = num_rows;
		colCount = num_cols;

		matrix.resize(num_rows);
		for (auto& item : matrix)
		{
			item.assign(num_cols, 0);
		}
	}

	int At(int row, int col) const
	{
		if (row < 0 || row >= GetNumRows() || col < 0 || col >= GetNumColumns())
		{
			throw out_of_range("Index out of range");
		}

		return matrix[row][col];
	}

	int& At(int row, int col)
	{
		if (row < 0 || row >= GetNumRows() || col < 0 || col >= GetNumColumns())
		{
			throw out_of_range("Index out of range");
		}

		return matrix[row][col];
	}

	int GetNumRows() const
	{
		return rowCount;
	}

	int GetNumColumns() const
	{
		return colCount;
	}

private:
	vector<vector<int>> matrix;

	int rowCount = 0;
	int colCount = 0;
};

istream& operator>>(istream& stream, Matrix& matrix)
{
	int cols_num, rows_num;
	stream >> rows_num >> cols_num;

	matrix.Reset(rows_num, cols_num);

	for (int row_id = 0; row_id < rows_num; ++row_id)
	{
		for (int col_id = 0; col_id < cols_num; ++col_id)
		{
			int num;
			stream >> num;
			matrix.At(row_id, col_id) = num;
		}
	}

	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix)
{
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;

	for (int row_id = 0; row_id < matrix.GetNumRows(); ++row_id)
	{
		for (int col_id = 0; col_id < matrix.GetNumColumns(); ++col_id)
		{
			stream << matrix.At(row_id, col_id) << " ";
		}
		stream << endl;
	}

	return stream;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows() ||
		lhs.GetNumColumns() != rhs.GetNumColumns())
	{
		throw invalid_argument("Matrix sizes do not match");
	}

	Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());

	for (int row_id = 0; row_id < lhs.GetNumRows(); ++row_id)
	{
		for (int col_id = 0; col_id < lhs.GetNumColumns(); ++col_id)
		{
			result.At(row_id, col_id) = lhs.At(row_id, col_id) + rhs.At(row_id, col_id);
		}
	}

	return result;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows() ||
		lhs.GetNumColumns() != rhs.GetNumColumns())
	{
		return false;
	}

	for (int row_id = 0; row_id < lhs.GetNumRows(); ++row_id)
	{
		for (int col_id = 0; col_id < lhs.GetNumColumns(); ++col_id)
		{
			if (lhs.At(row_id, col_id) != rhs.At(row_id, col_id))
			{
				return false;
			}
		}
	}

	return true;
}

int main()
{
	Matrix one(0, 1);
	Matrix two(1, 0);

	auto t = one + two;

	return 0;
}
