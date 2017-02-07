#ifndef SDL_GameState_h
#define SDL_GameState_h

#include <string>
#include <iostream>
#include <vector>


/* book version differs from shipped framework
class GameState
{
public:
virtual void update() = 0; //pure virtual function page 103
virtual void render() = 0;
virtual bool onEnter() = 0;
virtual bool onExit() = 0;
virtual std::string getStateID() const = 0;

};
*/

#include <string>
#include <vector>

class GameState
{
public:
    
    virtual ~GameState() {}
    
    virtual void update() = 0;
    virtual void render() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual void resume() {}
    
    virtual std::string getStateID() const = 0;
    
protected:
    
    GameState() : m_loadingComplete(false), m_exiting(false)
    {
        
    }
    
    bool m_loadingComplete;
    bool m_exiting;
    
    std::vector<std::string> m_textureIDList;
};




#endif