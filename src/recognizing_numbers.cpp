#include "recognizing_numbers.h"
using namespace std;

static vector<DIR> zero = { DIR::UP, DIR::RIGHT, DIR::DOWN, DIR::LEFT };
static vector<DIR> one = { DIR::UP };
static vector<DIR> two = { DIR::UP, DIR::RIGHT, DIR::UP, DIR::LEFT, DIR::RIGHT };
static vector<DIR> three = { DIR::RIGHT, DIR::UP, DIR::LEFT, DIR::LEFT };
static vector<DIR> four = { DIR::UP, DIR::LEFT, DIR::UP };
static vector<DIR> five = { DIR::RIGHT, DIR::UP, DIR::LEFT, DIR::UP, DIR::RIGHT };
static vector<DIR> six = { DIR::UP, DIR::RIGHT, DIR::RIGHT, DIR::DOWN, DIR::LEFT };
static vector<DIR> seven = { DIR::UP, DIR::LEFT };
static vector<DIR> eight = { DIR::UP, DIR::RIGHT, DIR::DOWN, DIR::LEFT, DIR::LEFT };
static vector<DIR> nine = { DIR::RIGHT, DIR::UP, DIR::LEFT, DIR::DOWN, DIR::RIGHT };

static vector<vector<DIR>> numbers = { zero, one, two, three, four, five, six, seven, eight, nine };


vector<int> recognize_numbers(Picture& pic)
{
	pic.ClearVisited();
	vector<int> recognized_numbers;
	vector<DIR> dirs;
	for (int i = pic.Height() - 1; i >= 0; i--)
	{
		for (int j = 0; j < pic.Width(); j++)
		{
			if (pic.isBlack({ i, j }) && !pic.isVisited({ i, j }))
			{
				dirs = pic.dfs_clockwise({ i, j });

				for (int i = 0; i <= 9; i++)
					if (dirs == numbers[i])
						recognized_numbers.push_back(i);
			}
		}
	}
	return recognized_numbers;
}
