#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<int> merge_sort(vector<int>& v)
{
	if (v.size() <= 1) return v;
	int mid = v.size() / 2;
	vector<int> left(v.begin(), v.begin() + mid);
	vector<int> right(v.begin() + mid, v.end());
	left = merge_sort(left);
	right = merge_sort(right);
	int left_size = left.size();
	int right_size = right.size();
	vector<int> merged(left_size + right_size);
	int left_index = 0, right_index = 0, merged_index = 0;
	for (int i = 0; i < left_size + right_size; i++)
	{
		if (left_index == left_size) { merged[merged_index++] = right[right_index++]; continue; }
		if (right_index == right_size) { merged[merged_index++] = left[left_index++]; continue; }
		if (left[left_index] < right[right_index]) merged[merged_index++] = left[left_index++];
		else merged[merged_index++] = right[right_index++];
	}
	return merged;
}

int solution(string str1, string str2) {
	float answer = 0.0;
	vector<int> set1;
	vector<int> set2;
	int inter_count = 0;
	int union_count = 0;

	for (int i = 0; i < str1.size() - 1; i++)
	{
		if ((str1[i] >= 'a' && str1[i] <= 'z') && (str1[i + 1] >= 'a' && str1[i + 1] <= 'z')) { set1.push_back(((int)str1[i] - 97) * 26 + (int)str1[i + 1] - 97); }
		if ((str1[i] >= 'a' && str1[i] <= 'z') && (str1[i + 1] >= 'A' && str1[i + 1] <= 'Z')) { set1.push_back(((int)str1[i] - 97) * 26 + (int)str1[i + 1] - 65); }
		if ((str1[i] >= 'A' && str1[i] <= 'Z') && (str1[i + 1] >= 'a' && str1[i + 1] <= 'z')) { set1.push_back(((int)str1[i] - 65) * 26 + (int)str1[i + 1] - 97); }
		if ((str1[i] >= 'A' && str1[i] <= 'Z') && (str1[i + 1] >= 'A' && str1[i + 1] <= 'Z')) { set1.push_back(((int)str1[i] - 65) * 26 + (int)str1[i + 1] - 65); }
	}
	for (int i = 0; i < str2.size() - 1; i++)
	{
		if ((str2[i] >= 'a' && str2[i] <= 'z') && (str2[i + 1] >= 'a' && str2[i + 1] <= 'z')) { set2.push_back(((int)str2[i] - 97) * 26 + (int)str2[i + 1] - 97); }
		if ((str2[i] >= 'a' && str2[i] <= 'z') && (str2[i + 1] >= 'A' && str2[i + 1] <= 'Z')) { set2.push_back(((int)str2[i] - 97) * 26 + (int)str2[i + 1] - 65); }
		if ((str2[i] >= 'A' && str2[i] <= 'Z') && (str2[i + 1] >= 'a' && str2[i + 1] <= 'z')) { set2.push_back(((int)str2[i] - 65) * 26 + (int)str2[i + 1] - 97); }
		if ((str2[i] >= 'A' && str2[i] <= 'Z') && (str2[i + 1] >= 'A' && str2[i + 1] <= 'Z')) { set2.push_back(((int)str2[i] - 65) * 26 + (int)str2[i + 1] - 65); }
	}
	if (set1.size() == 0 && set2.size() == 0) return 65536;

	set1 = merge_sort(set1);
	set2 = merge_sort(set2);

	int set1_index = 0, set2_index = 0;
	while (set1_index < set1.size() && set2_index < set2.size())
	{
		if (set1[set1_index] < set2[set2_index]) { union_count++; set1_index++; }
		else if (set1[set1_index] > set2[set2_index]) { union_count++; set2_index++; }
		else { inter_count++; union_count++; set1_index++; set2_index++; }
	}
	if (set1_index < set1.size() || set2_index < set2.size())
	{
		if (set1_index == set1.size()) union_count += set2.size() - set2_index;
		if (set2_index == set2.size()) union_count += set1.size() - set1_index;
	}
	answer = (float)inter_count / union_count;
	return (int)(answer * 65536);
}

int main()
{
	string input1 = "FRANCE";
	string input2 = "french";
	cout << solution(input1, input2) << '\n';
	return 0;
}
