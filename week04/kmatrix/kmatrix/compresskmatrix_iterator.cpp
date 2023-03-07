#include"compress_matrix.h"
#include"compresskmatrix_iterator.h"


template<typename T>
CompressKMatrixIterator<T>::CompressKMatrixIterator( CompressKMatrix<T>& compressMatrix)
	: m_nowRow(0)
	, m_nowCol(0)
	, m_standardRow(compressMatrix.getRows())
	, m_standardCol(compressMatrix.getCols())
	, m_value(0)
{
	m_matrix = compressMatrix.m_matrix;
}

template<typename T>
CompressKMatrixIterator<T>& CompressKMatrixIterator<T>::operator=(const CompressKMatrixIterator& src)
{
	m_nowCol = src.m_nowCol;
	m_nowRow = src.m_nowRow;
	m_standardCol = src.m_standardCol;
	m_standardRow = src.m_standardRow;
	m_value = src.m_value;
}

template<typename T>
T& CompressKMatrixIterator<T>::operator*()
{
	return m_value;
}

template<typename T>
CompressKMatrixIterator<T>& CompressKMatrixIterator<T>::operator++()
{
	if (m_nowCol < m_standardCol-1)
	{
		m_nowCol++;
		if (m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol)) != m_matrix.end())
			m_value = m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol))->second;
		else
			m_value = 0;
	}
	else
	{
		m_nowCol = 0;
		++m_nowRow;
		if (m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol)) != m_matrix.end())
			m_value = m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol))->second;
		else
			m_value = 0;
	}
	return *this;
}

template<typename T>
CompressKMatrixIterator<T> CompressKMatrixIterator<T>::operator++(int)
{
	auto temp = *this;
	if (m_nowCol < m_standardCol)
	{
		m_nowCol++;
		if (m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol)) != m_matrix.end())
			m_value = m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol))->second;
		else
			m_value = 0;
	}
	else
	{
		m_nowCol = 0;
		++m_nowRow;
		if (m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol)) != m_matrix.end())
			m_value = m_matrix.find(std::pair<int, int>(m_nowRow, m_nowCol))->second;
		else
			m_value = 0;
	}
	return temp;
}

template<typename T>
bool CompressKMatrixIterator<T>::operator==(const CompressKMatrixIterator& iter) const
{
	return this->m_standardRow == iter.m_standardRow && this->m_standardCol == iter.m_standardCol
		&& this->m_nowRow * this->m_standardCol + this->m_nowCol > iter.m_nowRow* iter.m_standardCol + iter.m_nowCol;
}

template<typename T>
bool CompressKMatrixIterator<T>::operator!=(const CompressKMatrixIterator& iter) const
{
	return !(this->m_standardRow == iter.m_standardRow && this->m_standardCol == iter.m_standardCol
		&& this->m_nowRow * this->m_standardCol + this->m_nowCol > iter.m_nowRow* iter.m_standardCol + iter.m_nowCol);
}
