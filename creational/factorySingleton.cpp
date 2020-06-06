#include "factorySingleton.h"

#include <assert.h>
#include <iostream>

struct OreganoChickenBBQBuilder : public PolicySandwichBuilder<OreganoBreadPolicy, ChickenPattyPolicy, BBQSaucePolicy>
{
    std::string description() const override
    {
        return "Policy::OreganoBread::ChickenPatty::BBQSauce";
    }
};

struct MultigrainHamSweetOnionBuilder : public PolicySandwichBuilder<MultigrainBreadPolicy, HamPattyPolicy, SweetOnionSaucePolicy>
{
    std::string description() const override
    {
        return "Policy::MultigrainBread::HamPatty::SweetOnionSauce";
    }
};

int main()
{
    auto factory = SandwichBuilderFactorySingleton::getSandwichFactory();
    auto builder1 = new OreganoChickenBBQBuilder();
    auto builder2 = new MultigrainHamSweetOnionBuilder();

    assert(!factory->registerSandwichBuilder(builder1));
    assert(!factory->registerSandwichBuilder(builder2));
    assert(factory->registerSandwichBuilder(builder2));

    assert(factory->getSandwichBuilder(builder1->description()) == builder1);
    assert(factory->getSandwichBuilder(builder2->description()) == builder2);
    assert(factory->getSandwichBuilder("garbage") == nullptr);

    std::cout<<"All checks pass\n";
    return 0;
}