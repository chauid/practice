#include "main.hpp"

/// <param name="maze">2차원 행렬 포인터</param>
/// <param name="width">미로 가로 길이(벽 포함)</param>
/// <param name="height">미로 세로 길이(벽 포함)</param>
void init_maze_with_wall(int** maze, int width, int height)
{
	// 벽 초기화: 못 뚫는 벽 = 4, 뚫을 수 있는 벽 = 3, 방문한 셀 = 2, 방문하지 않은 셀 = 1
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y % 2 == 0 || x % 2 == 0)
			{

				//if (y == 0 || y == height - 1 || x == 0 || x == width - 1) *(*(maze + y) + x) = 4;
				if ((y % 2 == 0 && x % 2 == 0) || y == 0 || y == height - 1 || x == 0 || x == width - 1) *(*(maze + y) + x) = 4;
				else *(*(maze + y) + x) = 3;
			}
			else *(*(maze + y) + x) = 1;
		}
	}
}

/// <param name="matrix">2차원 행렬 포인터</param>
/// <param name="width">미로 가로 길이(벽 포함)</param>
/// <param name="height">미로 세로 길이(벽 포함)</param>
/// /// <param name="is_step">단계별 출력 여부: 기본값 = false(3)</param>
void print_maze(int** maze, int width, int height, int is_step)
{
	// 미로 입구 생성: 단계별 출력이 아닐 경우
	if (is_step == 3)
	{
		*(*(maze + 0) + 1) = 2;
		*(*(maze + height - 1) + width - 2) = 2;
	}

	system("cls");
	if (is_step == 1) printf("Step\n---------------------------------\n");
	if (is_step == 2) printf("Procedure\n---------------------------------\n");
	if (is_step == 3) printf("Result\n---------------------------------\n");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (*(*(maze + y) + x))
			{
			case 1:
				printf("×"); // 방문하지 않은 셀
				break;
			case 2:
				printf("□"); // 방문한 셀
				break;
			case 3:
				printf("■"); // 벽
				break;
			case 4:
				printf("■"); // 벽
				break;
			case 5:
				printf("▣"); // 특수 블록
				break;
			default:
				printf("%2d", *(*(maze + y) + x));
				break;
				//printf("\ninvalid value.\n");
				//return;
			}
		}
		printf("\n");
	}
	printf("\n");
	system("pause");
}

/// <param name="maze">2차원 미로 행렬</param>
/// <param name="x">현재 x좌표</param>
/// <param name="y">현재 y좌표</param>
/// <param name="width">출력을 위한 값: 미로 가로 길이(벽 포함)</param>
/// <param name="height">출력을 위한 값: 미로 세로 길이(벽 포함)</param>
/// <param name="is_step">단계별 출력: 기본값 = false(3)</param>
void backtracking(int** maze, int x, int y, int width, int height, int is_step = 3)
{
	//printf("%d, %d 방문\n", x, y);
	*(*(maze + y) + x) = 5; // 현재 셀 방문(현재 위치 표시용)

	int available_count = 0; // 방문가능한 인접 셀 개수
	Direction direction[4]{};
	if (*(*(maze + y) + x + 1) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// x + 2 (벽을 고려한 좌표계산)
		if (*(*(maze + y) + x + 2) == 1) direction[available_count++] = Direction::E;
	}
	if (*(*(maze + y) + x - 1) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// x - 2
		if (*(*(maze + y) + x - 2) == 1) direction[available_count++] = Direction::W;
	}
	if (*(*(maze + y + 1) + x) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// y + 2
		if (*(*(maze + y + 2) + x) == 1) direction[available_count++] = Direction::S;
	}
	if (*(*(maze + y - 1) + x) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// y - 2
		if (*(*(maze + y - 2) + x) == 1) direction[available_count++] = Direction::N;
	}
	if (available_count == 0) // 막다른 길
	{
		if (is_step == 2) print_maze(maze, width, height, is_step);
		*(*(maze + y) + x) = 2; // 현재 셀 방문
		return;
	}

	// 방문 순서 섞기: 안 섞으면 동->서->남->북 순서대로 우선순위를 가짐
	for (int i = 0; i < available_count; i++)
	{
		int random = i + rand() % (available_count - i);
		Direction temp = direction[i];
		direction[i] = direction[random];
		direction[random] = temp;
	}

	for (int visit = 0; visit < available_count; visit++)
	{
		if (is_step == 1) print_maze(maze, width, height, is_step);
		*(*(maze + y) + x) = 2; // 현재 셀 방문
		switch (direction[visit])
		{
		case 0: // x + 1
			if (*(*(maze + y) + x + 2) == 1) // 방문하고자 한 셀이 아직 유효한가?
			{
				*(*(maze + y) + x + 1) = 2; // 벽 뚫기
				backtracking(maze, x + 2, y, width, height, is_step);
			}
			break;
		case 1: // x - 1
			if (*(*(maze + y) + x - 2) == 1)
			{
				*(*(maze + y) + x - 1) = 2; // 벽 뚫기
				backtracking(maze, x - 2, y, width, height, is_step);
			}
			break;
		case 2: // y + 1
			if (*(*(maze + y + 2) + x) == 1)
			{
				*(*(maze + y + 1) + x) = 2; // 벽 뚫기
				backtracking(maze, x, y + 2, width, height, is_step);
			}
			break;
		case 3: // y - 1
			if (*(*(maze + y - 2) + x) == 1)
			{
				*(*(maze + y - 1) + x) = 2; // 벽 뚫기
				backtracking(maze, x, y - 2, width, height, is_step);
			}
			break;
		default:
			break;
		}
	}

	if (is_step == 1)
	{
		*(*(maze + y) + x) = 5; // 현재 셀 방문(현재 위치 표시용)
		print_maze(maze, width, height, is_step);
		*(*(maze + y) + x) = 2; // 현재 셀 방문
	}
}

