/*[Summary]
Facade is a structural design pattern that provides a simplified 
interface to a library, a framework, or any other complex set of classes.

Note: Do not make a "god class", try to refine your facade.
*/

#include <iostream>
#include <string>
#include <format>
#include <vector>

class Network
{
    enum class State : uint32_t {INIT = 0x1, LOGIN = 0x2, COMFIRM = 0x4, READY = 0x7};
public:
    void init() { this->state |= static_cast<uint32_t>(State::INIT); }
    void logIn() { this->state |= static_cast<uint32_t>(State::LOGIN); }
    void confirm() { this->state |= static_cast<uint32_t>(State::COMFIRM); }

    void visit(std::string url)
    {
        if (this->state != static_cast<uint32_t>(Network::State::READY)) 
            std::cout << "Error\n";
        else std::cout << std::format("Visit {}\n", url);
    }
private:
    uint32_t state = 0;
};

class NetFacade
{
public:
    NetFacade()
    {
        this->net.init();
        this->net.logIn();
        this->net.confirm();
    }
    void connect(std::string url)
    {
        this->net.visit(std::move(url));
    }
private:
    Network net;
};

int main(int argc, char* argv[])
{
    NetFacade client;
    client.connect("www.bing.com");

    return EXIT_SUCCESS;
}