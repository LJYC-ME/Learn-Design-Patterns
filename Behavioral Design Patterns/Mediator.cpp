/*[Summary]
Mediator is a behavioral design pattern that lets you reduce chaotic 
dependencies between objects. The pattern restricts direct communications 
between the objects and forces them to collaborate only via a mediator object.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <memory>
#include <unordered_map>

class Component
{
public:
    virtual void execute() = 0;
};

class TextField
    :public Component
{
public:
    virtual void execute() override
    {
        std::cout << "[Text] >> ";
        std::cin >> this->text;
    }

    std::string_view getContent() const { return this->text; }
protected:
    std::string text;
};

class CheckBox
    :public Component
{
public:
    virtual void execute() override
    {
        this->checked = !(this->checked);
    }
    bool isChecked() const { return this->checked; }
protected:
    bool checked = false;
};

class Dialog // Mediator
{
public:
    Dialog()
    {
        this->components["CheckBox"] = std::make_unique<CheckBox>();
        this->components["TextField"] = std::make_unique<TextField>();
    }
    std::unique_ptr<Component>& click(std::string_view id)
    {
        // This function may be implemented via Chain of Responsibility pattern.
        if (id == "CheckBox") this->components["CheckBox"]->execute();
        else if (id == "TextField")
        {
            if (dynamic_cast<CheckBox*>(this->components["CheckBox"].get())->isChecked())
                std::cerr << "Text Field is locked!\n"; 
            else
                this->components["TextField"]->execute();
        }
        else throw std::runtime_error("Undefined Behavior!");
    }
protected:
    std::unordered_map<std::string, std::unique_ptr<Component>> components;
};

int main(int argc, char* argv[])
{
    Dialog dialog{};
    dialog.click("TextField");

    dialog.click("CheckBox");
    dialog.click("TextField");

    return EXIT_SUCCESS;
}

