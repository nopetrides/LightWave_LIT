#ifndef SDL_GameStateMachine_h
#define SDL_GameStateMachine_h

#include "GameState.h"

/*chapter 5 code differes from shipped framework
class GameStateMachine
{
public:

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

private:

	std::vector<GameState*> m_gameStates;
};
*/

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
    
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void update();
    void render();
    
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    
    void clean();

	std::vector<GameState*>& getGameStates() { return m_gameStates; }
    
private:
    std::vector<GameState*> m_gameStates;
};


#endif