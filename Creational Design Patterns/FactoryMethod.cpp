/*[Summary]
Factory Method is a creational design pattern that provides 
an interface for creating objects in a superclass, but allows 
subclasses to alter the type of objects that will be created.
*/

#include <iostream>
#include <vector>
#include <memory>

// Products
class Button
{
public:
    virtual void render() = 0;
};

class DesktopButton
:public Button
{
public:
    virtual void render()
    {
        std::cout << "Rendering>> Desktop Button\n";
    }
};

class MobileButton
:public Button
{
public:
    virtual void render()
    {
        std::cout << "Rendering>> Mobile Button\n";
    }
};

// Factories
class UI
{
public:
    void renderComponents()
    {
        for (const auto& button : this->buttons)
        {
            button->render();
        }
    }

    virtual void createButton() = 0;

protected:
    std::vector<std::shared_ptr<Button>> buttons;
};

class DesktopUI
:public UI
{
public:
    virtual void createButton()
    {
        this->buttons.emplace_back(std::make_shared<DesktopButton>());
    }
};

class MobileUI
:public UI
{
public:
    virtual void createButton()
    {
        this->buttons.emplace_back(std::make_shared<MobileButton>());
    }
};

#define PLATFORM_DESKTOP
#undef PLATFORM_MOBILE

int main(int argc, char argv[])
{
#if defined(PLATFORM_DESKTOP)
    std::unique_ptr<UI> sys_ui = std::make_unique<DesktopUI>();
#elif defined(PLATFORM_MOBILE)
    std::unique_ptr<UI> sys_ui = std::make_unique<MobileUI>();
#endif

    sys_ui->createButton();
    
    sys_ui->renderComponents();

    return EXIT_SUCCESS;
}