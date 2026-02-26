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
    int _delay;
    BattleUnit* _unit;
    bool _fade;

public:
    TextBanner(const std::string& text, BattleUnit* unit, bool fade = true, int delay = 0);
    ~TextBanner();

    void think();
    void draw(Surface* surface, Camera* camera, Game* game, int offset_x, int offset_y);
	void draw(Surface* surface, Game* game, int x, int y);
	bool isExpired() const { return _age >= _delay + _ttl; }
	bool isActive() const { return _unit && _age >= _delay && _age < _delay + _ttl; }
    BattleUnit* getUnit() const { return _unit; }
	Text* getSprite() const { return _sprite;  }
	int getTtl() const { return _ttl; }
    int getAge() const { return _age; }
	int getDelay() const { return _delay; }
};

}

#endif
