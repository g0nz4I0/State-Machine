#include "StateMachine.hpp"

State::State(int _id, string _name):id{_id},name{_name}
{
}
void State::update() {
    for (auto& e : actions)
        e();
}
void State::add_action(Action& aux) { //adds an action to a State
    actions.push_back(aux);
}
int State::getId()const {
    return id;
}


StateMachine:: StateMachine(State* _inicial) {
        p_actual = _inicial;
    }

void StateMachine::update() {
    check_for_transitions();
    p_actual->update();
}

void StateMachine::add_element(State* initial_state, pair <State*, Transition> transition_to_state) {
    mapa[initial_state][transition_to_state.first] = transition_to_state.second;
}
void StateMachine::check_for_transitions() {   
    for (const auto& transition_to_state : mapa[p_actual]) {
        if (transition_to_state.second()) { // transition_to_state.second() is a function that returns a bool if you need to change states
            p_actual = transition_to_state.first; //p_actual now points to the target state of the transition that returned true
            break;
        }
    }
    return;
}
