#include "compoundshape.h"
#include <iostream>

CompoundShape::CompoundShape()
{
	m_typeName = "CompoundShape";
}

CompoundShape::~CompoundShape()
{
}

void CompoundShape::remove(Shape* element)
{
	m_compositeShape.remove(element);
}

void CompoundShape::add(Shape* element)
{
	m_compositeShape.push_back(element);
}

double CompoundShape::getArea() const
{
	double sumArea = 0.0;
	for (auto element : m_compositeShape) 
	{
		sumArea+=element->getArea();
	}
	return sumArea;
}

double CompoundShape::getGirth() const
{
	double sumGirth = 0.0;
	for (auto element : m_compositeShape) 
	{
		sumGirth += element->getGirth();
	}
	return sumGirth;
}

std::string CompoundShape::getType() const
{
	return m_typeName;
}

void CompoundShape::print() const
{
	std::cout << "Type: " << getType() << "    Area: " << getArea() << "    Girth: "
		<< getGirth() << std::endl;
}
