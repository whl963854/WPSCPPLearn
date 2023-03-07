#include<iostream>
#include <iomanip> 
#include<vld.h>
#include"kmatrix.cpp"
#include"kmatrix_iterator.cpp"
#include"compress_matrix.cpp"
#include"compresskmatrix_iterator.cpp"

#define random(x) rand()%(x)

template<typename T>
KMatrix<T> testInit1(int col, int column)
{
	KMatrix<T>temp(col, column);
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.setData(i, j, i + j);
		}
	}
	return temp;
}

template<typename T>
KMatrix<T> testInit2(int col, int column)
{
	KMatrix<T>temp(col, column);
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.setData(i, j,1);
		}
	}
	return temp;
}

template<typename T>
CompressKMatrix<T> testInit3(int row, int col)
{
	CompressKMatrix<T>temp(row, col);
	for (int i = 0; i < random(row*col); i++)
	{
		temp.setData(random(row), random(col), random(100));
	}
	return temp;
}

void testKMatrix()
{
	KMatrix<int>temp1 = testInit1<int>(10, 10);
	KMatrix<int>temp2 = testInit1<int>(10, 10);
	temp1.print();

	
	
	if(temp1.sameSize(temp2))
		std::cout << "temp1 and temp2 have the same size "<< std::endl;
	else
		std::cout << "temp1 and temp2 do not have the same size " << std::endl ;
	std::cout << std::endl;

	
	KMatrix<int>temp3 = temp1 - temp2;
	temp3.print();

	temp3 = temp1 + temp2;
	temp3.print();

	for (int i = 0 ; i < temp3.getRows(); i++)
	{
		for (int j = 0; j < temp3.getCols(); j++)
		{
			temp3.setData(i, j, 10);
		}
	}
	temp3.print();

	temp3.eraseRow(0);
	temp3.eraseRow(0);
	temp3.eraseRow(0);
	temp3.eraseRow(0);
	temp3.eraseRow(0);
	temp3.print();

	temp3.eraseRow(10);
	temp3.print();

	temp2.print();
	temp2.eraseCol(0);
	temp2.eraseCol(0);
	temp2.eraseCol(0);
	temp2.eraseCol(0);
	temp2.print();


	KMatrix<int> temp4 = testInit2<int>(10, 20);
	KMatrix<int> temp5 = testInit2<int>(20, 10);
	temp4.print();
	temp5.print();

	KMatrix<int>temp6 = temp4 * temp5;
	temp6.print();

	temp6.eraseCol(0);
	temp6.eraseCol(0);
	temp6.eraseCol(0);
	temp6.eraseCol(0);
	temp6.print();

	KMatrix<int>temp7 = temp6.transpose();
	temp7.print();
}

void testIterator()
{
	KMatrix<int>temp1 = testInit1<int>(10, 10);
	temp1.print();
	std::cout << "------------------------------------" << std::endl;
	int count = temp1.getCols();
	auto iterTemp = temp1.begin();
	auto iterEnd = temp1.end();

	for (auto i : temp1) {
		std::cout << std::setw(3) << std::setiosflags(std::ios::left) << i;
		
		if (!(--count))
		{
			count = temp1.getCols();
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::resetiosflags(std::ios::left);
}

void testCompressMatrix()
{
	CompressKMatrix<int> temp1=testInit3<int>(5,5);
	CompressKMatrix<int> temp2 = testInit3<int>(5, 5);
	temp1.print();
	temp2.print();

	if (temp1.sameSize(temp2))
		std::cout << "temp1 and temp2 have the same size " << std::endl;
	else
		std::cout << "temp1 and temp2 do not have the same size " << std::endl;
	std::cout << std::endl;


	CompressKMatrix<int> temp3 = temp1 - temp2;
	temp3.print();

	temp3 = temp1 + temp2;
	temp3.print();

	for (int i = 0; i < temp3.getRows(); i++)
	{
		for (int j = 0; j < temp3.getCols(); j++)
		{
			temp3.setData(i, j, 10);
		}
	}
	temp3.print();

	temp3.eraseRow(0);
	temp3.eraseRow(0);
	temp3.print();

	temp3.eraseRow(10);
	temp3.print();

	temp2.print();
	temp2.eraseCol(0);
	temp2.eraseCol(0);
	temp2.print();


	CompressKMatrix<int> temp4 = testInit3<int>(5, 10);
	CompressKMatrix<int> temp5 = testInit3<int>(10, 6);
	for (int i = 0; i < temp4.getRows(); i++)
	{
		for (int j = 0; j < temp4.getCols(); j++)
		{
			temp4.setData(i, j, 1);
		}
	}
	for (int i = 0; i < temp5.getRows(); i++)
	{
		for (int j = 0; j < temp5.getCols(); j++)
		{
			temp5.setData(i, j, 1);
		}
	}
	temp4.print();
	temp5.print();

	CompressKMatrix<int>temp6 = temp4 * temp5;
	temp6.print();

	temp6.eraseRow(0);
	temp6.eraseRow(0);
	temp6.print();

	CompressKMatrix<int>temp7 = temp6.transpose();
	temp7.print();
}

void testCompressMatrixIterator()
{
	CompressKMatrix<int>temp1 = testInit3<int>(10, 10);
	temp1.print();
	std::cout << "------------------------------------" << std::endl;
	int count = temp1.getCols();
	auto iterTemp = temp1.begin();
	auto iterEnd = temp1.end();

	for (auto i : temp1) {
		std::cout << std::setw(4) << std::setiosflags(std::ios::left) << i;
		if (!(--count))
		{
			count = temp1.getCols();
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::resetiosflags(std::ios::left);
}
int main()
{
	//testKMatrix();
	//testIterator();
	//testCompressMatrix();
	//testCompressMatrixIterator();
	return 0;
}


