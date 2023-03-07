#ifndef __KMATRIX_ITERATOR
#define __KMATRIX_ITERATOR
#include <iterator>
#include <vector>

template <typename T>
class KMatrix;

template <typename T>
class KMatrixIterator : public std::iterator < std::forward_iterator_tag, T >
{
	friend class KMatrix<T>;

public:

	explicit KMatrixIterator(KMatrix<T>& matrix);


	KMatrixIterator<T>& operator=(const KMatrixIterator& src);

	T& operator*();

	KMatrixIterator<T>& operator++();

	KMatrixIterator<T> operator++(int);

	bool operator<(const KMatrixIterator& iter) const;

	bool operator==(const KMatrixIterator& iter) const;

	bool operator!=(const KMatrixIterator& iter) const;

	bool operator>(const KMatrixIterator& iter) const;

	bool operator<=(const KMatrixIterator& iter) const;

	bool operator>=(const KMatrixIterator& iter) const;

private:

	//不加typename，std::vector<T>::iterator这个类型无法被编译器确定
	typename std::vector<T>::iterator m_iterator;

	std::vector<typename std::vector<T>::iterator> m_iterVec;

	int m_nowRow;

	int m_nowCol;

	int m_standardRow;

	int m_standardCol;
};



#endif // !__KMATRIX_ITERATOR

