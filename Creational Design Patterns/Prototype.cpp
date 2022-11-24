/*[Summary]
Prototype is a creational design pattern that lets you copy existing 
objects without making your code dependent on their classes.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

class PrototypeTimer
{
public:
    virtual std::unique_ptr<PrototypeTimer> clone() const = 0;
    virtual void showTime() const = 0;
};

class PrototypeRegistryTimer
{
public:
    void addPrototype(std::string id, const PrototypeTimer* p_prototype)
    {
        if (this->prototypes.find(id) != this->prototypes.end())
            throw std::runtime_error("ID conflicted!");
        this->prototypes[id] = p_prototype;
    }

    const PrototypeTimer* getPrototype(std::string id) const
    {
        auto prototype = this->prototypes.find(id);
        if (prototype == this->prototypes.end())
            throw std::runtime_error("Failed to find the prototype!");
        return  prototype->second;
    }
private:
    std::unordered_map<std::string, const PrototypeTimer*> prototypes;
};

// Items which is complex but we often use some kinds of them.
class Timer
    :public PrototypeTimer
{
public:
    Timer() = delete;
    Timer(float init_cnt, float div) : cnt{ init_cnt }, div{ div } {};
    Timer(const Timer& copier) // Note that we should use the deep copy
    {
        this->cnt = copier.cnt;
        this->div = copier.div;
    }

    virtual std::unique_ptr<PrototypeTimer> clone() const
    {
        return std::make_unique<Timer>(*this); // copy constructor
    }

    virtual void showTime() const
    {
        std::cout << "Current Time: " << this->cnt / this->div << std::endl;
    }

private:
    float cnt = 0.0f; // suppose that cnt presents the count of seconds.
    float div = 1.0f;
};

int main(int argc, char argv[])
{
    // init system
    PrototypeRegistryTimer timerRegistry{};
    const Timer timer_sec{ 120, 1 };
    const Timer timer_min{ 120,60 };
    timerRegistry.addPrototype("Timer Sec", &timer_sec);
    timerRegistry.addPrototype("Timer Min", &timer_min);

    // Client who does not care about the Timer class but need them.
    auto clientTimerSec = timerRegistry.getPrototype("Timer Sec")->clone();
    auto clientTimerMin = timerRegistry.getPrototype("Timer Min")->clone();
    clientTimerSec->showTime();
    clientTimerMin->showTime();
    return EXIT_SUCCESS;
}