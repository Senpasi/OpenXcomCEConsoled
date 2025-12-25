#include "NotificationMessage.h"
#include "../Engine/Font.h"
#include "../Engine/Options.h"

namespace OpenXcom
{

NotificationMessage::NotificationMessage(int width, int height, int x, int y)
	: Surface(width, height, x, y), _visible(false)
{
	_text = new Text(width, height, 0, 0);
	_text->setVerticalAlign(ALIGN_MIDDLE);
	_text->setAlign(ALIGN_LEFT);

	_timer = new Timer(5000); // 5 seconds
	_timer->onTimer((SurfaceHandler)&NotificationMessage::update);
}

NotificationMessage::~NotificationMessage()
{
	delete _text;
	delete _timer;
}

void NotificationMessage::setPalette(const SDL_Color *colors, int firstcolor, int ncolors)
{
	Surface::setPalette(colors, firstcolor, ncolors);
	_text->setPalette(colors, firstcolor, ncolors);
}

void NotificationMessage::initText(Font *big, Font *small, Language *lang)
{
	_text->initText(big, small, lang);
}

void NotificationMessage::setColor(Uint8 color)
{
	 _text->setColor(color);
	_text->setHighContrast(true);
	_text->setSecondaryColor(color);
}

void NotificationMessage::showMessage(const std::string &msg)
{
	_currentMessage = msg;
	_text->setText(msg);
	_visible = true;
	_timer->start();
	_redraw = true;
}

void NotificationMessage::hide()
{
	_visible = false;
	_timer->stop();
	_redraw = true;
}

void NotificationMessage::update()
{
	hide(); // auto-hide after timer
}

void NotificationMessage::think()
{
	_timer->think(0, this);
	Surface::think();
}

void NotificationMessage::draw()
{
	Surface::draw();
	if (_visible)
	{
		_text->blit(this->getSurface());
	}
}

} // namespace OpenXcom
