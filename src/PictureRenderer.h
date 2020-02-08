#pragma once
#include "Picture.h"
#include "Label.h"


class PictureRenderer
{
public:
	PictureRenderer(int rows, int cols, unsigned int cell_size = 50);
	void Loop();
private:
	Picture pic;

	unsigned int cell_size;
	unsigned int row_cnt, col_cnt;
	int width, height;

	sf::Event event;
	sf::RenderWindow window;
	sf::Image image;
	Button btn_recognize;
	Button btn_clear;
	Label label_numbers;
	bool is_mouse_pressed;
	sf::Vector2i last_mouse_pos;

	bool isInTheSameCell(sf::Vector2i a, sf::Vector2i b) const;

	void Draw();
	void HandleInput();
};
