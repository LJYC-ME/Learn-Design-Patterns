/*[ Summary ]
Strategy is a behavioral design pattern that lets you define 
a family of algorithms, put each of them into a separate class, 
and make their objects interchangeable.
*/

#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <vector>
#include <memory>

class Player;
class PhysicalAttack;
class MagicAttack;

class AttackStrategy
{
public:
    virtual bool operator()(Player& actor, Player& target) = 0;
};

class Player
{
public:
    struct State
    {
        uint32_t health = 0;
        uint32_t magic = 0;
        uint32_t strength = 0;
        uint32_t intelligence = 0;
    };
public:
    Player() = delete;
    Player(State state, std::shared_ptr<AttackStrategy> attckStrategy) :
        state{ state }, attackStrategy{ attckStrategy } { };
public:
    State& getState() { return this->state; }
    void attack(Player& target) { (*this->attackStrategy)(*this, target); }
protected:
    State state;
    std::shared_ptr<AttackStrategy> attackStrategy;
};

class PhysicalAttack
    :public AttackStrategy
{
public:
    bool operator()(Player& attacker, Player& target) override
    {
        auto& sa = attacker.getState();
        auto& st = attacker.getState();
        st.health -= sa.strength;
        std::cout << std::format("Physical Attack Damage: {}\n", sa.strength);
        return true;
    }
};

class MagicAttack
    :public AttackStrategy
{
public:
    bool operator()(Player& attacker, Player& target) override
    {
        auto& sa = attacker.getState();
        if (sa.magic < 1) return false;
        else sa.magic -= 1;
        auto& st = attacker.getState();
        st.health -= sa.strength + sa.intelligence;
        std::cout << std::format("Magic Attack Damage: {} (MP - {})\n", sa.strength + sa.intelligence, 1);
        return true;
    }
};

int main(int argc, char* argv[])
{
    auto skill_slash = std::make_shared<PhysicalAttack>();
    auto skill_fireBall = std::make_shared<MagicAttack>();

    Player mercenary{ 
        Player::State
        {
            .health = 10,
            .magic = 3,
            .strength = 5,
            .intelligence = 2
        },
        skill_slash };

    Player magician{
        Player::State
        {
            .health = 8,
            .magic = 10,
            .strength = 1,
            .intelligence = 5
        },
        skill_fireBall };

    std::cout << "Mercenary -> Magician\n";
    mercenary.attack(magician);
    std::cout << "Magician -> Mercenary\n";
    magician.attack(mercenary);
    
    return EXIT_SUCCESS;
}

