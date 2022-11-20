#pragma once

#include <vector>
#include <memory>

#include "renderer.hpp"

class StateStack;
class State;

class StateTransition
{
public:
    virtual ~StateTransition() = default;
    virtual void execute(StateStack& stack) = 0;
};

class PopState : public StateTransition
{
public:
    PopState();
    virtual void execute(StateStack& stack) override;
};

class PushState : public StateTransition
{
    std::unique_ptr<State> state;
public:
    PushState(std::unique_ptr<State> state);
    virtual void execute(StateStack& stack) override;
};

class State
{
public:
    virtual ~State() = default;
    virtual std::vector<std::unique_ptr<StateTransition>> run(Renderer& renderer) = 0;
};

class StateStack
{
public:
    std::vector<std::unique_ptr<State>> states;
    void run(Renderer& renderer);
};