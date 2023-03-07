#include "square.h"
#include <iostream>

Square::Square()
	: m_sideLength(0.0)
{
	m_typeName = "Square";
}

Square::~Square()
{
}

explicit Square::Square(double sideLength)
	: m_sideLength(sideLength)
{
	if (sideLength < 0) 
	{
		std::cout << "illegal sides!!!" << std::endl;
		m_sideLength = 0;
	}
	m_typeName = "Square";
}

double Square::getArea() const
{
	return m_sideLength* m_sideLength;
}

double Square::getGirth() const
{
	return 4*m_sideLength;
}

std::string Square::getType() const
{
	return m_typeName;
}

void Square::print() const
{
	std::cout << "Type: " << getType() << "    Area: " << getArea() << "    Girth: "
		<< getGirth() << std::endl;
}
