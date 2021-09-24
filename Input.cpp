#include "Input.h"

Input::Input():mX(0),mY(0),mXRel(0),mYRel(0),mQuit(false)
{
    for(int i(0);i<SDL_NUM_SCANCODES;i++)
        mTouches[i] = false;

    for(int i(0); i < 8; i++)
        mMouseButtons[i] = false;
}

Input::~Input(){}

void Input::uptdateEvent()
{
    mXRel = 0;
    mYRel = 0;

    while(SDL_PollEvent(&mEvents))
    {
        switch(mEvents.type)
        {
        case SDL_KEYDOWN:
            mTouches[mEvents.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            mTouches[mEvents.key.keysym.scancode] = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mMouseButtons[mEvents.button.button] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            mMouseButtons[mEvents.button.button] = false;
            break;

        case SDL_MOUSEMOTION:
            mX = mEvents.motion.x;
            mY = mEvents.motion.y;

            mXRel = mEvents.motion.xrel;
            mYRel = mEvents.motion.yrel;
            break;

        case SDL_WINDOWEVENT:
            if(mEvents.window.event == SDL_WINDOWEVENT_CLOSE)
                mQuit = true;
            break;

        default:
            break;
        }
    }
}

bool Input::quit() const
{
    return mQuit;
}

bool Input::getKey(const SDL_Scancode key) const
{
    return mTouches[key];
}

bool Input::getMouseButton(const Uint8 mouseButton) const
{
    return mMouseButtons[mouseButton];
}

bool Input::mouseMoved() const
{
    if(mXRel == 0 && mYRel == 0)
        return false;

    return true;
}

int Input::getX() const
{
    return mX;
}

int Input::getY() const
{
    return mY;
}

int Input::getXRel() const
{
    return mXRel;
}

int Input::getYRel() const
{
    return mYRel;
}

void Input::showCursor(bool show) const
{
    if(show)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void Input::lockCursor(bool lock) const
{
    if(lock)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}
