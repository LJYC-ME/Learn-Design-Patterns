// Author: Frozen(https://github.com/AlterFrozen)

#include <iostream>
#include <string>
#include <unordered_map>

class Cat;
class CatShop;
class MyCatShop;

/* [I] Interface Segregation Principle
@Summary: 
>> Clients shouldn’t be forced to depend on methods they do not use.
   Try to make your interfaces narrow enough that client classes don’t have to implement behaviors they don’t need.
   
   <Two different SEGREGATION scenarios>
   (1.Interface is Thin) The clients want to finish one task only in one line.
   (2.Interface is Redundant) The clients finished the task in one line but also did anything else.

@Illustration:
>> (1): Look at the function buy() in class CatShop, we should encapsulate trivial steps for clients. (Just pay and let us do the rest!)
>> (2): No specific code here, but one example to illustrate the Redundancy: 
        If you want to take over a shop where people can drink and play games.
        Ususally,these 2 things are roughly divided into 2 categories - food and entertainment.
        What we need to do next is to strip some of the functions we need from these 2 generic concepts,
        and then discard other unnecessary functions.
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
    struct CatGiftPack
    {
        Cat cat;
        //.. Other things, such as coupon, cat food and so on.
    };
public:
    CatShop(){cats["Tom"];}

    Cat& rent(std::string name)
    {
        auto cat = cats.find(name);
        if (cat == cats.end())
            throw std::runtime_error("Failed to find the cat!");
      
        return cat->second;
    }

    CatGiftPack buy(std::string name, int money)
    {
        auto& cat = rent(name);
        if (money < 100)
            throw std::runtime_error("Failed to buy the cat!");
        CatGiftPack giftPack;
        giftPack.cat = cat;
        //... giftPack.food = goldKera; ...
        
        // Remove this cat from shop (omitted)
        return giftPack;
    };

protected:
    std::unordered_map<std::string,Cat> cats;
};

int main(int argc, char* argv[])
{
    CatShop catShop{};
    auto& cat_tom = catShop.rent("Jim");

    auto package = catShop.buy("Jim", 100);
    return EXIT_SUCCESS;
}