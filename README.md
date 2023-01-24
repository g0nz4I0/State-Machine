# State-Machine
Simple state machine implementation based on maps

It's implemented using two maps, the first one stores an State* and a map.
The second map contains an State* and the Transition that takes you to that State*

Actions and Transitions are implemented as lambdas

|Function | Task|
| :--- | :--- |
| **State**| |
| add_action() | appends an action to State, actions are stored in a vector |
| update() | calls every action on the vector |
|**StateMachine**| |
| update() | calls *check_for_transition()* &  *state.update()* for the new state |
| add_element() | inserts an State and its State *(new state)*<->Transition pair |
| check_for_transitions() | access the map using the actual State* as a key, and then navigates the second map to find the only transition active, it also transitions to the desired State |


<img align="left" width="380" height="300" src=https://user-images.githubusercontent.com/58850783/214279781-23710bf1-fd47-40d5-9fce-ffe2c1ca9460.png>

