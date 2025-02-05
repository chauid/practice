#include "solution.h"

string Solution1::solution(string input_string)
{
	string answer = "";
	vector<int> check_alone(26);

	int before_alphabet_code = 0;
	int current_alphabet_code = 0;
	for (int i = 0; i < input_string.length(); i++)
	{
		current_alphabet_code = (int)input_string[i];
		if (current_alphabet_code != before_alphabet_code)
		{
			check_alone[current_alphabet_code - 97]++;
		}
		before_alphabet_code = current_alphabet_code;
	}

	for (int i = 0; i < 26; i++)
	{
		if (check_alone[i] > 1) answer.push_back((char)i + 97);
	}
	if (answer == "") answer = "N";

	return answer;
}

int Solution2::solution(vector<vector<int>> ability)
{
	int student_length = ability.size();
	int event_length = ability[0].size();
	int prev = student_length;
	deque<Node> PQ(1); // init 0, 0, 0, vector()
	int max_profit = 0;

	Node cur_node;
	while (!PQ.empty())
	{
		Node tmp_node;
		cur_node.profit = PQ.front().profit;
		cur_node.event_index = PQ.front().event_index;
		cur_node.selected_student = PQ.front().selected_student;
		PQ.pop_front();
		if (cur_node.event_index == event_length) break;

		vector<vector<int>> ability_copy = ability;
		for (int i = 0; i < cur_node.selected_student.size(); i++)
		{
			ability_copy.erase(ability_copy.begin() + cur_node.selected_student[i]);
			tmp_node.selected_student.push_back(cur_node.selected_student[i]);
		}
		for (int i = 0; i < ability_copy.size(); i++)
		{
			int next_event_index = cur_node.event_index + 1;
			tmp_node.profit = cur_node.profit + ability_copy[i][cur_node.event_index];
			tmp_node.bound = tmp_node.profit + calc_bound(ability_copy, ability_copy[0].size(), ability_copy.size(), next_event_index);
			if (tmp_node.profit == tmp_node.bound && tmp_node.bound > max_profit) max_profit = tmp_node.bound;

			tmp_node.event_index = next_event_index;

			vector<int> temp_selected = tmp_node.selected_student;
			tmp_node.selected_student.push_back(i);
			PQ = enqueue(PQ, tmp_node);
			tmp_node.selected_student = temp_selected;
		}
		//cout << "-----------------------------------------------------\n";
		//cout << "max profit: " << max_profit << '\n';
		//for (int i = 0; i < PQ.size(); i++)
		//{
		//	cout << "{ " << PQ[i].profit << ", " << PQ[i].bound << ", " << PQ[i].event_index << ", [";
		//	for (int j = 0; j < PQ[i].selected_student.size(); j++)
		//	{
		//		cout << PQ[i].selected_student[j] << ", ";
		//	}
		//	cout << "] }\n";
		//}
	}
	return max_profit;
}

deque<Solution2::Node> Solution2::enqueue(deque<Node> pqueue, Node item)
{
	if (pqueue.empty()) { pqueue.push_front(item); return pqueue; }
	bool is_insert = false;
	for (int i = 0; i < pqueue.size(); i++)
	{
		if (item.bound > pqueue[i].bound)
		{
			pqueue.insert(pqueue.begin() + i, item);
			is_insert = true;
			break;
		}
	}
	if (!is_insert) pqueue.push_back(item);
	return pqueue;
}

int Solution2::calc_bound(vector<vector<int>> ability, int event_length, int student_length, int event_index)
{
	int sum_of_max = 0;
	for (int i = event_index; i < event_length; i++)
	{
		int max = 0;
		for (int j = 0; j < student_length; j++)
		{
			if (ability[j][i] > max) max = ability[j][i];
		}
		sum_of_max += max;
	}
	return sum_of_max;
}

