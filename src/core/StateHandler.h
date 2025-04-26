#pragma once
#include <memory>
#include <stack>
#include "IGameState.h"

class StateHandler {
public:
    void changeState(std::shared_ptr<IGameState> newState);
    void pushState(std::shared_ptr<IGameState> newState);
    void popState();
    std::shared_ptr<IGameState> getCurrentState();

private:
    std::stack<std::shared_ptr<IGameState>> states;
};
