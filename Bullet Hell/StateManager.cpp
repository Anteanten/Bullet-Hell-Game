#include "StateManager.h"
#include "GameState.h"

void StateManager::expand() {
	//Most likely there will not be many states in the stack at one time as such we dont require big expands
	capacity += 1;
	//Create a temp double pointer with higher capacity and assign old values
	GameState** temp = new GameState*[capacity];
	for (int i = 0; i < nrOfObj; i++) {
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

StateManager::~StateManager() {
	for (int i = 0; i < capacity; i++) {
		delete stack[i];
	}
	delete[] stack;
}

bool StateManager::isEmpty() {
	bool returnBool = false;
	if (nrOfObj == 0) {
		returnBool = true;
	}
	return returnBool;
}

void StateManager::push(GameState* state) {
	if (capacity == nrOfObj) {
		expand();
	}
	stack[nrOfObj++] = state;
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

GameState* StateManager::peek()throw(...) {
	GameState *temp;
	if (nrOfObj == 0) {
		throw "StateManager is empty";
	} else {
		temp = stack[nrOfObj - 1];
	}
	return temp;
}

void StateManager::clear() {
	if (nrOfObj != 0) {
		for (int i = 0; i < nrOfObj; i++) {
			delete stack[i];
			stack[i] = nullptr;
		}
		nrOfObj = 0;
	}
}
