#include "solution.h"

int main()
{
	vector<vector<int>> points;
	vector<vector<int>> routes;

	// test case 1
	points = { {3, 2}, {6, 4}, {4, 7}, {1, 4} };
	routes = { {4, 2}, {1, 3}, {2, 4} };
	cout << Solution::solution(points, routes) << '\n';
	cout << "----------------------------\n\n";

	// test case 2
	points = { {3, 2}, {6, 4}, {4, 7}, {1, 4} };
	routes = { {4, 2}, {1, 3}, {4, 2}, {4, 3} };
	cout << Solution::solution(points, routes) << '\n';
	cout << "----------------------------\n\n";

	// test case 3
	points = { {2, 2}, {2, 3}, {2, 7}, {6, 6}, {5, 2} };
	routes = { {2, 3, 4, 5}, {1, 3, 4, 5} };
	cout << Solution::solution(points, routes) << '\n';
	cout << "----------------------------\n\n";

	return 0;
}
