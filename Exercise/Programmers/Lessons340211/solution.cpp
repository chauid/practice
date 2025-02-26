#include "solution.h"

int Solution::solution(vector<vector<int>> points, vector<vector<int>> routes)
{
	int robot_size = routes.size();
	vector<robot> robots(robot_size);

	for (int i = 0; i < robot_size; i++)
	{
		robots[i].x = points[routes[i][0] - 1][0]; // x
		robots[i].y = points[routes[i][0] - 1][1]; // y
		robots[i].routes = deque<int>();
		for (int j = 0; j < routes[i].size(); j++)
		{
			robots[i].routes.push_back(routes[i][j]);
		}
	}

	int exit_robot_count = 0;
	int count = 0;
	int sec = 1;

	//cout <<"0초\n";
	//for (int i = 0; i < robot_size; i++)
	//{
	//	cout << "[" << i << "] 로봇: " << "{" << robots[i].x << ", " << robots[i].y << "}\n";
	//}
	count += check_collision_count(robots);
	while (exit_robot_count < robot_size)
	{
		//cout << sec++ << "초\n";
		move(robots, points, exit_robot_count);
		count += check_collision_count(robots);
	}
	return count;
}

void Solution::move(vector<robot>& robots, vector<vector<int>>& points, int& exit_count)
{
	for (int i = 0; i < robots.size(); i++)
	{
		if (robots[i].is_exit) continue;
		vector<int> cur_target = points[robots[i].routes.front() - 1]; // [0]: x, [1]: y
		if (robots[i].x < cur_target[0]) robots[i].x++;
		else if (robots[i].x > cur_target[0]) robots[i].x--;
		else if (robots[i].y < cur_target[1]) robots[i].y++;
		else if (robots[i].y > cur_target[1]) robots[i].y--;
		else
		{
			robots[i].routes.pop_front();
			if (robots[i].routes.empty())
			{
				robots[i].is_exit = true;
				exit_count++;
				continue;
			}
			cur_target = points[robots[i].routes.front() - 1]; // [0]: x, [1]: y
			if (robots[i].x < cur_target[0]) robots[i].x++;
			else if (robots[i].x > cur_target[0]) robots[i].x--;
			else if (robots[i].y < cur_target[1]) robots[i].y++;
			else if (robots[i].y > cur_target[1]) robots[i].y--;
		}
		//cout << "[" << i << "] 로봇: " << "{" << robots[i].x << ", " << robots[i].y << "}\n";
	}
	//cout << "\n";
}

int Solution::check_collision_count(vector<robot> robots)
{
	vector<vector<int>> collision_coord;
	int length = robots.size();
	for (int i = 0; i < length - 1; i++)
	{
		if (robots[i].is_exit) continue;
		for (int j = i + 1; j < length; j++)
		{
			if (robots[j].is_exit) continue;
			if ((robots[i].x == robots[j].x) && (robots[i].y == robots[j].y))
			{
				//cout << "충돌: " << i << "<->" << j << "{" << robots[i].x << ", " << robots[i].y << "}\n";
				if (collision_coord.empty()) collision_coord.push_back({ robots[i].x, robots[i].y }); // = robot[j].x, robots[j].y
				else
				{
					bool is_duplicate = false;
					for (int k = 0; k < collision_coord.size(); k++) // 충돌 벡터 순회하고 중복된 좌표는 추가하지 않음
					{
						if (collision_coord[k][0] == robots[i].x && collision_coord[k][1] == robots[i].y)
						{
							is_duplicate = true;
							break;
						}
					}
					if (!is_duplicate) collision_coord.push_back({ robots[i].x, robots[i].y });
				}
			}
		}
	}
	//cout << "충돌횟수: " << collision_coord.size() << "\n\n";
	return collision_coord.size();
}
