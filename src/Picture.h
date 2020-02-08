#pragma once
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

enum DIR
{
	RIGHT = 0,
	UP = 1,
	LEFT = 2,
	DOWN = 3
};

struct Point
{
	int x, y;
};

class Picture
{
public:
	Picture(const Matrix<int>&);
	Picture(size_t w, size_t h);

	void InvertPixel(int x, int y);
	bool isVisited(Point) const;
	bool isBlack(Point) const;
	std::vector<DIR> dfs_clockwise(Point);
	size_t Width() const;
	size_t Height() const;
	void ClearVisited();
	void Clear();

private:
	Matrix<int> pixels;
	Matrix<bool> visited;
	std::vector<DIR> dirs;
	size_t height;
	size_t width;

	void dfs_impl(Point);
	bool isCorrectCoord(Point) const;
};


