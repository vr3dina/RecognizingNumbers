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
	Button button;
	Label label_numbers;
	bool isMousePressed;


	void Draw();
	void HandleInput();
};
