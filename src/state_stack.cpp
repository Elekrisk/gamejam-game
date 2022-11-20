#include "state_stack.hpp"

PopState::PopState() {}

void PopState::execute(StateStack& stack)
{
    stack.states.pop_back();
}

PushState::PushState(std::unique_ptr<State> state) : state{std::move(state)} {}

void PushState::execute(StateStack& stack)
{
    stack.states.push_back(std::move(state));
}

void StateStack::run(Renderer& renderer)
{
    while (!states.empty())
    {
        auto transitions = states[states.size() - 1]->run(renderer);
        for (auto &transition : transitions)
        {
            transition->execute(*this);
        }
    }
}
