#pragma once
#ifndef __SOLUTION__
#define __SOLUTION__

#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class Solution1
{
public:
	static string solution(string input_string);
};

class Solution2
{
public:
	static int solution(vector<vector<int>> ability);
private:
	struct Node
	{
		int profit = 0;
		int bound = 0;
		int event_index = 0;
		vector<int> selected_student;
	};
	static deque<Node> enqueue(deque<Node> pqueue, Node item);
	static int calc_bound(vector<vector<int>> ability, int event_length, int student_length, int event_index);
};

class Solution3
{
public:
	static vector<string> solution(vector<vector<int>> queries);
};

class Solution4
{
public:
	static vector<long long> solution(vector<vector<int>> program);
private:
	struct Program {
		long long priority;
		long long call_time;
		long long execute_time;
	};
	static void merge(deque<Program>& arr, int left, int mid, int right);
	static void merge_sort_call_time(deque<Program>& arr, int left, int right);
	static void enqueue(deque<Program>& pqueue, int queue_size, Program program);
};

#endif // !__SOLUTION__