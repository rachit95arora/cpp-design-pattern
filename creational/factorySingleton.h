#pragma once
#include "builder.h"

#include <unordered_map>
/*
Factory model allows returning a base type that has a defined interface that can be implemented/built upon
by derived classes. Such a factory object can take a runtime parameter and return an appropriate derived class
registered with it

Singleton Design Pattern is used to ensure a master instance of a given class that is easy to access globally
It can be implemented by returning a private static instance of a class itself using a public getter

Caveat: All constructors should be private for such a singleton class to prevent rogue instances breaking
        the singleton invariant
*/

/* 
Here we implement a singleton factory for the sandwich builder abstract class that supports:
- Registering any number of unique sandwich builder classes deriving from AbstractSandwichBuilder
- Returning a builder corresponding to a requested description at runtime
*/

class SandwichBuilderFactorySingleton
{
    public:
    static SandwichBuilderFactorySingleton* getSandwichFactory()
    {
        static SandwichBuilderFactorySingleton s_instance;
        return &s_instance;
    }

    AbstractSandwichBuilder* getSandwichBuilder(const std::string& description)
    {
        auto it = m_builders.find(description);
        if (it == m_builders.end()) return nullptr;
        return it->second;
    }

    // Returns true if builder replaced an existing one
    bool registerSandwichBuilder(AbstractSandwichBuilder* builder)
    {
        bool duplicateDesciption = false;
        if (m_builders.find(builder->description()) != m_builders.end())
            duplicateDesciption = true;
        m_builders[builder->description()] = builder;
        return duplicateDesciption;
    }

    private:
    // Private constructor necessary for singleton instance
    SandwichBuilderFactorySingleton() = default;
    ~SandwichBuilderFactorySingleton() = default;
    SandwichBuilderFactorySingleton(const SandwichBuilderFactorySingleton&) = delete;
    SandwichBuilderFactorySingleton& operator=(const SandwichBuilderFactorySingleton&) = delete;

    private:
    std::unordered_map<std::string, AbstractSandwichBuilder*> m_builders;
};
