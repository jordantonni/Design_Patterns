#pragma once
#include <string>

/*
 * ABSTRACT:
 * Now the pimpl memeber is a polymorphic pointer to some human implementation.
 * We can pass any concrete implementation we need in to the human and it will define how the Human API is actually provided.
 * 
 * The impl is now the BRIDGE. Between the Human interface that people consume, and the actual implementation / behavoir that we exhibt.
 */

struct HumanInterface
{
    virtual void greet() = 0;
};

struct HappyHumanBridgeImpl : HumanInterface
{
    void greet() override;
};

struct AngryHumanBridgeImpl : HumanInterface
{
    void greet() override;
};


struct HumanBridge : HumanInterface
{
private:
    // This bridges the gap between the interface (The HumanBridge class)
    // and the concrete implmentation (The Happy or sad HumanBridgeImp)
    HumanInterface& impl;

public:
    HumanBridge(HumanInterface& imp);
    ~HumanBridge();;

    void greet() override;
};
