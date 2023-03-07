#ifndef SHAPECOMPOSITE_RECTANGLE
#define SHAPECOMPOSITE_RECTANGLE
#include<string>
#include"shape.h"

class Rectangle :public Shape {
public:

	Rectangle();

	~Rectangle();

	Rectangle(double shortSide, double longSide);

	double getArea()const override;

	double getGirth()const override;

	std::string getType()const override;

	void print()const override;

private:

	double m_shortSide,m_longSide;

};


#endif // !SHAPECOMPOSITE_RECTANGLE

