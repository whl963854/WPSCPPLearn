#ifndef COMPRESS_KMATRIX
#define COMPRESS_KMATRIX
#include<unordered_map>

template<typename T>
class CompressKMatrixIterator;


template <typename T>
class CompressKMatrix
{
    friend class CompressKMatrixIterator<T>;

public:

    CompressKMatrix();

    CompressKMatrix(int row, int column);

    ~CompressKMatrix();

    void  init(int row, int column);

    int  getRows() const;

    int  getCols() const;

    void setData(int row, int col, T value);

    T  getData(int row, int col)const;

    void  eraseRow(int row);

    void  eraseCol(int column);

    bool sameSize(const CompressKMatrix<T>& matrix)const;

    T operator()(int i, int j)const;


    template<typename T>
    friend CompressKMatrix<T> operator+(const CompressKMatrix<T>& a, const CompressKMatrix<T>& b);

    template<typename T>
    friend CompressKMatrix<T> operator-(const CompressKMatrix<T>& a, const CompressKMatrix<T>& b);

    template<typename T>
    friend CompressKMatrix<T> operator*(const CompressKMatrix<T>a, const CompressKMatrix<T>b);

    CompressKMatrix<T> transpose() const; //×ªÖÃ

    void print() const;//Êä³ö

    CompressKMatrixIterator<T> begin();

    CompressKMatrixIterator<T> end();

private:

    struct pair_hash
    {
        template<class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& p) const
        {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 ^ h2;
        }
    };

    struct KeyEqual {
        bool operator() (const std::pair<int, int>& keyL, const std::pair<int, int>& keyR) const {
            return keyL.first == keyR.first && keyL.second == keyR.second;
        }
    };

    std::unordered_map<std::pair<int, int>, T, pair_hash, KeyEqual> m_matrix;

    int m_row;

    int m_column;

    std::unordered_map < std::pair<int, int>, T, pair_hash, KeyEqual>& getCompressKMatrix();


};
#endif // COMPRESS_KMATRIX

