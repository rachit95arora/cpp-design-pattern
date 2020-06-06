#pragma once
#include <string>
#include <memory>

/*
Builder Creational Pattern
Used to remove the construction of a complex object from its representation
Helps avoid complex constructors needing many arguments
*/

/*
Product
The final product of the builder design pattern
Includes complete definition of its setters
*/
class Sandwich
{
public:
    void addBread(const std::string& bread)
    {
        m_bread = bread;
    }
    void addPatty(const std::string& patty)
    {
        m_patty = patty;
    }
    void addSauce(const std::string& sauce)
    {
        m_sauce = sauce;
    }
    bool operator== (const Sandwich& other)
    {
        return (m_bread == other.m_bread
        and m_patty == other.m_patty
        and m_sauce == other.m_sauce);
    }
    std::string describeSandwich()
    {
        return m_bread + " with " + m_patty + " and " + m_sauce;
    }
private:
    std::string m_bread;
    std::string m_patty;
    std::string m_sauce;
};

/*
Abstract Builder
A signature for the builder intermediate object that can be derived and 
implemented in a plethora of ways to create a different product
*/

class AbstractSandwichBuilder
{
public:
    virtual ~AbstractSandwichBuilder() = default;
    virtual void createSandwich() = 0;
    virtual Sandwich* getSandwich() = 0;
    virtual std::string description() const = 0;
};

class VirtualSandwichBuilder : public AbstractSandwichBuilder
{
public:
    virtual ~VirtualSandwichBuilder() = default;

    // Product construction implementations
    virtual void buildBread() = 0;
    virtual void buildPatty() = 0;
    virtual void buildSauce() = 0;

    // Creator - Creates a new object managed by this builder
    void createSandwich() final
    {
        m_sandwich = std::make_unique<Sandwich>();
        buildBread();
        buildPatty();
        buildSauce();
    }

    // Getter - Releases ownership and returns the stored object
    Sandwich* getSandwich() final
    {
        return m_sandwich.release();
    }

    std::string description() const override
    {
        return "Virtual Builder::Unknown";
    }

protected:
    std::unique_ptr<Sandwich> m_sandwich;
};

/*
An alternate approach: Template Based Policy Design
Bread, Patty and Sauce are essentially independent of each other and can be implemented by seperate policy structs
However this method quickly goes out of hands if the number of object members to construct are many leading to too many
template arguments. It is wise to use a mix of both policies and virtual functions to achieve a reasonable balance

Pros: No virtual calls, break into independent policies that can be modified without having to redefine the constituted builder

*/

template <typename BreadBuilder, typename PattyBuilder, typename SauceBuilder>
class PolicySandwichBuilder : public AbstractSandwichBuilder
{
public:
    void createSandwich() final
    {
        m_sandwich = std::make_unique<Sandwich>();
        BreadBuilder::buildBread(m_sandwich.get());
        PattyBuilder::buildPatty(m_sandwich.get());
        SauceBuilder::buildSauce(m_sandwich.get());
    }

    Sandwich* getSandwich() final
    {
        return m_sandwich.release();
    }

    std::string description() const override
    {
        return "Virtual Builder::Unknown";
    }
protected:
    std::unique_ptr<Sandwich> m_sandwich;
};

// Bread builder Policies
struct OreganoBreadPolicy
{
    static void buildBread(Sandwich* sandwich)
    {
        sandwich->addBread("Oregano Bread");
    }
};

struct MultigrainBreadPolicy
{
    static void buildBread(Sandwich* sandwich)
    {
        sandwich->addBread("Multigrain");
    }
};

struct GarlicBreadPolicy
{
    static void buildBread(Sandwich* sandwich)
    {
        sandwich->addBread("Garlic Bread");
    }
};

// Patty Builder Policies
struct ChickenPattyPolicy
{
    static void buildPatty(Sandwich* sandwich)
    {
        sandwich->addPatty("Chicken");
    }
};

struct HamPattyPolicy
{
    static void buildPatty(Sandwich* sandwich)
    {
        sandwich->addPatty("Ham");
    }
};

struct CornPattyPolicy
{
    static void buildPatty(Sandwich* sandwich)
    {
        sandwich->addPatty("Corn");
    }
};

// Sauce Builder Policies
struct TeriyakiSaucePolicy
{
    static void buildSauce(Sandwich* sandwich)
    {
        sandwich->addSauce("Teriyaki");
    }
};
struct BBQSaucePolicy
{
    static void buildSauce(Sandwich* sandwich)
    {
        sandwich->addSauce("BBQ");
    }
};
struct SweetOnionSaucePolicy
{
    static void buildSauce(Sandwich* sandwich)
    {
        sandwich->addSauce("Sweet Onion");
    }
};