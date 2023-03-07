#include "triangle.h"
#include <iostream>
#include <cstdarg>

Triangle::Triangle()
	: m_sideOne(0.0)
	, m_sideThree(0.0)
	, m_sideTwo(0.0)
{
	m_typeName = "Triangle";
}

Triangle::~Triangle()
{
}

Triangle::Triangle(double sideOne, double sideTwo, double sideThree)
{
	m_typeName = "Triangle";
	if (check(sideOne, sideTwo, sideThree)) 
	{
		m_sideOne = sideOne;
		m_sideThree = sideThree;
		m_sideTwo = sideTwo;
	}
	else 
	{
		m_sideOne = 0.0;
		m_sideThree = 0.0;
		m_sideTwo = 0.0;
	}
}

double Triangle::getArea() const
{
	double girth = getGirth() / 2;
	//º£Â×¹«Ê½
	return sqrt(girth * (girth - m_sideOne) *(girth - m_sideTwo) * (girth - m_sideThree));
}

double Triangle::getGirth() const
{
	return m_sideOne+m_sideTwo+m_sideThree;
}

std::string Triangle::getType() const
{
	return m_typeName;
}

void Triangle::print() const
{
	std::cout << "Type: " << getType() << "    Area: " << getArea()<< "    Girth: " 
		<< getGirth() << std::endl;
}

bool Triangle::check(double sideOne, double sideTwo, double sideThree) const
{
	if (sideTwo <= 0 || sideOne <= 0 || sideThree <= 0 || sideOne + sideTwo <= sideThree
		|| sideOne + sideThree <= sideTwo || sideTwo + sideThree <= sideOne)
	{
		std::cout << "illegal sides!!!" << std::endl;
		return false;
	}
	return true;
}
