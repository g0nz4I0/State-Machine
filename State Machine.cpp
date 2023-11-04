#include<functional>
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<thread>
#include<chrono>
#include<cstdlib>

using namespace std;
using namespace chrono;

using Action = std::function<void()> ;
using Transition = std::function<bool()> ;

class State { // stores an id for comparison purposes, a name for clarification and a vector of the actions it can perform
public:
    State(int _id, string _name) : 
        id(_id), name(_name) {}
    State() = default;

    void update() {
        for (auto& e : actions)
            e();
    }
    void add_action(Action& aux) { //adds an action to a State
        actions.push_back(aux);
    }
    int getId()const {
        return id;
    }

private:
    std::vector<Action> actions;
    string name{};
    int id{};

};

class StateMachine {   // Estado inicial, estado actual, mapa transiciones  
public:
   
    StateMachine(State* _inicial) {
        p_actual = _inicial;
    }

    void update() {
        check_for_transitions();
        p_actual->update();
    }

    void add_element(State* initial_state, pair <State*, Transition> transition_to_state) {
        mapa[initial_state][transition_to_state.first] = transition_to_state.second;
    }
    void check_for_transitions() {   
        for (const auto& transition_to_state : mapa[p_actual]) {
            if (transition_to_state.second()) { // transition_to_state.second() is a function that returns a bool if you need to change states
                p_actual = transition_to_state.first; //p_actual now points to the target state of the transition that returned true
                break;
            }
        }
      return;
    }
    private:
        map<State*,map<State*, Transition>> mapa;
        State* p_actual;
};

int main() {
    int i = 1;
    State s1(1, "SLEEPING");
    State s2(2, "WORKING");
    State* p_s1 = &s1;
    State* p_s2 = &s2;

    StateMachine machine(p_s1);
    
    Transition t = [&i]() {
        return i % 2;
    };

    Action a1 = []() {
        cout << "\ndummy action";
    };
    Action a2 = [](){
        cout<<"\nanother dummy action";
    };
    s1.add_action(a1);
    s2.add_action(a2);
    machine.add_element(p_s1, { p_s2,t  });
    machine.add_element(p_s2, { p_s1,t  });
    while (true) {
        machine.update();
        this_thread::sleep_for(seconds(1));
        i = rand() % 50;
    }
    return 0;
}
