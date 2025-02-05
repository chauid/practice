#pragma once
#ifndef __SOLUTION__
#define __SOLUTION__

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution
{
public:
	static int solution(vector<vector<int>> points, vector<vector<int>> routes);
private:
	struct robot
	{
		int x;
		int y;
		deque<int> routes;
		bool is_exit = false; // 벡터 재할당 오버헤드 방지
	};
	static void move(vector<robot>& robots, vector<vector<int>>& points, int& exit_count);
	static int check_collision_count(vector<robot> robots);
};

#endif // !__SOLUTION__