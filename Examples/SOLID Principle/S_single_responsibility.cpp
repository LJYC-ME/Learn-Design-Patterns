// Author: Frozen(https://github.com/AlterFrozen)

#include <iostream>
#include <string>
#include <unordered_map>

class Cat;
class CatShop;

/* [S] Single Responsibility Principle
@Summary: 
>> A class should have just one reason to change.

@Illustration:
>> The CatShop should change only when the trading
   strategy changes. Any changes in Cat should not
   affect CatShop. For example, if we modify the 
   reaction of touch() from "Meow~" to "Meow~Meow~", 
   there are no changes in CatShop.
*/
class Cat
{
public:
    void touch()
    {
        //std::cout << "Meow~\n";
        std::cout << "Meow~Meow~\n";
    };
private:
    unsigned int age;
};

class CatShop
{
public:
    CatShop(){cats["Tom"];}

    Cat& rent(std::string name)
    {
        auto cat = cats.find(name);
        if (cat == cats.end())
            throw std::runtime_error("Failed to find the cat!");
      
        return cat->second;
    }

protected:
    std::unordered_map<std::string,Cat> cats;
};


int main(int argc, char* argv[])
{
    CatShop petner{};
    auto& cat_tom = petner.rent("Tom");

    cat_tom.touch();
    return EXIT_SUCCESS;
}