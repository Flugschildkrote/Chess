#include "GUI_Manager.h"

GUI_Manager::GUI_Manager() : mShader("Shaders/texture.vert","Shaders/texture.frag"), mFontTexture("Font.png"), mNbTexts(0)
{
    mShader.charger();
    mFontTexture.load();
    mProjection = glm::ortho(-1.0,1.0,-1.0,1.0,1.0,100.0);
}

/*GUI_Manager::GUI_Manager(const GUI_Manager &old_GUI) : mFontTexture(old_GUI.mFontTexture), mProjection(old_GUI.mProjection), mShader(old_GUI.mShader)
{
    mShader.charger();
    mFontTexture.load();
}*/

GUI_Manager::~GUI_Manager()
{
}

void GUI_Manager::setFontTexture(const std::string fontTexture)
{
    //mFontTexture = Texture(fontTexture);
    //mFontTexture.load();
}

void GUI_Manager::addText(const std::string texte, const glm::vec3 pointHautGauche, const glm::vec3 pointBasDroit)
{
    int index = mNbTexts;
    mTexts[index] = GUI_Text(texte,pointHautGauche,pointBasDroit);
    mTexts[index].charger();
    mNbTexts ++;
}

void GUI_Manager::hideText(const std::string text,const bool hide)
{
    for(int i(0); i < mNbTexts; i++)
    {
        if(mTexts[i].getText() == text)
        {
            mTexts[i].show(!hide);
        }
    }
}

void GUI_Manager::afficher()
{
    for(int i(0); i < mNbTexts; i++)
    {
        mTexts[i].afficher(mFontTexture,mProjection,mShader);
    }
}
