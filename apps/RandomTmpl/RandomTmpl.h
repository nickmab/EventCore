#pragma once

#include <Core/Application.h>

using namespace EventCore;

class RandomTmpl: public Application
{
    virtual void Init() override;
    virtual void OnUpdate() override;
};

Application* CreateApplication(int argc, char* argv[]);


struct A
{
    A(int x, double y);
    int mX;
    double mY;

    std::string ToString() const;

    template <typename T>
    T Dog(T arg);
};

template <typename T>
T A::Dog(T arg)
{
    mY += arg;
    return T(arg);
}

template <>
float A::Dog(float arg)
{
    LOG_ERROR("Ignoring float");
    return arg;
}

struct B
{
    B(const std::string& name);
    std::string mName;

    std::string ToString() const;
};

template <typename T, typename ...Args>
T Construct(Args&&... args)
{
    return T(std::forward<Args>(args)...);
}

using FakeBaseClass = std::variant<A, B>;

std::string ToString(const FakeBaseClass&);

struct FBSVec
{
    std::vector<FakeBaseClass> mVec;
    
    template <typename T, typename ...Args>
    void emplace_back(Args&& ...args);
};

template <typename T, typename ...Args>
void FBSVec::emplace_back(Args&&... args)
{
    mVec.emplace_back(T(std::forward<Args>(args)...));
}