#ifndef SHAPECOMPOSITE_TRIANGLE
#define SHAPECOMPOSITE_TRIANGLE
#include<string>
#include"shape.h"

class Triangle:public Shape {
public:
	
	Triangle();

	~Triangle();

	Triangle(double sideOne,double sideTwo,double sideThree);

	double getArea()const override;

	double getGirth()const override;

	std::string getType()const override;

	void print()const override;

private:

	bool check(double sideOne, double sideTwo, double sideThree)const;

private:

	double m_sideOne, m_sideTwo, m_sideThree;

};


#endif // !SHAPECOMPOSITE_TRIANGLE

