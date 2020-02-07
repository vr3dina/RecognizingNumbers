#include "Label.h"
#include <iostream>

Label::Label(double x, double y, const std::string& text) :
	x(x),
	y(y),
	text(text)
{
	if (!font.loadFromFile(font_path))
		std::cout << "error\t" << font_path << std::endl;


	display_text.setFont(font);
	display_text.setCharacterSize(font_size);
	display_text.setFillColor(sf::Color::Black);
	display_text.setPosition(x, y);
}

sf::Text Label::displayText()
{
	display_text.setString(text);
	return display_text;
}

Button::Button(double x, double y, double w, double h, const std::string& text) :
	Label(x, y, text),
	width(w),
	height(h)

{
	display_text.setString(text);
	sf::FloatRect textRect = display_text.getLocalBounds();
	display_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	display_text.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));


	button.setSize(sf::Vector2f(width, height));
	button.setPosition(x, y);
	button.setFillColor(sf::Color(0, 0, 0, 50));
	button.setOutlineThickness(2);
	button.setOutlineColor(sf::Color::Black);
}

bool Button::select(sf::Vector2i mouse_pos)
{
	return (mouse_pos.x > x && mouse_pos.x < x + width) && (mouse_pos.y > y && mouse_pos.y < y + height);
}

sf::Text Button::displayText()
{
	return display_text;
}

sf::RectangleShape Button::displayButton()
{
	return button;
}
