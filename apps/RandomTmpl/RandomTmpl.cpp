#include <pch.h>

#include "RandomTmpl.h"

namespace EventCore {
    Application* CreateApplication(int argc, char* argv[])
    {
        return new ::RandomTmpl();
    }
}

using namespace EventCore;

void RandomTmpl::Init()
{
    FBSVec vec;
    vec.emplace_back<A>(3, -5.4);
    std::get<A>(vec.mVec[0]).Dog(3);
    vec.emplace_back<B>("Sou uma abelha");
    
    for (FakeBaseClass& c : vec.mVec)
    {
        LOG_WARN(ToString(c));
    }
}

void RandomTmpl::OnUpdate()
{
}

A::A(int x, double y)
    : mX(x)
    , mY(y)
{
    LOG_CRITICAL("Fresh instance of A");
}

std::string A::ToString() const
{
    std::stringstream ss;
    ss << "Instance of A with mX(" << mX << ") and mY(" << mY << ")";
    return ss.str();
}

B::B(const std::string& name)
    : mName(name)
{
    LOG_CRITICAL("Fresh instance of B");
}

std::string B::ToString() const
{
    std::stringstream ss;
    ss << "Instance of B with mName(" << mName << ")";
    return ss.str();
}

std::string ToString(const FakeBaseClass& fcc)
{
    return std::visit(
        [](const auto& arg) -> std::string {
            return arg.ToString();
        }, fcc);
}