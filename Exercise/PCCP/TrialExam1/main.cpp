#include "solution.h"

int main()
{
	string input1 = "edeaaabbccd";
	cout << "solution 1\n------------------------------\n";
	cout << Solution1::solution(input1) << "\n------------------------------\n\n";

	vector<vector<int>> input2 = { {40,10,10},{20,5,0},{30,30,30},{70,0,70},{100,100,100} };
	cout << "solution 2\n------------------------------\n";
	cout << Solution2::solution(input2) << "\n------------------------------\n\n";

	vector<vector<int>> input3 = { {3,8}, {2,2}, {3, 5}, {5, 6}, {5, 200}, {4, 26} };
	vector<string> output3 = Solution3::solution(input3);
	cout << "solution 3\n------------------------------\n";
	for (string out : output3) cout << out << '\n';
	cout << "------------------------------\n\n";

	vector<vector<int>> input4 = { {3, 6, 4} ,{4, 2, 5},{1, 0, 50}, {5, 0, 5}, {1, 20, 13}, {8, 99, 5}, {1, 1, 7}, {1, 2, 5}, {1, 3, 6} };
	cout << "solution 4\n------------------------------\n";
	vector<long long> output4 = Solution4::solution(input4);
	for (long long out : output4) cout << out << ' ';
	cout << "\n------------------------------\n";
	return 0;
}