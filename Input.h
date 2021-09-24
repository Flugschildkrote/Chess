#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#define SDL_MAIN_HANDLED
#include <SDL.h>

class Input
{
public:
    Input();
    ~Input();

    void uptdateEvent();
    bool quit() const;

    bool getKey(const SDL_Scancode key) const ;
    bool getMouseButton(const Uint8 mouseButton)const;
    bool mouseMoved()const ;

    int getX() const;
    int getY() const;
    int getXRel() const;
    int getYRel() const;

    void showCursor(bool show) const;
    void lockCursor(bool lock) const;

private:
    SDL_Event mEvents;

    bool mTouches[SDL_NUM_SCANCODES];
    bool mMouseButtons[8];

    int mX;
    int mY;
    int mXRel;
    int mYRel;

    bool mQuit;
};

#endif // INPUT_H_INCLUDED
