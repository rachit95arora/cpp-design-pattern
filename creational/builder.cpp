#include "builder.h"

#include <iostream>
#include <assert.h>

// Concrete Sandwich Builders
class MultigrainChickenBBQSandwichBuilder : public VirtualSandwichBuilder
{
public:
    void buildBread() override
    {
        m_sandwich->addBread("Multigrain");
    }
    void buildPatty() override
    {
        m_sandwich->addPatty("Chicken");
    }
    void buildSauce() override
    {
        m_sandwich->addSauce("BBQ");
    }
};

class OreganoHamSweetOnionSandwichBuilder : public VirtualSandwichBuilder
{
public:
    void buildBread() override
    {
        m_sandwich->addBread("Oregano Bread");
    }
    void buildPatty() override
    {
        m_sandwich->addPatty("Ham");
    }
    void buildSauce() override
    {
        m_sandwich->addSauce("Sweet Onion");
    }
};

// yuck, who needs this builder
class GarlicBreadCornTeriyakiSandwichBuilder : public VirtualSandwichBuilder
{
public:
    void buildBread() override
    {
        m_sandwich->addBread("Garlic Bread");
    }
    void buildPatty() override
    {
        m_sandwich->addPatty("Corn");
    }
    void buildSauce() override
    {
        m_sandwich->addSauce("Teriyaki");
    }
};

using AlternateGarlicBreadCornTeriyakiSandwichBuilder = PolicySandwichBuilder<GarlicBreadPolicy, CornPattyPolicy, TeriyakiSaucePolicy>;

int main()
{
    GarlicBreadCornTeriyakiSandwichBuilder virtualBuilder;
    AlternateGarlicBreadCornTeriyakiSandwichBuilder policyBuilder;
    virtualBuilder.createSandwich();
    policyBuilder.createSandwich();

    Sandwich *a = virtualBuilder.getSandwich(), *b = policyBuilder.getSandwich();
    std::cout<<a->describeSandwich()<<std::endl;
    std::cout<<b->describeSandwich()<<std::endl;
    assert(*a == *b);
    std::cout<<"The builders create identical objects!\n";
    return 0;
};