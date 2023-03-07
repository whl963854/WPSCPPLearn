#ifndef SHAPECOMPOSITE_COMPOUNDSHAPE
#define SHAPECOMPOSITE_COMPOUNDSHAPE
#include<string>
#include<List>
#include"shape.h"

class CompoundShape :public Shape {
public:

	CompoundShape();

	~CompoundShape();

	void remove(Shape *element);

	void add(Shape *element);

	double getArea()const override;

	double getGirth()const override;

	std::string getType()const override;

	void print()const override;

private:

	std::list<Shape*> m_compositeShape;

};


#endif // !SHAPECOMPOSITE_COMPOUNDSHAPE

