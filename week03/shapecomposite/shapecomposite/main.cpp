#include <iostream>
#include"shape.h"
#include"compoundshape.h"
#include"round.h"
#include"rectangle.h"
#include"square.h"
#include"trapezium.h"
#include"triangle.h"

void illegalInputTest() 
{
    std::cout << "illegal input test" << std::endl;
    std::shared_ptr<Shape> triangle(new Triangle(10, 4, 5));
    triangle->print();

    std::shared_ptr<Shape> trapezium(new Trapezium(20, 8, 5, 5));
    trapezium->print();

    std::shared_ptr<Shape> round(new Round(-1));
    round->print();

    std::shared_ptr<Shape> rectangle(new Rectangle(-3, 20));
    rectangle->print();

    std::shared_ptr<Shape> square(new Square(-100));
    square->print();
    std::cout << std::endl;
}
void singleShapeTest()
{
    std::cout << "single shape test" << std::endl;

    std::shared_ptr<Shape> triangle(new Triangle(3, 4, 5));
    triangle->print();

    std::shared_ptr<Shape> trapezium(new Trapezium(2, 8, 5, 5));
    trapezium->print();

    std::shared_ptr<Shape> round (new Round(10));
    round->print();

    std::shared_ptr<Shape> rectangle (new Rectangle(10, 20));
    rectangle->print();

    std::shared_ptr<Shape> square (new Square(10));
    square->print();

    std::cout << std::endl;

}
void complexShapeTest()
{
    std::cout << "complex shape test" << std::endl;

    Shape* triangleShape = new Triangle(3, 4, 5);
    Shape* trapeziumShape = new Trapezium(2, 8, 5, 5);
    Shape* roundShape = new Round(10);
    Shape* rectangleShape = new Rectangle(10, 20);
    Shape* squareShape = new Square(10);

    CompoundShape* compountShape = new CompoundShape();
    compountShape->add(triangleShape);
    compountShape->add(trapeziumShape);
    compountShape->add(roundShape);
    compountShape->add(rectangleShape);
    compountShape->add(squareShape);
    compountShape->print();

    CompoundShape* compountShape2 = new CompoundShape();
    compountShape2->add(compountShape);
    compountShape2->add(triangleShape);
    compountShape2->add(trapeziumShape);
    compountShape2->add(roundShape);
    compountShape2->add(rectangleShape);
    compountShape2->add(squareShape);
    compountShape2->print();

    CompoundShape* compountShape3 = new CompoundShape();
    compountShape3->add(compountShape2);
    compountShape3->add(compountShape);
    compountShape3->add(triangleShape);
    compountShape3->add(trapeziumShape);
    compountShape3->add(roundShape);
    compountShape3->add(rectangleShape);
    compountShape3->add(squareShape); 
    compountShape3->print();

    std::cout<<std::endl;
    std::cout << "remove test" << std::endl;
    std::cout << "current value";
    compountShape3->print();
    compountShape3->remove(roundShape);
    std::cout << "remove roundShape(Area:314  Girth:62.8):";
    compountShape3->print();
    compountShape3->remove(compountShape2);
    std::cout << "remove compountShape2(Area:1280  Girth:390):";
    compountShape3->print();

    std::cout << std::endl;

    delete triangleShape;
    delete trapeziumShape;
    delete roundShape;
    delete rectangleShape;
    delete squareShape;
    delete compountShape2;
    delete compountShape;


}
int main()
{
    illegalInputTest();
    singleShapeTest();
    complexShapeTest();
    return 0;
}

