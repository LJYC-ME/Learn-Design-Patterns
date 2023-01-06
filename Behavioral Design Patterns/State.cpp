/*[Summary]
State is a behavioral design pattern that lets an object alter its 
behavior when its internal state changes. It appears as if the object 
changed its class.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <vector>
#include <memory>

class Player
{
public:
    Player() { this->state = std::make_shared<Idle>(*this); }

    void beginRun() { this->state->beginRun(); }
    void endRun() { this->state->endRun(); }
    void beginFly() { this->state->beginFly(); }
    void endFly() { this->state->endFly(); }
public:
    struct State // Context
    {
        State() = delete;
        State(Player& host) :host{ host } {};

        virtual void beginRun() = 0;
        virtual void endRun() = 0;
        virtual void beginFly() = 0;
        virtual void endFly() = 0;
    protected:
        Player& host;
    };
    struct Idle
        :public Player::State
    {
        Idle() = delete;
        Idle(Player& host) :State{ host } { std::cout << "Idling\n"; }

        void beginRun() override
        {
            this->host.changeState(std::make_shared<Running>(this->host));
        }
        void endRun() override {};
        void beginFly() override
        {
            this->host.changeState(std::make_shared<Flying>(this->host));
        }
        void endFly() override {};
    };
    struct Flying
        :public Player::State
    {
        Flying() = delete;
        Flying(Player& host) :State{ host } { std::cout << "Flying\n"; }

        void beginRun() override {};
        void endRun() override {};
        void beginFly() override {};
        void endFly() override
        {
            this->host.changeState(std::make_shared<Idle>(this->host));
        }
    };
    struct Running
        :public Player::State
    {
        Running() = delete;
        Running(Player& host) :State{ host } { std::cout << "Running\n"; }

        void beginRun() override
        {
            this->host.changeState(std::make_shared<Running>(this->host));
        }
        void endRun() override
        {
            this->host.changeState(std::make_shared<Idle>(this->host));
        };
        void beginFly() override
        {
            this->host.changeState(std::make_shared<Flying>(this->host));
        }
        void endFly() override {};
    };
public:
    void changeState(std::shared_ptr<State> newState)
    {
        this->state = newState;
    }
protected:
    std::shared_ptr<State> state;
};

int main(int argc, char* argv[])
{
    Player player{};
    player.beginRun();
    player.beginFly();
    player.endRun();
    player.endFly();
    
    return EXIT_SUCCESS;
}

