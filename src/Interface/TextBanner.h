// TextBanner.h
#ifndef OPENXCOM_TEXTBANNER_H
#define OPENXCOM_TEXTBANNER_H

#include <string>
#include "Text.h"
#include "../SaveGame/BattleUnit.h"
#include "../Mod/Mod.h"

namespace OpenXcom
{

class Game;
class Camera;
class Surface;

class TextBanner
{
private:
    std::string _text;
    Text* _sprite;
    int _ttl;
    int _age;
    BattleUnit* _unit;
    bool _fade;

public:
    TextBanner(const std::string& text, BattleUnit* unit, bool fade = true);
    ~TextBanner();

    void think();
    void draw(Surface* surface, Camera* camera, Game* game, int offset_x, int offset_y);
    bool isExpired() const { return _age >= _ttl; }
    BattleUnit* getUnit() const { return _unit; }
	Text* getSprite() const { return _sprite;  }
};

}

#endif
