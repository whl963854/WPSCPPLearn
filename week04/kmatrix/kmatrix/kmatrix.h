#ifndef __KMATRIX
#define __KMATRIX
#include<vector>


template<typename T>
class KMatrixIterator;


template <typename T>
class KMatrix
{
    friend class KMatrixIterator<T>;

public:

    KMatrix();

    KMatrix(int row, int column);

    ~KMatrix();

    void  init(int row, int column); 

    int  getRows() const; 

    int  getCols() const;

    void setData(int row, int col, T value);

    T  getData(int row, int col)const;

    void  eraseRow(int row); 

    void  eraseCol(int column);

    bool sameSize(const KMatrix<T>& matrix)const;

    T operator()(int i,int j)const;


    template<typename T>
    friend KMatrix<T> operator+(const KMatrix<T>& a, const KMatrix<T>& b);

    template<typename T>
    friend KMatrix<T> operator-(const KMatrix<T>& a, const KMatrix<T>& b);

    template<typename T>
    friend KMatrix<T> operator*(const KMatrix<T>a, const KMatrix<T>b);

    KMatrix<T> transpose() const; //×ªÖÃ

    void print() const;//Êä³ö

    KMatrixIterator<T> begin();

    KMatrixIterator<T> end();

private:

    std::vector<std::vector<T> > m_matrix;

    int m_row;

    int m_column;

    bool check(int row, int column)const;

    std::vector<std::vector<T>>& getMatrix();
};
#endif // __KMATRIX

