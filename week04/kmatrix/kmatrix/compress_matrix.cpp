#include"compress_matrix.h"
#include<iostream>
#include <iomanip> 
#include <iterator>
#include<unordered_map>
#include"compresskmatrix_iterator.h"


template<typename T>
CompressKMatrix<T>::CompressKMatrix()
    : m_row(0)
    , m_column(0)
{
}

template<typename T>
CompressKMatrix<T>::CompressKMatrix(int row, int column)
{
    init(row, column);
}

template<typename T>
CompressKMatrix<T>::~CompressKMatrix()
{
}

template<typename T>
void CompressKMatrix<T>::init(int row, int column)
{
    if (row < 0 || column < 0)
    {
        std::cout << "illegal row or column" << std::endl;
        m_row = 0;
        m_column = 0;
    }
    else
    {
        m_row = row;
        m_column = column;
    }
}

template<typename T>
int CompressKMatrix<T>::getRows() const
{
    return this->m_row;
}

template<typename T>
int CompressKMatrix<T>::getCols() const
{
    return this->m_column;
}

template<typename T>
void CompressKMatrix<T>::setData(int row, int col, T value)
{
    if (!value)return;
    auto it = m_matrix.find(std::pair<int, int>(row, col)); 
    if (it != m_matrix.end())
        it->second = value;
    else
        m_matrix.insert(std::pair<std::pair<int, int>,T>(std::pair<int, int>(row, col), value));
}

template<typename T>
T CompressKMatrix<T>::getData(int row, int col) const
{
    auto it = m_matrix.find(std::pair<int, int>(row, col));
    if (it != m_matrix.end())
        return  it->second;
    else
        return 0;
}

template<typename T>
void CompressKMatrix<T>::eraseRow(int row)
{
    std::unordered_map<std::pair<int, int>, T, pair_hash, KeyEqual> ans;
    for (auto it = m_matrix.begin(); it != m_matrix.end();it++)
    {
        if (it->first.first > row)
        {
            ans.insert(std::pair<std::pair<int, int>, T>(std::pair<int, int>(it->first.first-1, it->first.second), it->second));
        }
        else if(it->first.first < row)
        {
            ans.insert(std::pair<std::pair<int, int>, T>(std::pair<int, int>(it->first.first, it->first.second), it->second));
        }  
    }
    m_matrix = ans;
    m_row--;
}

template<typename T>
void CompressKMatrix<T>::eraseCol(int column)
{
    std::unordered_map<std::pair<int, int>, T, pair_hash, KeyEqual> ans;
    for (auto it = m_matrix.begin(); it != m_matrix.end(); it++)
    {
        if (it->first.second > column)
        {
            ans.insert(std::pair<std::pair<int, int>, T>(std::pair<int, int>(it->first.first, it->first.second-1), it->second));
        }
        else if (it->first.second < column)
        {
            ans.insert(std::pair<std::pair<int, int>, T>(std::pair<int, int>(it->first.first, it->first.second), it->second));
        }
    }
    m_matrix = ans;
    m_column--;
}

template<typename T>
bool CompressKMatrix<T>::sameSize(const CompressKMatrix<T>& matrix) const
{
    return getCols()==matrix.getCols()&&getRows()==matrix.getRows();
}

template<typename T>
T CompressKMatrix<T>::operator()(int i, int j) const
{
    return getData(i,j);
}

template<typename T>
CompressKMatrix<T> CompressKMatrix<T>::transpose() const
{
    CompressKMatrix<T> temp(m_column,m_row);
    for (auto it = m_matrix.begin(); it != m_matrix.end();it++)
    {
        temp.m_matrix.insert(std::pair<std::pair<int, int>,T>(std::pair<int, int>(it->first.second, it->first.first),it->second));
    }
    return temp;
}

template<typename T>
void CompressKMatrix<T>::print() const
{
    for (int i= 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            if (m_matrix.find(std::pair<int, int>(i, j)) != m_matrix.end())
                std::cout << std::setw(4) << std::setiosflags(std::ios::left) << m_matrix.find(std::pair<int, int>(i, j))->second;
            else
                std::cout << std::setw(4) << std::setiosflags(std::ios::left) << 0;
        }
        std::cout << std::endl;
        std::cout << std::resetiosflags(std::ios::left);
    }
    std::cout << std::endl;
}

