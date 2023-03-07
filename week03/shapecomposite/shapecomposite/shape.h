#ifndef SHAPECOMPOSITE_SHAPE
#define SHAPECOMPOSITE_SHAPE
#include<string>

//没有提供add()和remove()的函数接口，如果提供需要在每个简单图形类把这两个函数私有化隐藏，
//避免被对象直接调用
class Shape {
public:

	virtual double getArea()const = 0;

	virtual double getGirth()const = 0;

	virtual std::string getType()const = 0;

	virtual void print()const = 0;

	virtual ~Shape() = 0;

protected:

	std::string m_typeName;

};


#endif // !SHAPECOMPOSITE_SHAPE

