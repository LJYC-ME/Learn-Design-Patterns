/*[Summary]
Chain of Responsibility is a behavioral design pattern that lets you pass 
requests along a chain of handlers. Upon receiving a request, each handler 
decides either to process the request or to pass it to the next handler in the chain.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>

class MessageHandler
{
public:
    void setNext(MessageHandler* next) { this->next = next; }
    virtual void execute(std::string_view request) = 0;
protected:
    MessageHandler* next = nullptr;
};

class MessageParser
{
public:
    static std::string_view getCurrencyType(std::string_view message)
    {
        return message.substr(0, 3);
    }
};

class AsianPayment
    :public MessageHandler
{
public:
    virtual void execute(std::string_view request) override
    {
        auto ctype = MessageParser::getCurrencyType(request);
        if (ctype == "CNY" || ctype == "JPY") 
            std::cout << "[Asian Payment] >> Successful!\n";
        else if (this->next != nullptr) 
            this->next->execute(request);
        else std::cout << "[Asian Payment] >> Failed!\n";
    }
};

class AmericanPayment
    :public MessageHandler
{
public:
    virtual void execute(std::string_view request) override
    {
        auto ctype = MessageParser::getCurrencyType(request);
        if (ctype == "USD")
            std::cout << "[American Payment] >> Successful!\n";
        else if (this->next != nullptr)
            this->next->execute(request);
        else std::cout << "[American Payment] >> Failed!\n";
    }
};

int main(int argc, char* argv[])
{
    // Chain of Responsibility
    AsianPayment asianPay{};
    AmericanPayment americanPay{};
    asianPay.setNext(&americanPay);

    asianPay.execute("USD: 9.15");

    return EXIT_SUCCESS;
}