vector<string> Solution3::solution(vector<vector<int>> queries)
{
	vector<string> answer;
	string assume; // RR, Rr, rr
	for (int i = 0; i < queries.size(); i++)
	{
		//cout << "----------------------\n";
		if (queries[i][0] == 1) { answer.push_back("Rr"); continue; }
		if (queries[i][0] == 2)
		{
			switch (queries[i][1])
			{
			case 1:
				answer.push_back("RR");
				break;
			case 2:
			case 3:
				answer.push_back("Rr");
				break;
			case 4:
				answer.push_back("rr");
				break;
			default:
				break;
			}
			continue;
		}
		int parent_index = queries[i][1];
		int selected_index; // 0: RR, 1: Rr, 2: Rr, 3: rr
		bool containedRRrr = false;
		int candidate = 0;
		for (int j = queries[i][0]; j >= 2; j--)
		{
			selected_index = (int)parent_index % 4;
			parent_index = (int)ceil(parent_index / 4.0);
			if (selected_index == 0)
			{
				//cout << "4 선택\n";
				containedRRrr = true;
				candidate = 0;
			}
			if (selected_index == 1)
			{
				//cout << "1 선택\n";
				candidate = 1;
				containedRRrr = true;
			}
			//else
			//{
			//	cout << "2, 3 선택\n";
			//}
			if (j == 2)
			{
				if (!containedRRrr) assume = "Rr";
				else
				{
					if (candidate == 0) assume = "rr";
					if (candidate == 1) assume = "RR";
				}
			}
		}
		answer.push_back(assume);
	}
	return answer;
}

vector<long long> Solution4::solution(vector<vector<int>> program)
{
	vector<long long> answer(11, 0);
	int program_size = program.size();
	deque<Program> program_list(program_size);
	for (int i = 0; i < program_size; i++)
	{
		program_list[i] = { program[i][0], program[i][1], program[i][2] };
	}
	merge_sort_call_time(program_list, 0, program_size - 1);

	deque<Program> program_queue;
	int queue_size = 0;
	while (true)
	{
		while (true) // enqueue
		{
			if (program_list.empty()) break;
			if (program_list[0].call_time == answer[0])
			{
				enqueue(program_queue, queue_size, program_list[0]);
				program_list.pop_front();
				queue_size++;
			}
			else if (program_list[0].call_time < answer[0])
			{
				Program insert = program_list[0];
				enqueue(program_queue, queue_size, insert);
				program_list.pop_front();
				queue_size++;
			}
			else if (queue_size == 0) // 모든 큐가 비어있고 대기하고 있는 프로그램 없을 때
			{
				answer[0] = program_list[0].call_time;
				enqueue(program_queue, queue_size, program_list[0]);
				program_list.pop_front();
				queue_size++;
			}
			else break;
		}

		//cout << "-------------------------------\n" << "os time: " << answer[0] << "\nprogram list: ";
		//for (const Program& i : program_list)
		//{
		//	cout << "{" << i.priority << ", " << i.call_time << ", " << i.execute_time << "} ";
		//}
		//cout << "\nprogram queue: ";
		//for (const Program& i : program_queue)
		//{
		//	cout << "{" << i.priority << ", " << i.call_time << ", " << i.execute_time << "} ";
		//}
		//cout << "\n";

		if (program_queue.empty()) break;
		else // execute program at queue front
		{
			answer[program_queue[0].priority] += answer[0] - program_queue[0].call_time;
			answer[0] += program_queue[0].execute_time;
			program_queue.pop_front();
			queue_size--;
		}
	}
	return answer;
}

void Solution4::merge(deque<Program>& arr, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<Program> left_arr(n1), right_arr(n2);
	for (int i = 0; i < n1; i++) left_arr[i] = arr[left + i];
	for (int j = 0; j < n2; j++) right_arr[j] = arr[mid + 1 + j];

	int left_index = 0, right_index = 0;
	int arr_index = left;
	while (left_index < n1 && right_index < n2)
	{
		if (left_arr[left_index].call_time <= right_arr[right_index].call_time) { arr[arr_index] = left_arr[left_index]; left_index++; }
		else { arr[arr_index] = right_arr[right_index];right_index++; }
		arr_index++;
	}
	while (left_index < n1)
	{
		arr[arr_index] = left_arr[left_index];
		left_index++;
		arr_index++;
	}
	while (right_index < n2) {
		arr[arr_index] = right_arr[right_index];
		right_index++;
		arr_index++;
	}
}

void Solution4::merge_sort_call_time(deque<Program>& arr, int left, int right)
{
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	merge_sort_call_time(arr, left, mid);
	merge_sort_call_time(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

void Solution4::enqueue(deque<Program>& pqueue, int queue_size, Program program)
{
	if (pqueue.empty()) { pqueue.push_front(program); return; }
	bool is_insert = false;
	for (int i = 0; i < queue_size; i++)
	{
		if (program.priority < pqueue[i].priority)
		{
			pqueue.insert(pqueue.begin() + i, program);
			is_insert = true;
			break;
		}
	}
	if (!is_insert) pqueue.push_back(program);
}
