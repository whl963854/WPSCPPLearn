#include"ksostring.cpp"
#include"ksostring_iterator.h"
#include"linknode.h"

template<typename T>
KsoString_Iterator<T>::KsoString_Iterator(KsoString<T>& startIterator)
	: m_startIterator(startIterator.m_linkHead)
{
	if (startIterator.m_linkHead)
		m_value = startIterator.m_linkHead->m_val;
	else m_value = 0;
}

template<typename T>
KsoString_Iterator<T>& KsoString_Iterator<T>::operator=(const KsoString_Iterator& src)
{
	m_startIterator = src.m_startIterator;
	m_value = src.m_value;
}


template<typename T>
T& KsoString_Iterator<T>::operator*()
{
	return m_value;
}

template<typename T>
KsoString_Iterator<T>& KsoString_Iterator<T>::operator++()
{
	m_startIterator = m_startIterator->m_next;
	if(m_startIterator)
		m_value = m_startIterator->m_val;
	return *this;
}

template<typename T>
KsoString_Iterator<T> KsoString_Iterator<T>::operator++(int)
{
	auto temp = *this;
	m_startIterator = m_startIterator->m_next;
	m_value = m_startIterator->m_val;                       // Increment the value by the range step
	return temp;
}

template<typename T>
bool KsoString_Iterator<T>::operator<(const KsoString_Iterator& iter) const
{
	return m_value<iter.m_value;
}

template<typename T>
bool KsoString_Iterator<T>::operator==(const KsoString_Iterator& iter) const
{
	return m_value == iter.m_value;
}

template<typename T>
bool KsoString_Iterator<T>::operator!=(const KsoString_Iterator& iter) const
{
	return m_startIterator != iter.m_startIterator;
}

template<typename T>
bool KsoString_Iterator<T>::operator>(const KsoString_Iterator& iter) const
{
	return m_value > iter.m_value;
}

template<typename T>
bool KsoString_Iterator<T>::operator>=(const KsoString_Iterator& iter) const
{
	return m_value >= iter.m_value;
}

template<typename T>
bool KsoString_Iterator<T>::operator<=(const KsoString_Iterator& iter) const
{
	return m_value <= iter.m_value;
}
