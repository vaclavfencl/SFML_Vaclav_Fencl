#include "StateHandler.h"

void StateHandler::pushState(std::shared_ptr<IGameState> state) {
    states.push(state);
}

void StateHandler::popState() {
    if (!states.empty()) states.pop();
}

void StateHandler::changeState(std::shared_ptr<IGameState> state) {
    popState();
    pushState(state);
}

std::shared_ptr<IGameState> StateHandler::getCurrentState() {
    if (!states.empty()) return states.top();
    return nullptr;
}
