// TextBanner.cpp
#include "TextBanner.h"
#include "../Battlescape/Camera.h"
#include "../Battlescape/BattlescapeState.h"
#include "../Engine/Surface.h"
#include "../Mod/Mod.h"
#include "../Engine/Game.h"
#include "../Engine/Palette.h"

namespace OpenXcom
{

TextBanner::TextBanner(const std::string& text, BattleUnit* unit, bool fade) :
    _text(text),
    _sprite(nullptr),
    _ttl(30000), // 30 секунд
    _age(0),
    _unit(unit),
    _fade(fade)
{
    _sprite = new Text(180, 16);
    // Шрифт и язык будут инициализированы позже — в draw()
    _sprite->setBig();
    _sprite->setColor(Palette::blockOffset(8));
    _sprite->setHighContrast(true);
    _sprite->setText(_text);
    _sprite->setAlign(ALIGN_CENTER);
}

TextBanner::~TextBanner()
{
    delete _sprite;
}

void TextBanner::think()
{
    if (!_unit || isExpired()) return;
    _age += 16; // ~60 FPS

    if (_fade && _age >= _ttl - 500)
    {
        int fadeAge = _age - (_ttl - 500);
        int alpha = 255 - (fadeAge * 255 / 500);
        alpha = std::max(0, std::min(255, alpha));
        //_sprite->setAlpha(alpha);
    }
}

void TextBanner::draw(Surface* surface, Camera* camera, Game* game, int offset_x, int offset_y)
{
    if (!_unit || isExpired()) return;

    // Инициализируем шрифт и язык, если ещё не инициализировано
    if (!_sprite->getFont())
    {
        _sprite->initText(
            game->getMod()->getFont("FONT_BIG"),
            game->getMod()->getFont("FONT_SMALL"),
            game->getLanguage()
        );
    }

    Position pos = _unit->getPosition();
    int x, y;
	Position screenPos;
    camera->convertMapToScreen(pos, &screenPos);
	screenPos.x += camera->getMapOffset().x + offset_x;
	screenPos.y += camera->getMapOffset().y + offset_y;

    // Смещение по вертикали (анимация ходьбы)
    //auto offset = camera->getMap()->calculateWalkingOffset(_unit);
    //y += offset.ScreenOffset.y;
    //y -= 20; // Над головой

    // Центрируем по ширине текста
    int textWidth = _sprite->getTextWidth();
    screenPos.x -= textWidth / 2;

    _sprite->setX(screenPos.x);
    _sprite->setY(screenPos.y);

    _sprite->draw(); // draw() без аргументов — Text сам рисуется на surface
}

}