/// <param name="maze">2차원 미로 행렬</param>
/// <param name="width">미로 가로 길이(벽 포함)</param>
/// <param name="height">미로 세로 길이(벽 포함)</param>
/// <param name="is_step">단계별 출력: 기본값 = false(3)</param>
void eller_algorithm(int** maze, int width, int height, int is_step = 3)
{
	int x_width = (width - 1) / 2; // 벽 제외 미로 가로 길이
	int* sets_count = (int*)calloc(x_width, sizeof(int)); // 각 집합당 원소의 수: 최대 집합 개수 = 벽을 제외한 미로의 가로 길이
	int set = 6; // 집합 명칭(숫자): 집합에 속하지 않은 셀(예약 숫자: 1,2,3,4,5) 값 제외 -> 6부터 시작

	for (int y = 1; y < height; y += 2)
	{
		// 집합에 속하지 않은 빈 셀은 새로운 집합에 할당
		for (int x = 1; x < width; x += 2) if (*(*(maze + y) + x) == 1) *(*(maze + y) + x) = set++;

		// 마지막 행
		if (y == height - 2)
		{
			for (int x = 1; x < width - 2; x += 2) // 마지막 열은 [x + 2] 인덱스를 허용하지 않음
			{
				if (*(*(maze + y) + x) != *(*(maze + y) + x + 2)) // 오른쪽 셀이 같지 않으면 벽 뚫기
				{
					*(*(maze + y) + x + 1) = 2; // 오른쪽 벽 뚫기
				}

				if (is_step == 1) print_maze(maze, width, height, is_step);
			}

		}
		else
		{
			int sets_count_index = 0; // 각 집합당 원소 인덱스
			int index_count = 1; // 각 집합당 원소 카운터: 최대값 = 집합의 원소 수의 최대값, 최소값 = 1(집합당 원소는 최소 1개)
			int sum_of_elements = 1; // 각 집합의 원소 합: 초기값 = 1(집합당 원소는 최소 1개)

			// 수평 벽 연결
			for (int x = 1; x < width; x += 2)
			{
				if (*(*(maze + y) + x) == *(*(maze + y) + x + 2)) { sum_of_elements++; continue; } // 오른쪽 셀이 같은 집합이면 벽 유지

				if (rand() % 2 == 0 && x < width - 2) // 마지막 열은 [x + 2] 인덱스를 허용하지 않음
				{
					*(*(maze + y) + x + 1) = 2; // 오른쪽 벽 뚫기
					*(*(maze + y) + x + 2) = *(*(maze + y) + x); // 오른쪽 집합 -> 현재 집합 연결
					sum_of_elements++;
				}
				else
				{
					*(sets_count + sets_count_index++) = sum_of_elements; // 연속된 집합 원소의 합 저장
					sum_of_elements = 1; // 원소의 합 초기화
				}

				if (is_step == 1) print_maze(maze, width, height, is_step);
			}

			sets_count_index = 0;
			// 수직 벽 연결
			for (int x = 1; x < width; x += 2)
			{
				//printf("index_count: %d, sets_count[%d] = %d\n", index_count, sets_count_index, *(sets_count + sets_count_index));
				// 현재 인덱스 == 집합당 원소 수의 합 배열의 인덱스: 각 집합당 원소의 마지막마다 실행
				if (index_count == sets_count[sets_count_index])
				{
					if (*(sets_count + sets_count_index) == 1) // 집합의 원소합이 1일 때
					{
						*(*(maze + y + 1) + x) = 2; // 아래쪽 벽 뚫기
						*(*(maze + y + 2) + x) = *(*(maze + y) + x); // 아래쪽 집합 -> 현재 집합 연결
					}
					else
					{
						int vertical_count = 0;
						// 수직 벽 연결이 없으면 마지막 집합의 마지막 원소에서 수직 연결
						for (int i = 1; i < *(sets_count + sets_count_index); i++) if (*(*(maze + y + 2) + x - i * 2) == *(*(maze + y) + x)) vertical_count++;
						if (vertical_count == 0)
						{
							*(*(maze + y + 1) + x) = 2; // 아래쪽 벽 뚫기
							*(*(maze + y + 2) + x) = *(*(maze + y) + x); // 아래쪽 집합 -> 현재 집합 연결
						}
					}
					index_count = 1;
					sets_count_index++;
				}
				else
				{
					if (rand() % 2 == 1)
					{
						*(*(maze + y + 1) + x) = 2; // 아래쪽 벽 뚫기
						*(*(maze + y + 2) + x) = *(*(maze + y) + x); // 아래쪽 집합 -> 현재 집합 연결
					}
					index_count++;
				}

				if (is_step == 1) print_maze(maze, width, height, is_step);
			}
			// 집합 배열 초기화
			for (int i = 0; i < x_width; i++) *(sets_count + i) = 0;
		}

		if (is_step == 2) print_maze(maze, width, height, is_step);
	}
	free(sets_count);

	// 출력을 위한 셀 초기화: 모든 셀을 방문 셀로 설정
	for (int y = 1; y < height; y += 2) for (int x = 1; x < width; x += 2) *(*(maze + y) + x) = 2;
}