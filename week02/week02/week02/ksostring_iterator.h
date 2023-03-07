#ifndef      WEEKTWO_KTOSTRING_ITERATOR_H 	
#define      WEEKTWO_KTOSTRING_ITERATOR_H 	

template<typename T>
class KsoString;

template<typename T>
class KsoString_Iterator : public std::iterator < std::forward_iterator_tag, T >
{
	friend class KsoString<T>;

public:

	explicit KsoString_Iterator(KsoString<T>& startIterator);

	KsoString_Iterator<T>& operator=(const KsoString_Iterator& src);

	T& operator*();

	KsoString_Iterator<T>& operator++();
	
	KsoString_Iterator operator++(int);

	bool operator<(const KsoString_Iterator& iter) const;

	bool operator==(const KsoString_Iterator& iter) const;

	bool operator!=(const KsoString_Iterator& iter) const;

	bool operator>(const KsoString_Iterator&iter) const;

	bool operator<=(const KsoString_Iterator& iter) const;

	bool operator>=(const KsoString_Iterator& iter) const;

private:
	LinkNode<T>* m_startIterator;
	T m_value;
};

#endif  //     WEEKTWO_KTOSTRING_ITERATOR_H 

