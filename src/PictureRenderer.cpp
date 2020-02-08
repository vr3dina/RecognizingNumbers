#include "PictureRenderer.h"
#include "recognizing_numbers.h"
#include <iostream>
#include <sstream>

PictureRenderer::PictureRenderer(int rows, int cols, unsigned int cell_size) :
	cell_size(cell_size),
	row_cnt(rows), col_cnt(cols),
	width(cols* cell_size), height(rows* cell_size),
	pic(rows, cols),
	is_mouse_pressed(false),
	last_mouse_pos(0, 0),
	button(width + 20, height - 70, 150, 50, "Recognize"),
	label_numbers(width + 20, 20, "")
{
	window.create(sf::VideoMode(width + 200, height), "Recognizing numbers");
	window.setFramerateLimit(60);

	image.create(width, height, sf::Color::White);
}

void PictureRenderer::Loop()
{
	while (window.isOpen())
	{
		HandleInput();
		window.clear(sf::Color::White);
		Draw();
		window.display();
	}
}

bool PictureRenderer::isInTheSameCell(sf::Vector2i a, sf::Vector2i b) const
{
	return a.x / cell_size == b.x / cell_size && a.y / cell_size == b.y / cell_size;
}

void PictureRenderer::HandleInput()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			std::exit(0);
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				auto pos = sf::Vector2i(sf::Mouse::getPosition(window));
				if (pos.x < col_cnt * cell_size && pos.y < row_cnt * cell_size)
				{
					is_mouse_pressed = true;
					pic.InvertPixel(pos.y / cell_size, pos.x / cell_size);
				}

				if (button.select(pos))
				{
					auto nums = recognize_numbers(pic);
					std::stringstream result;
					std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(result, " "));

					label_numbers.text = "Recognized\nnumbers\n" + result.str();
				}
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
				is_mouse_pressed = false;
			break;

			case sf::Event::MouseMoved:
				auto pos = sf::Vector2i(sf::Mouse::getPosition(window));
				if (is_mouse_pressed && !isInTheSameCell(pos, last_mouse_pos))
				{
					pic.InvertPixel(pos.y / cell_size, pos.x / cell_size);
					last_mouse_pos = sf::Vector2i(sf::Mouse::getPosition(window));
				}
				break;
		}
	}

}


void PictureRenderer::Draw()
{
	window.draw(button.displayButton());
	window.draw(button.displayText());
	window.draw(label_numbers.displayText());

	sf::RectangleShape cell;
	cell.setFillColor(sf::Color::Black);
	cell.setSize(sf::Vector2f(cell_size * 1.0, cell_size * 1.0));

	sf::RectangleShape tile;
	tile.setSize(sf::Vector2f(cell_size * 1.0, cell_size * 1.0));

	for (int i = 0; i < row_cnt; i++)
	{
		for (int j = 0; j < col_cnt; j++)
		{
			tile.setFillColor((i + j) % 2 == 1 ? sf::Color(0, 0, 0, 30) : sf::Color::White);
			tile.setPosition(sf::Vector2f(j * cell_size * 1.0, i * cell_size * 1.0));
			window.draw(tile);

			if (pic.isBlack({ i, j }))
			{
				cell.setPosition(sf::Vector2f(j * cell_size, i * cell_size));
				window.draw(cell);
			}
		}
	}
}

