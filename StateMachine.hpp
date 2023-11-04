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

class State{
    public:
        State(int _id,string name);
        State() = delete;
        void update();
        void add_action(Action& aux);
        int getId()const;
    private:
        std::vector<Action> actions;
        int id{};
        string name{};

};

class StateMachine{
    public:
        StateMachine(State* _inicial);
        void update();
        void add_element(State* initial_state, pair <State*, Transition> transition_to_state);
        void check_for_transitions();
    private:
        State* p_actual;
        std::map<State*, std::map<State*, Transition>> mapa;
};