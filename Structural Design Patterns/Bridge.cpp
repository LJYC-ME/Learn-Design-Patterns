/*[Summary]
Bridge is a structural design pattern that lets you split a large class 
or a set of closely related classes into two separate hierarchies—abstraction 
and implementation—which can be developed independently of each other.

Note: Divide the monolithic class into 2 parts: interface and implementation,
      and then manage these two parts separately.
*/

#include <iostream>
#include <string>
#include <format>

class Device
{
public:
    virtual void info() { std::cout << std::format("Power>> {}\nFreq>> {}\n", this->power, this->frequency); }
    virtual void togglePower() { this->power = !(this->power); }
    virtual void setFrequency(float freq) { this->frequency = freq; }
protected:
    bool power = false;
    float frequency = 0;
};

class Remote
{
public:
    Remote() = delete;
    Remote(Device* host) : host{ host } {};
    // interfaces
    void key_power() { host->togglePower(); }
protected:
    Device* host;
};

class AdvancedRemote
    :public Remote
{
public:
    void VIPChannel() { this->host->setFrequency(3.1415); }
};


int main(int argc, char* argv[])
{
    Device TV{};
    AdvancedRemote myRemote{ &TV };
    TV.info();
    myRemote.key_power();
    myRemote.VIPChannel();
    TV.info();

    return EXIT_SUCCESS;
}