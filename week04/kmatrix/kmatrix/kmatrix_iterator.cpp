#include"kmatrix_iterator.h"
#include<vector>
#include<iostream>
#include"kmatrix.h"

template<typename T>
KMatrixIterator<T>::KMatrixIterator(KMatrix<T>& kmatrix)
	: m_nowRow(0)
	, m_nowCol(0)
	, m_standardRow(kmatrix.getRows())
	, m_standardCol(kmatrix.getCols())
{
	for (int i = 0; i < kmatrix.getRows(); i++)
	{
		m_iterVec.push_back(kmatrix.m_matrix[i].begin());
	}
	if (m_standardRow && m_standardCol)
		m_iterator = kmatrix.m_matrix[0].begin();
	else
		std::cout << "this is an illegal matrix!" << std::endl;
}

template<typename T>
KMatrixIterator<T>& KMatrixIterator<T>::operator=(const KMatrixIterator& src)
{
	m_iterator = src.m_iterator;
	m_nowCol = src.m_nowCol;
	m_nowRow = src.m_nowRow;
	m_standardCol = src.m_standardCol;
	m_standardRow = src.m_standardRow;
	m_iterVec = src.m_iterVec;
}

template<typename T>
T& KMatrixIterator<T>::operator*()
{
	return *m_iterator;
}

template<typename T>
KMatrixIterator<T>& KMatrixIterator<T>::operator++()
{
	if (m_nowCol < m_standardCol-1) {
		m_nowCol++;
		m_iterator++;
	}
	else
	{
		m_nowCol = 0;
		++m_nowRow;
		if(m_nowRow < m_standardRow)
			m_iterator = m_iterVec[m_nowRow];
		else
			m_iterator++;
	}
	return *this;
}

template<typename T>
KMatrixIterator<T> KMatrixIterator<T>::operator++(int)
{
	auto temp = *this;
	if (m_nowCol < m_standardCol-1)
	{
		m_nowCol++;
		m_iterator++;
	}
	else
	{
		m_nowRow++;
		m_nowCol = 0;
		if (m_nowRow < m_standardRow)
			m_iterator = m_iterVec[m_nowRow];
		else
			m_iterator++;
	}
	return temp;
}

template<typename T>
bool KMatrixIterator<T>::operator<(const KMatrixIterator& iter) const
{
	return this->m_nowRow * this->m_standardCol + this->m_nowCol <
		iter.m_nowRow * iter.m_standardCol + iter.m_nowCol;
}

template<typename T>
bool KMatrixIterator<T>::operator==(const KMatrixIterator& iter) const
{
	return this->m_standardRow == iter.m_standardRow && this->m_standardCol == iter.m_standardCol
		&& this->m_nowRow == iter.m_nowRow && this->m_nowCol == iter.m_nowCol;
}

template<typename T>
bool KMatrixIterator<T>::operator!=(const KMatrixIterator& iter) const
{
	return !(this->m_standardRow == iter.m_standardRow && this->m_standardCol == iter.m_standardCol
		&& this->m_nowRow == iter.m_nowRow && this->m_nowCol == iter.m_nowCol);
}

template<typename T>
bool KMatrixIterator<T>::operator>(const KMatrixIterator& iter) const
{
	return this->m_nowRow * this->m_standardCol + this->m_nowCol >iter.m_nowRow * iter.m_standardCol + iter.m_nowCol;
}

template<typename T>
bool KMatrixIterator<T>::operator<=(const KMatrixIterator& iter) const
{
	return this->m_nowRow * this->m_standardCol + this->m_nowCol <=iter.m_nowRow * iter.m_standardCol + iter.m_nowCol;
}

template<typename T>
bool KMatrixIterator<T>::operator>=(const KMatrixIterator& iter) const
{
	return this->m_nowRow * this->m_standardCol + this->m_nowCol >= iter.m_nowRow * iter.m_standardCol + iter.m_nowCol;
}
