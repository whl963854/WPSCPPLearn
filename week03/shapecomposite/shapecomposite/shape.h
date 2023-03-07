#ifndef SHAPECOMPOSITE_SHAPE
#define SHAPECOMPOSITE_SHAPE
#include<string>

//û���ṩadd()��remove()�ĺ����ӿڣ�����ṩ��Ҫ��ÿ����ͼ���������������˽�л����أ�
//���ⱻ����ֱ�ӵ���
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

