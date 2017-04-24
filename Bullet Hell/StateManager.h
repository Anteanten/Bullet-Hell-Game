#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "GameState.h"
/*
This is a stack to hold all the gamestates
When pushing a new gamestate it will be ran instead of the previous one, however we still keep
the previous state as such we can pop the current state and return to the previous one.
*/

class StateManager {
private:
	GameState **stack;
	int capacity;
	int nrOfObj;

	void expand();
public:
	StateManager();
	~StateManager();

	void push(GameState* state);
	void pop()throw(...);
	GameState* peek()throw(...);
	void clear();

};

#endif

inline void StateManager::expand() {
	//Most likely there will not be many states in the stack at one time as such we dont require big expands
	capacity += 1;
	//Create a temp double pointer with higher capacity and assign old values
	GameState** temp = new GameState*[capacity];
	for(int i = 0; i < nrOfObj; i++){
		temp[i] = stack[i];
	}
	delete[] stack;
	stack = temp;
	temp = nullptr;
	delete[] temp;
}

StateManager::StateManager() {
	nrOfObj = 0;
	capacity = 2;
	stack = new GameState*[capacity];
	for (int i = 0; i < capacity; i++) {
		stack[i] = nullptr;
	}
}

inline StateManager::~StateManager() {
	clear();
	delete[] stack;
}

void StateManager::push(GameState* state) {
	if (capacity == nrOfObj) {
		expand();
	}
	stack[nrOfObj++] = state;
	capacity++;
}

void StateManager::pop()throw(...) {
	if (nrOfObj == 0) {
		throw "StateManager is empty";
	} else {
		delete stack[nrOfObj - 1];
		stack[nrOfObj - 1] = nullptr;
		nrOfObj--;
	}
}

inline GameState* StateManager::peek()throw(...){
	GameState *temp;
	if (nrOfObj == 0) {
		throw "StateManager is empty";
	} else {
		temp = stack[nrOfObj - 1];
	}
	return temp;
}

inline void StateManager::clear(){
	if (nrOfObj != 0) {
		for (int i = 0; i < nrOfObj; i++) {
			delete stack[i];
			stack[i] = nullptr;
		}
		nrOfObj = 0;
	}
}
