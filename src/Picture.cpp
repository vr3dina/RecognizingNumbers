#include "Picture.h"

using namespace std;

Picture::Picture(const Matrix<int>& p) : pixels(p), width(p[0].size()), height(p.size())
{
	visited.resize(height, vector<bool>(width));
}

Picture::Picture(size_t h, size_t w) : height(h), width(w)
{
	pixels.resize(height, vector<int>(width));
	visited.resize(height, vector<bool>(width));
}

void Picture::InvertPixel(int i, int j)
{
	if (isCorrectCoord({ i, j }))
		pixels[i][j] = pixels[i][j] == 1 ? 0 : 1;
}

bool Picture::isVisited(Point p) const
{
	return isCorrectCoord(p) && visited[p.x][p.y];
}

bool Picture::isBlack(Point p) const
{
	return isCorrectCoord(p) && pixels[p.x][p.y] == 1;
}

std::vector<DIR> Picture::dfs_clockwise(Point p)
{
	dirs.clear();
	dfs_impl(p);
	return dirs;
}

void Picture::dfs_impl(Point p)
{
	visited[p.x][p.y] = true;

	bool f = false;

	pair<DIR, Point> dirs_to_check[4] = {
										{ DIR::UP, {p.x - 1, p.y }},
										{ DIR::RIGHT, {p.x, p.y + 1}},
										{ DIR::DOWN, {p.x + 1, p.y }},
										{ DIR::LEFT, {p.x, p.y - 1 }}
	};

	for (const auto& d : dirs_to_check)
	{
		if (isBlack(d.second) && !isVisited(d.second))
		{
			if (f || (dirs.empty() || dirs.back() != d.first))
				dirs.push_back(d.first);
			f = true;
			dfs_impl({ d.second });
		}
	}
}

size_t Picture::Width() const
{
	return width;
}

size_t Picture::Height() const
{
	return height;
}

void Picture::ClearVisited()
{
	for (size_t i = 0; i < visited.size(); i++)
		for (size_t j = 0; j < visited[i].size(); j++)
			visited[i][j] = false;
}

void Picture::Clear()
{
	for (auto& row : pixels)
		for (auto& el : row)
			el = 0;
}

bool Picture::isCorrectCoord(Point p) const
{
	return p.x >= 0 && p.x < height && p.y >= 0 && p.y < width;
}
