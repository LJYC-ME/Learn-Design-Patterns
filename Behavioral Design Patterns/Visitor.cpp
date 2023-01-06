/*[ Summary ]
Visitor is a behavioral design pattern that lets you separate 
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

class Visitor
{
public:
    void visit(Circle* circle);
    void visit(Dot* dot);
};

class Visitable 
// If you add this properity to some class, you should overload visit() in class Visitor and set class Visitor as a friend.
{
public:
    virtual void accept(Visitor* visitor) = 0; // Double Dispatch
};

class Circle
    :public Visitable
{
    friend Visitor;
public:
    void accept(Visitor* visitor) override { visitor->visit(this); }
protected:
    double radius = 1.0;
};

class Dot
    :public Visitable
{
    friend Visitor;
public:
    void accept(Visitor* visitor) override { visitor->visit(this); }
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

    void visitAllShapes() const
    {
        static Visitor visitor{};

        for (auto& shape : this->shapes) 
            shape->accept(&visitor);
    }
protected:
    std::vector<std::unique_ptr<Visitable>> shapes;
};

int main(int argc, char* argv[])
{
    Canvas canvas{};
    canvas.addShape(std::make_unique<Circle>())
                .addShape(std::make_unique<Dot>());

    canvas.visitAllShapes();
    
    return EXIT_SUCCESS;
}

void Visitor::visit(Circle* circle)
{
    std::cout << std::format("Circle Radius = {}\n", circle->radius);
}

void Visitor::visit(Dot* dot)
{
    std::cout << std::format("Dot Radius = {}\n", dot->radius);
}

