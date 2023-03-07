#include "kmatrix.h"
#include<iostream>
#include <iomanip> 
#include <iterator>
#include "kmatrix_iterator.h"

template<typename T>
KMatrix<T>::KMatrix()
	: m_row(0)
	, m_column(0)
{
}

template<typename T>
KMatrix<T>::KMatrix(int row, int column)
{
	init(row, column);
}

template<typename T>
KMatrix<T>::~KMatrix()
{
}

template<typename T>
void KMatrix<T>::init(int row, int column)
{
	if (row<0||column<0) 
	{
		std::cout << "illegal row or column" << std::endl;
		m_row = 0;
		m_column = 0;
	}
	else 
	{
		m_row = row;
		m_column = column;
		for (int i = 0; i < m_row; i++) 
		{
			std::vector<T> temp(m_column, 0);
			this->m_matrix.push_back(temp);
		}
	}
	
}

template<typename T>
int KMatrix<T>::getRows() const
{
	return this->m_row;
}

template<typename T>
int KMatrix<T>::getCols() const
{
	return this->m_column;
}

template<typename T>
void KMatrix<T>::setData(int row, int col, T value)
{
	if (!check(row,col)) 
	{
		std::cout << "illegal row or column" << std::endl;
	}
	else 
	{
		m_matrix[row][col] = value;
	}
}

template<typename T>
T KMatrix<T>::getData(int row, int col)const
{
	if (!check(row,col))
	{
		std::cout << "illegal row or column!" << std::endl;
		return 0;
	}
	else
	{
		return m_matrix[row][col];
	}
}

template <typename T>
KMatrix<T> operator+(const KMatrix<T>& a, const KMatrix<T>& b)
{
	if (!a.sameSize(b))
	{
		std::cout << "they have different size" << std::endl;
		return KMatrix<T>();
	}
	KMatrix<T> ans(a.getRows(), a.getCols());
	for (int i = 0; i < a.getRows(); i++) 
	{
		for (int j = 0; j < a.getCols();j++)
		{
			ans.setData(i,j,a.getData(i,j)+b.getData(i,j));
		}
	}
	return ans;
}

template <typename T>
KMatrix<T> operator-(const KMatrix<T>& a, const KMatrix<T>& b)
{
	if (!a.sameSize(b))
	{
		std::cout << "they have different size" << std::endl;
		return KMatrix<T>();
	}
	KMatrix<T> ans(a.getRows(), a.getCols());
	for (int i = 0; i < a.getRows(); i++) 
	{
		for (int j = 0; j < a.getCols();j++)
		{
			ans.setData(i, j, a.getData(i,j) - b.getData(i,j));
		}
	}
	return ans;
}



template <typename T>
KMatrix<T> operator*(const KMatrix<T> a, const KMatrix<T> b)
{
	if (a.getCols()!=b.getRows())
	{
		std::cout << "they have illegal size to multiply " << std::endl;
		return KMatrix<T>();
	}
	KMatrix<T> ans( a.getRows(), b.getCols());
	for (int i = 0; i < ans.getRows(); i++)
	{
		for (int j = 0; j < ans.getCols(); j++)
		{
			T sum = 0;
			for (int t = 0; t < a.getCols(); t++)
			{
				sum = sum + a(i, t) * b(t,j);
			}	
			ans.setData(i, j, sum);
		}
	}
	return ans;
}



template<typename T>
void KMatrix<T>::eraseRow(int row)
{
	if (!check(row, 0))
	{
		std::cout << "illegal row" << std::endl;
		return;
	}
	auto iter = m_matrix.begin();
	for (int i = 0; i < row; i++, iter++);
	m_matrix.erase(iter);
	m_row--;
}

template<typename T>
void KMatrix<T>::eraseCol(int column)
{
	if (!check(0,column))
	{
		std::cout << "illegal column" << std::endl;
		return;
	}
	for (int i = 0; i < getRows(); i++)
	{
		auto iter = m_matrix[i].begin();
		for (int j = 0; j < column; j++,iter++);
		m_matrix[i].erase(iter);
	}
	m_column--;
}

template<typename T>
bool KMatrix<T>::sameSize(const KMatrix<T>& matrix) const
{
	return getRows() == matrix.getRows() && getCols() == matrix.getCols();
}

template<typename T>
T KMatrix<T>::operator()(int i, int j) const
{
	return getData(i,j);
}

template<typename T>
KMatrix<T> KMatrix<T>::transpose() const
{
	KMatrix<T>ans(this->getCols(),this->getRows());
	for (int i = 0; i < this->getRows(); i++)
	{
		for (int j = 0; j < this->getCols(); j++)
		{
			ans.setData(j, i, getData(i,j));
		}
	}
	return ans;
}

template<typename T>
void KMatrix<T>::print() const
{
	for (auto i : this->m_matrix) 
	{
		for (auto j : i)
		{
			std::cout << std::setw(3) << std::setiosflags(std::ios::left) << j;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::resetiosflags(std::ios::left);
}

template<typename T>
KMatrixIterator<T> KMatrix<T>::begin()
{
	return KMatrixIterator<T>(*this);
}

template<typename T>
KMatrixIterator<T> KMatrix<T>::end()
{
	KMatrixIterator<T> endIter(*this);
	endIter.m_iterator = endIter.m_iterVec[endIter.m_standardRow - 1];
	int i = 0;
	while (i < endIter.m_standardCol)
	{
		i++;
		endIter.m_iterator++;
	}
	endIter.m_nowCol = 0;
	endIter.m_nowRow = endIter.m_standardRow;
	return endIter;
}

template<typename T>
bool KMatrix<T>::check(int row, int column) const
{
	if (row < 0 || column < 0||row>=m_row||column>=m_column)
		return false;
	else
		return true;
}

template<typename T>
std::vector<std::vector<T>>& KMatrix<T>::getMatrix()
{
	return this->m_matrix;
}

