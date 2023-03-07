#include "trapezium.h"
#include <iostream>

Trapezium::Trapezium()
	: m_baseline(0.0)
	, m_topline(0.0)
	, m_lwaist(0.0)
	, m_rwaist(0.0)
{
	m_typeName = "Trapezium";
}

Trapezium::~Trapezium()
{
}

Trapezium::Trapezium(double topline, double baseline, double lwaist, double rwaist)
{
	if (check(topline, baseline, lwaist, rwaist)) 
	{
		m_baseline = baseline;
		m_topline = topline;
		m_lwaist = lwaist;
		m_rwaist = rwaist;
	}
	else 
	{
		m_baseline = 0.0;
		m_topline = 0.0;
		m_lwaist = 0.0;
		m_rwaist = 0.0;
	}
	m_typeName = "Trapezium";
}

double Trapezium::getArea() const
{
	if (!m_topline || !m_baseline || !m_lwaist || !m_rwaist)
		return 0.0;
	double area = (m_topline + m_baseline) / (4 * fabs(m_baseline - m_topline))
		* sqrt((m_topline + m_lwaist - m_baseline + m_rwaist) * (m_topline - m_lwaist - m_baseline + m_rwaist)
			* (m_topline + m_lwaist - m_baseline - m_rwaist) * (m_lwaist - m_topline + m_baseline + m_rwaist));
	return area;
}

double Trapezium::getGirth() const
{
	return m_baseline +m_topline+m_lwaist+m_rwaist;
}

std::string Trapezium::getType() const
{
	return m_typeName;
}

void Trapezium::print() const
{
	std::cout << "Type: " << getType() << "    Area: " << getArea() << "    Girth: "
		<< getGirth() << std::endl;
}

//两腰和>两底差，两腰差<两底差
bool Trapezium::check(double topline, double baseline, double lwaist, double rwaist) const
{
	if (fabs(baseline - topline) > fabs(lwaist - rwaist)
		&& fabs(baseline - topline) < fabs(lwaist + rwaist))
	{
		return true;
	}
	else 
	{
		std::cout << "illegal sides!!!" << std::endl;
	}
	return false;
}
