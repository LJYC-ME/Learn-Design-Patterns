/* [Summary]
Observer is a behavioral design pattern that lets you define a 
subscription mechanism to notify multiple objects about any events 
that happen to the object they’re observing.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <vector>
#include <memory>

class Subscriber
{
public:
    virtual void notify(std::string_view message)
    {
        std::cout << message;
    }
};

class Publisher
{
public:
    void addSubscriber(std::shared_ptr<Subscriber> subscriber)
    {
        this->subsribers.emplace_back(subscriber);
    }

    virtual void notifySubscribers(std::string_view message)
    {
        for (const auto& subsriber : this->subsribers)
            subsriber->notify(message);
    }
protected:
    std::vector<std::shared_ptr<Subscriber>> subsribers;
};

class FacebookUser
    :public Subscriber
{
public:
    void notify(std::string_view message) override
    {
        std::cout << "Facebook>> " << message << '\n';
    }
};

class TwitterUser
    :public Subscriber
{
public:
    void notify(std::string_view message) override
    {
        std::cout << "Twitter>> " << message << '\n';
    }
};

int main(int argc, char* argv[])
{
    Publisher myApp{};
    myApp.addSubscriber(std::make_shared<FacebookUser>());
    myApp.addSubscriber(std::make_shared<TwitterUser>());

    myApp.notifySubscribers("Hello World\n");

    return EXIT_SUCCESS;
}