template<typename T>
CompressKMatrixIterator<T> CompressKMatrix<T>::begin()
{
    CompressKMatrixIterator<T> startIter(*this);
    if (m_matrix.find(std::pair<int, int>(0, 0)) != m_matrix.end())
        startIter.m_value = m_matrix.find(std::pair<int, int>(0, 0))->second;
    else
        startIter.m_value = 0;
    startIter.m_nowCol = 0;
    startIter.m_nowRow = 0;
    return startIter;
}


template<typename T>
std::unordered_map < std::pair<int, int>, T, typename CompressKMatrix<T>::pair_hash, typename CompressKMatrix<T>::KeyEqual>& CompressKMatrix<T>::getCompressKMatrix()
{
    return this->m_matrix;
}

template<typename T>
CompressKMatrixIterator<T> CompressKMatrix<T>::end()
{
    CompressKMatrixIterator<T> endIter(*this);
    endIter.m_value = 0;
    endIter.m_nowCol = endIter.m_standardCol-1;
    endIter.m_nowRow = endIter.m_standardRow-1;
    return endIter;
}




template<typename T>
CompressKMatrix<T> operator+(const CompressKMatrix<T>& a, const CompressKMatrix<T>& b)
{
    if (!a.sameSize(b))
    {
        std::cout << "they have different size" << std::endl;
        return CompressKMatrix<T>();
    }
    CompressKMatrix<T> ans(a.getRows(), a.getCols());
    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end()
                || b.m_matrix.find(std::pair<int, int>(i, j)) != b.m_matrix.end())
            {
                if (a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end()
                    && b.m_matrix.find(std::pair<int, int>(i, j)) != b.m_matrix.end())
                {
                    ans.setData(i, j, a.getData(i, j) + b.getData(i, j));
                }
                else if(a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end())
                {
                    ans.setData(i, j, a.getData(i, j));
                }
                else
                {
                    ans.setData(i, j, b.getData(i, j));
                }
            }
        }
    }
    return ans;
}

template<typename T>
CompressKMatrix<T> operator-(const CompressKMatrix<T>& a, const CompressKMatrix<T>& b)
{
    if (!a.sameSize(b))
    {
        std::cout << "they have different size" << std::endl;
        return CompressKMatrix<T>();
    }
    CompressKMatrix<T> ans(a.getRows(), a.getCols());
    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end()
                || b.m_matrix.find(std::pair<int, int>(i, j)) != b.m_matrix.end())
            {
                if (a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end()
                    && b.m_matrix.find(std::pair<int, int>(i, j)) != b.m_matrix.end())
                {
                    ans.setData(i, j, a.getData(i, j) - b.getData(i, j));
                }
                else if (a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end())
                {
                    ans.setData(i, j, a.getData(i, j));
                }
                else
                {
                    ans.setData(i, j, -b.getData(i, j));
                }
            }
        }
    }
    return ans;
}

template<typename T>
CompressKMatrix<T> operator*(const CompressKMatrix<T> a, const CompressKMatrix<T> b)
{
    if (a.getCols() != b.getRows())
    {
        std::cout << "they have illegal size to multiply " << std::endl;
        return CompressKMatrix<T>();
    }
    CompressKMatrix<T> ans(a.getRows(), b.getCols());
    for (int i = 0; i < ans.getRows(); i++)
    {
        for (int j = 0; j < ans.getCols(); j++)
        {
            T sum = 0;
            for (int t = 0; t < a.getCols(); t++)
            {
                if (a.m_matrix.find(std::pair<int, int>(i, j)) != a.m_matrix.end()
                    && b.m_matrix.find(std::pair<int, int>(i, j)) != b.m_matrix.end())
                {
                    sum = sum + a.getData(i, t) * b.getData(t, j);
                }
                
            }
            ans.setData(i, j, sum);
        }
    }
    return ans;
}
