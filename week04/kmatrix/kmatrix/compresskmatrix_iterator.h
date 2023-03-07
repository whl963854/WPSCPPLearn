#ifndef __COMPRESSKMATRIX_ITERATOR
#define __COMPRESSKMATRIX_ITERATOR
#include <iterator>
#include <unordered_map>

template <typename T>
class CompressKMatrix;

template <typename T>
class CompressKMatrixIterator : public std::iterator < std::forward_iterator_tag, T >
{
	friend class CompressKMatrix<T>;

public:

	explicit CompressKMatrixIterator(CompressKMatrix<T>& compressMatrix);


	CompressKMatrixIterator<T>& operator=(const CompressKMatrixIterator& src);

	T& operator*();

	CompressKMatrixIterator<T>& operator++();

	CompressKMatrixIterator<T> operator++(int);

	bool operator==(const CompressKMatrixIterator& iter) const;

	bool operator!=(const CompressKMatrixIterator& iter) const;


private:

	T m_value;

	std::unordered_map<std::pair<int, int>, T,struct CompressKMatrix<T>::pair_hash, struct CompressKMatrix<T>::KeyEqual> m_matrix;

	int m_nowRow;

	int m_nowCol;

	int m_standardRow;

	int m_standardCol;
};



#endif // !__COMPRESSKMATRIX_ITERATOR

