/*[Summary]
Composite is a structural design pattern that lets you compose objects
into tree structures and then work with these structures as if they were
individual objects.
*/

#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <memory>

class Graphics
{
public:
    virtual void draw() = 0 ;
};

class Dot
    :public Graphics
{
public:
    virtual void draw() override { std::cout << "Drawing a dot\n"; }
};

class Triangle
    :public Graphics
{
public:
    virtual void draw() override { std::cout << "Drawing a triangle\n"; }
};

class CompoundGraphics // Container
    :public Graphics
{
public:
    void addMember(std::shared_ptr<Graphics> member)
    {
        this->members.emplace_back(member);
    }

    virtual void draw() override 
    { 
        std::cout << ">> Decompositing a group\n"; 
        for (auto& member : this->members) member->draw();
    }
protected:
    std::vector<std::shared_ptr<Graphics>> members;
};

class ImageEditor
{
public:
    void addElement(std::shared_ptr<Graphics> element)
    {
        this->elements.emplace_back(element);
    }
    void draw(uint32_t idx)
    {
        elements[idx]->draw(); // Unsafe
    }
protected:
    std::vector<std::shared_ptr<Graphics>> elements;
};

int main(int argc, char* argv[])
{
    // init
    ImageEditor editor{};
    auto dot = std::make_shared<Dot>();
    auto triangle = std::make_shared<Triangle>();

    editor.addElement(triangle);

    auto groupA = std::make_shared<CompoundGraphics>();
    groupA->addMember(dot);
    groupA->addMember(dot);
    groupA->addMember(dot);
    editor.addElement(groupA);
    
    // render
    editor.draw(0);
    editor.draw(1);

    return EXIT_SUCCESS;
}