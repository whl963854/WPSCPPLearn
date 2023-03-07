#include "round.h"
#include <iostream>

Round::Round()
	: m_radius(0.0)
{
	m_typeName = "Round";
}

Round::~Round()
{
}

explicit Round::Round(double radius)
{
	m_typeName = "Round";
	if (radius > 0)
	{
		m_radius = radius;
	}
		
	else 
	{
		m_radius = 0.0;
		std::cout << "illegal sides!!!" << std::endl;
	}
		
}

double Round::getArea() const
{
	return PI*m_radius*m_radius;
}

double Round::getGirth() const
{
	return 2 * PI * m_radius;
}

std::string Round::getType() const
{
	return m_typeName;
}

void Round::print() const
{
	std::cout << "Type: " << getType() << "    Area: " << getArea() << "    Girth: "
		<< getGirth() << std::endl;
}
