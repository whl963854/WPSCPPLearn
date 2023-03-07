#ifndef SHAPECOMPOSITE_TRAPEZIUM
#define SHAPECOMPOSITE_TRAPEZIUM
#include<string>
#include"shape.h"

class Trapezium :public Shape {
public:

	Trapezium();

	~Trapezium();

	Trapezium(double topline,double baseline,double lwaist,double rwaist);

	double getArea()const override;

	double getGirth()const override;

	std::string getType()const override;

	void print()const override;

private: 

	bool check(double topline, double baseline, double lwaist, double rwaist)const;

private:

	double m_topline;
	double m_baseline;
	double m_lwaist;
	double m_rwaist;

};


#endif // !SHAPECOMPOSITE_TRAPEZIUM

