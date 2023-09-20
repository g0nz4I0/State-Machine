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

typedef function<void()> Action;
typedef function<bool()> Transition;

class State { // stores an id for comparison purposes, a name for clarification and a vector of the actions it can perform
public:
    State(int _id, string _name) : id(_id), name(_name) {}
    void add_action(Action& aux) { //adds an action to a State
        actions.push_back(aux);
    }
    void update() {
        for (auto& e : actions)
            e();
    }
    State() {
        name = "";
    }
    int getId() {
        return id;
    }

private:
    std::vector<Action> actions;
    string name{};
    int id{};

};

class StateMachine {   // Estado inicial, estado actual, mapa transiciones  
public:
    State* p_actual;
    StateMachine(State* _inicial) {
        p_actual = _inicial;
    }
    map<State*,map<State*, Transition>> mapa;

    void update() {
        check_for_transitions();
        p_actual->update();
    }

    void add_element(State* initial_state, pair <State*, Transition> pareja) {
        mapa[initial_state][pareja.first] = pareja.second;
    }
    bool check_for_transitions() { // Transicionar Devuelve True si hay que transicionar    
        for (const auto& e : mapa[p_actual]) {
            if (e.second()) {
                p_actual = e.first;
                return true;
            }
        }
        return false;
    }
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
