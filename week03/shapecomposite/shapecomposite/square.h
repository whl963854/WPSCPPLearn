#ifndef SHAPECOMPOSITE_SQUARE
#define SHAPECOMPOSITE_SQUARE
#include<string>
#include"shape.h"

class Square :public Shape {
public:

	Square();

	~Square();

	explicit Square(double sideLength);

	double getArea()const override;

	double getGirth()const override;

	std::string getType()const override;

	void print()const override;

private:

	double m_sideLength;

};


#endif // !SHAPECOMPOSITE_SQUARE

