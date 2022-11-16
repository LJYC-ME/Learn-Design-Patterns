// Author: Frozen(https://github.com/AlterFrozen)

#include <iostream>
#include <string>
#include <unordered_map>

class Cat;
class CatShop;
class MyCatShop;

/* [L] Liskov Substitution Principle
@Summary: 
>> When extending a class, remember that you should be able to pass
   objects of the subclass in place of objects of the parent class 
   without breaking the client code.

   This means that the subclass should remain compatible with the 
   behavior of the superclass. When overriding a method, extend the
   base behavior rather than replacing it with something else entirely.

   Unlike other design principles which are wide open for interpretation,
   the substitution principle has a set of formal requirements for 
   subclasses, and specifically for their methods.

@Illustration:
>> Note that this principle has 7 formal requirements for subclasses!
   I will still use CatShop to illustrate these 7 demands EXCEPT the 6th demand.
   (1). Parameter types in a method of a subclass should match or be more abstract than parameter types in the method of the superclass.
   (2). The return type in a method of a subclass should match or be a subtype of the return type in the method of the superclass.
   (3). A method in a subclass shouldn’t throw types of exceptions which the base method isn’t expected to throw.
   (4). A subclass shouldn’t strengthen pre-conditions.
   (5). A subclass shouldn’t weaken post-conditions.
   (6). Invariants of a superclass must be preserved. (This is probably the least formal rule of all)
   (7). A subclass shouldn’t change values of private fields of the superclass.

   Q: Why did I not illustrate the 6th demand?
   A: The rule on invariants is the easiest to violate because you might misunderstand or 
      not realize all of the invariants of a complex class. Therefore, the safest way to
      extend a class is to introduce new fields and methods, and not mess with any existing 
      members of the superclass. Of course, that’s not always doable in real life.
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

   Cat& rent(std::string name) // (1): Maybe we can substitute std::string with class CatInfo.
   {
   // (3): If the superClass did not declare anyone cannot rent Tom, this subclass should not throw such an exception.
   // (4): Subclasses shoud not strengthen pre-conditions.
   // if (name == "Tom") throw std::runtime_error("Cannot rent Tom!");
      auto cat = cats.find(name);

   // (5): Subclasses shoud not weaken post-conditions. 
   //      The customer intends to rent Tom, so we should not offer another one although Tom is not here.
   // if (cat == cats.end()) return AnotherOne. <Pseudo Code>
      if (cat == cats.end())
            throw std::runtime_error("Failed to find the cat!");

      log[cat->first]++;

      return cat->second; // (2): It is good to return a Garfield cat, but you cannot return Animal!(Remember you are a cat shop!)
   }
private:
   // (7): A subclass shouldn’t change values of private fields of the superclass. 
   // This problem usually not exists in pure C++, because C++ has no Reflection Mechanisms.
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