// Author: Frozen(https://github.com/AlterFrozen)

#include <iostream>
#include <string>
#include <unordered_map>

class Cat;
class CatShop;
class MyCatShop;

/* [O] Open/Closed Principle
@Summary: 
>> Classes should be open for extension but closed for modification.
   The main idea of this principle is to keep existing code from 
   breaking when you implement new features.

   1. <A class is open> 
   if you can extend it, produce a subclass and do whatever you want
   with it—add new methods or fields, override base behavior, etc.
   
   2. <A class is closed>
   if it’s 100% ready to be used by other classes—its interface is 
   clearly defined and won’t be changed in the future.

@Illustration:
>> Now, I want to buy that CatShop and run by myself. So I can only
   add some small changes, and then a brand new CatShop appears.
   This time, I want to count the rent times of each cat.
   (1) class CatShop is open, so I can inherit it and build up my shop.
   (2) rent() is closed in most scenarios for cat shops.
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
        if (cats.find(name) == cats.end())
            throw std::runtime_error("Failed to find the cat!");
        return this->cats[name];
    }

protected:
    std::unordered_map<std::string,Cat> cats;
};


class MyCatShop
:public CatShop
{
public:
    MyCatShop():CatShop{}{cats["Jim"];}

    Cat& rent(std::string name)
    {
        auto cat = cats.find(name);
        if (cat == cats.end())
            throw std::runtime_error("Failed to find the cat!");

        log[cat->first]++;
        
        return cat->second;
    }
private:
    //std::unordered_map<std::string,Cat> cats;
    std::unordered_map<std::string, unsigned int> log;
};

int main(int argc, char* argv[])
{
    MyCatShop myCatShop{};
    auto& cat_tom = myCatShop.rent("Jim");

    cat_tom.touch();
    return EXIT_SUCCESS;
}