// Author: Frozen(https://github.com/AlterFrozen)

#include <iostream>
#include <string>
#include <unordered_map>

class Cat;
class CatShop;
class MyCatShop;

/* [D] Dependency Inversion Principle
@Summary: 
>> High-level classes shouldn’t depend on low-level classes. 
   Both should depend on abstractions. Abstractions shouldn’t 
   depend on details. Details should depend on abstractions.

   <Low-level classes>
   implement basic operations such as working with a disk, 
   transferring data over a network, connecting to a database, etc.

   <High-level classes>
   contain complex business logic that directs low-level classes
   to do something.

   The dependency inversion principle often goes along with the 
   open/closed principle

@Illustration:
>> This time, we will focus on Purchasing Cat Food.
   Please look at main() and compare class BadCatShop with GoodCatShop
   GoodCatShop has an Abstraction Layer, which makes purchasing more flexible.
*/

class CatFoodVendor
{
public:
    CatFoodVendor() = delete;
    CatFoodVendor(float price):price{price}{};

    virtual float purchase(float money) = 0;

    bool inBusiness(){ return true; }
protected:
    float price;
};

class CatFoodVendorCN
:public CatFoodVendor
{
public:
    CatFoodVendorCN() = delete;
    CatFoodVendorCN(float price):CatFoodVendor{price}{};

    virtual float purchase(float money)
    {
        return money / price;
    }
protected:
    float price;
};

class CatFoodVendorJP
:public CatFoodVendor
{
public:
    CatFoodVendorJP() = delete;
    CatFoodVendorJP(float price):CatFoodVendor{price}{};

    virtual float purchase(float money)
    {
        return money / price;
    }
protected:
    float price;
};

class BadCatShop
{
public:
    float purchasingCatFood(float money, CatFoodVendorCN& catFoodVendorCN)
    {
        if (!catFoodVendorCN.inBusiness()) return 0;
        return catFoodVendorCN.purchase(money);
    }
};

class GoodCatShop
{
public:
    float purchasingCatFood(float money, CatFoodVendor& catFoodVendor)
    {
        if (!catFoodVendor.inBusiness()) return 0;
        return catFoodVendor.purchase(money);
    }
};

int main(int argc, char* argv[])
{
    float foodCnt = 0.0f;
    CatFoodVendorCN vendorCN{1.0f};
    CatFoodVendorJP vendorJP{1.0f * 0.9}; // Discounting

    BadCatShop badCatShop;
    GoodCatShop goodCatShop;

    foodCnt += badCatShop.purchasingCatFood(100, vendorJP); // !!! Oshii
    foodCnt += goodCatShop.purchasingCatFood(100, vendorJP);
    
    return EXIT_SUCCESS;
}