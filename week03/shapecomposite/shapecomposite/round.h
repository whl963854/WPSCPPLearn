#ifndef SHAPECOMPOSITE_ROUND
#define SHAPECOMPOSITE_ROUND
#include<string>
#include"shape.h"

const double PI = acos(-1);

class Round :public Shape {
public:

	Round();

	~Round();

	explicit Round(double radius);

	double getArea()const override;

	double getGirth()const override;

	std::string getType()const override;

	void print()const override;

private:

	double m_radius;

};


#endif // !SHAPECOMPOSITE_ROUND

