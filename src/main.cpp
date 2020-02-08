#include <iostream>
#include <fstream>
#include "recognizing_numbers.h"
#include "PictureRenderer.h"


using namespace std;

vector<vector<int>> read_file(const string file_name)
{
	fstream fin("res\\" + file_name);
	int n, m;
	fin >> n >> m;
	vector<vector<int>> pic(n, vector<int>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fin >> pic[i][j];
		}
	}
	return pic;
}

void any_digits()
{
	Picture p(read_file("n.txt"));
	vector<int> expected = { 8, 1, 5 };
	auto n = recognize_numbers(p);
	if (n == expected)
		cout << "error in n.txt" << std::endl;
}

void simple_test()
{
	for (int i = 0; i <= 9; i++)
	{
		Picture p(read_file(to_string(i) + ".txt"));
		auto n = recognize_numbers(p);
		if (n[0] != i)
			cout << i << "!=" << n[0] << std::endl;
	}
	any_digits();
}


int main(int argc, char* argv[])
{
	PictureRenderer pr(7, 10);
	pr.Loop();
	
	return 0;
}