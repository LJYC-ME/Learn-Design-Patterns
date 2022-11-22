/*[Summary]
Abstract Factory is a creational design pattern that lets you 
produce families of related objects without specifying their 
concrete classes.

Note: Many creational patterns start from Factory Method,
      and thus they look similar.
      The Abstract Factory just integrates all create() existing
      in the previous Factory Method to clarify the duty of Factory.
      (note that the create() is only one function of a factory)

      Therefore, I will just need to modify the code of Factory Method.
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

// Abstract Factories
class UIComponentsCreator
{
public:
    virtual std::shared_ptr<Button> createButton() = 0;
};

class UIComponentsCreator_Desktop
:public UIComponentsCreator
{
public:
    virtual std::shared_ptr<Button> createButton()
    {
        return std::make_shared<DesktopButton>();
    }
};

class UIComponentsCreator_Mobile
:public UIComponentsCreator
{
public:
    virtual std::shared_ptr<Button> createButton()
    {
        return std::make_shared<MobileButton>();
    }
};

#define PLATFORM_DESKTOP
#undef PLATFORM_MOBILE

// Factories
class UI
{
public:
    void initialization()
    {
#if defined(PLATFORM_DESKTOP)
    this->factory = std::make_unique<UIComponentsCreator_Desktop>();
#elif defined(PLATFORM_MOBILE)
    this->factory = std::make_unique<UIComponentsCreator_Mobile>();
#endif
    }

    void renderComponents()
    {
        auto btn_confirm = this->factory->createButton(); // The resposibility for creation has been transferred to Abstract Factory.
        btn_confirm->render();
    }

protected:
    std::unique_ptr<UIComponentsCreator> factory; // Can be implemented via Singleton.
};


int main(int argc, char argv[])
{
    UI sys_ui;
    sys_ui.initialization();
    sys_ui.renderComponents();

    return EXIT_SUCCESS;
}