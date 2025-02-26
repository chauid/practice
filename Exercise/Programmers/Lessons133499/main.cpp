#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<string> babbling) {
	int answer = 0;
	for (int i = 0; i < babbling.size(); i++)
	{
		if (babbling[i].size() < 2) continue;
		bool is_spell = true;
		bool aya_spelled = false;
		bool ye_spelled = false;
		bool ma_spelled = false;
		bool woo_spelled = false;
		int word_index = 0;
		while (word_index < babbling[i].size())
		{
			string word = babbling[i].substr(word_index, 2);
			if (word == "ye")
			{
				if (ye_spelled) { is_spell = false; break; }
				word_index += 2;
				aya_spelled = false;
				ye_spelled = true;
				ma_spelled = false;
				woo_spelled = false;
				continue;
			}
			if (word == "ma")
			{
				if (ma_spelled) { is_spell = false; break; }
				word_index += 2;
				aya_spelled = false;
				ye_spelled = false;
				ma_spelled = true;
				woo_spelled = false;
				continue;
			}
			if (word != "ay" && word != "wo") { is_spell = false; break; }
			word = babbling[i].substr(word_index, 3);
			if (word == "aya")
			{
				if (aya_spelled) { is_spell = false; break; }
				word_index += 3;
				aya_spelled = true;
				ye_spelled = false;
				ma_spelled = false;
				woo_spelled = false;
				continue;
			}
			if (word == "woo")
			{
				if (woo_spelled) { is_spell = false; break; }
				word_index += 3;
				aya_spelled = false;
				ye_spelled = false;
				ma_spelled = false;
				woo_spelled = true;
				continue;
			}
			is_spell = false;
			break;
		}
		if (is_spell) answer++;
	}
	return answer;
}

int main()
{
	vector<string> input = { "ayaye", "uuu", "yeye", "yemawoo", "ayaayaa" };
	cout << solution(input);
	return 0;
}
