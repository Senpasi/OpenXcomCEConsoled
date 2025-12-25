#pragma once

#include "../Engine/Surface.h"
#include "../Engine/Timer.h"
#include "../Interface/Text.h"

namespace OpenXcom
{

class NotificationMessage : public Surface
{
private:
	Text *_text;
	Timer *_timer;
	bool _visible;
	std::string _currentMessage;

	void update();

public:
	/// Creates a new notification message display.
	NotificationMessage(int width, int height, int x, int y);
	/// Cleans up the notification message.
	~NotificationMessage();
	/// Sets the palette for the surface.
	void setPalette(const SDL_Color *colors, int firstcolor = 0, int ncolors = 256) override;
	/// Sets the font and language for text rendering.
	void initText(Font *big, Font *small, Language *lang);
	/// Sets the color of the text.
	void setColor(Uint8 color);
	/// Shows a message for 5 seconds.
	void showMessage(const std::string &msg);
	/// Hides the message immediately.
	void hide();
	/// Handles per-frame logic.
	void think() override;
	/// Draws the message.
	void draw() override;
};
}
