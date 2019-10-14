#pragma once

#include <SDL2/SDL.h>

class BaseState {
  public:
    virtual ~BaseState()                       = default;
    int width                                  = 0;
    int height                                 = 0;
    double ratio                               = 0;
    virtual void hardInit()                    = 0;
    virtual void softInit()                    = 0;
    virtual void display()                     = 0;
    virtual void unInit()                      = 0;
    virtual void handleInput(SDL_Event &event) = 0;
    virtual void update(double dt)             = 0;
    
};
