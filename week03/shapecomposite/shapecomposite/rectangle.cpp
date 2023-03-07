#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle()
	: m_longSide(0.0)
	, m_shortSide(0.0)
{
	m_typeName = "Rectangle";
}

Rectangle::~Rectangle()
{
	
}

Rectangle::Rectangle(double shortSide, double longSide)
{
	if (shortSide > 0 && longSide > 0) 
	{
		m_longSide = longSide;
		m_shortSide = shortSide;
	}
	else 
	{
		std::cout << "illegal sides!!!" << std::endl;
		m_longSide = 0.0;
		m_shortSide = 0.0;
	}
	m_typeName = "Rectangle";
}

double Rectangle::getArea() const
{
	return m_longSide*m_shortSide;
}

double Rectangle::getGirth() const
{
	return 2 * (m_longSide + m_shortSide);
}

std::string Rectangle::getType() const
{
	return m_typeName;
}

void Rectangle::print() const
{
	std::cout << "Type: " << getType() << "    Area: " << getArea() << "    Girth: "
		<< getGirth() << std::endl;
}
