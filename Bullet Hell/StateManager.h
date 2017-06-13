#ifndef STATEMANAGER_H
#define STATEMANAGER_H
/*
This is a stack to hold all the gamestates
When pushing a new gamestate it will be ran instead of the previous one, however we still keep
the previous state as such we can pop the current state and return to the previous one.
*/
class GameState;

class StateManager {
private:
	GameState **stack;
	int capacity;
	int nrOfObj;

	void expand();
public:
	StateManager();
	~StateManager();

	bool isEmpty();
	void push(GameState* state);
	void pop()throw(...);
	GameState* peek()throw(...);
	void clear();

};

#endif