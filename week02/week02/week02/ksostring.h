#ifndef      WEEKTWO_KTOSTRING_H 	
#define      WEEKTWO_KTOSTRING_H 	
#include"linknode.h"
#include"assert.h"

template<typename T>
class KsoString_Iterator;

template<class T>
class KsoString
{
public:

	friend class KsoString_Iterator<T>;

	KsoString();

	KsoString(const KsoString<T>& nodeList);

	~KsoString();

	void addNode(T data);

	int getLength()const noexcept;

	void insert(int index, T data);

	void deleteNode(int index);

	bool isEmpty()const noexcept;

	T getData(int index)const;

	T operator[](int index)const;

	int getIndex(const T& data)const noexcept;

	void printLink()const noexcept;

	KsoString_Iterator<T> begin(); 
	
	KsoString_Iterator<T> end();



private:
	int m_length;
	LinkNode<T> *m_linkHead;
	LinkNode<T> *m_linkTail;
};

#endif  //     WEEKTWO_KTOSTRING_H 

