/*[ Summary ]
ShapeSensor is a behavioral design pattern that lets you separate 
algorithms from the objects on which they operate.

Note: Double Dispatch is the key!
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <vector>
#include <memory>

class Circle;
class Dot;

class ShapeSensor
{
public:
    void visit(Circle* circle);
    void visit(Dot* dot);
};

class Visitable 
// If you add this properity to some class, you should overload visit() in class ShapeSensor and set class ShapeSensor as a friend.
{
public:
    virtual void accept(ShapeSensor* visitor) = 0; // Double Dispatch
};

class Circle
    :public Visitable
{
    friend ShapeSensor;
public:
    void accept(ShapeSensor* visitor) override { visitor->visit(this); }
protected:
    double radius = 1.0;
};

class Dot
    :public Visitable
{
    friend ShapeSensor;
public:
    void accept(ShapeSensor* visitor) override { visitor->visit(this); }
protected:
    double radius = 0.1;
};

class Canvas
{
public:
    Canvas& addShape(std::unique_ptr<Visitable> shape)
    {
        this->shapes.emplace_back(std::move(shape));
        return *this;
    }

    void measureAllShapes() const
    {
        static ShapeSensor sensor{};

        for (auto& shape : this->shapes) 
            shape->accept(&sensor);
    }
protected:
    std::vector<std::unique_ptr<Visitable>> shapes;
};

int main(int argc, char* argv[])
{
    Canvas canvas{};
    canvas.addShape(std::make_unique<Circle>())
          .addShape(std::make_unique<Dot>());

    canvas.measureAllShapes();
    
    return EXIT_SUCCESS;
}

void ShapeSensor::visit(Circle* circle)
{
    std::cout << std::format("Circle Radius = {}\n", circle->radius);
}

void ShapeSensor::visit(Dot* dot)
{
    std::cout << std::format("Dot Radius = {}\n", dot->radius);
}

