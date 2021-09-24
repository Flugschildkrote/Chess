#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED

#include "GUI_Text.h"

class GUI_Manager
{
public:
    GUI_Manager();
    GUI_Manager(const GUI_Manager &old_GUI) = delete;
    ~GUI_Manager();
    void setFontTexture(const std::string fontTexture);
    void addText(const std::string texte, const glm::vec3 pointHautGauche, const glm::vec3 pointBasDroit);
    void hideText(const std::string text, const bool hide);
    void afficher();
protected:
    int mNbTexts;
    Texture mFontTexture;
    glm::mat4 mProjection;
    glm::mat4 mProjectionBis;
    GUI_Text mTexts[10];
    Shader mShader;
};


#endif // GUI_MANAGER_H_INCLUDED
