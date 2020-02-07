#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Label
{
public:
	std::string text;
protected:
	double x;
	double y;

	sf::Font font;
	unsigned int font_size = 20;
	sf::Text display_text;

	std::string font_path = "res\\font\\Raleway-Regular.ttf";
public:
	Label(double x, double y, const std::string& text);
	sf::Text displayText();
};


class Button : public Label 
{
protected:
	double width;
	double height;
	sf::RectangleShape button;
public:
	Button(double x, double y, double w, double h, const std::string& text);
	bool select(sf::Vector2i _mouse);
	sf::Text displayText();
	sf::RectangleShape displayButton();
};

