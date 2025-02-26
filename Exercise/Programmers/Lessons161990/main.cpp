#include <iostream>

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> wallpaper) {
	int min_x = 50;
	int max_x = 0;
	int min_y = 50;
	int max_y = 0;
	for (int y = 0; y < wallpaper.size(); y++)
	{
		for (int x = 0; x < wallpaper[y].size(); x++)
		{
			if (wallpaper[y][x] == '.') continue;
			if (x < min_x) min_x = x;
			if (x > max_x) max_x = x;
			if (y < min_y) min_y = y;
			if (y > max_y) max_y = y;
		}
	}

	return { min_y, min_x, max_y + 1, max_x + 1 };
}

int main()
{
	vector<string> wallpaper = { ".##...##.", "#..#.#..#", "#...#...#", ".#.....#.", "..#...#..", "...#.#...", "....#...." };
	vector<int> result = solution(wallpaper);

	for (int i : result)
	{
		cout << i << ' ';
	}

	return 0;
}
