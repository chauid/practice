#include "main.hpp"

/// <param name="maze">2차원 행렬 포인터</param>
/// <param name="width">미로 가로 길이</param>
/// <param name="height">미로 세로 길이</param>
void init_maze_with_wall(int** maze, int width, int height)
{
	// 벽 초기화: 못 뚫는 벽 = 4, 뚫을 수 있는 벽 = 3, 방문한 셀 = 2, 방문하지 않은 셀 = 1
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y % 2 == 0 || x % 2 == 0)
			{
				if ((y % 2 == 0 && x % 2 == 0) || y == 0 || y == height - 1 || x == 0 || x == width - 1) maze[y][x] = 4;
				else maze[y][x] = 3;
			}
			else maze[y][x] = 1;
		}
	}
}

/// <param name="matrix">2차원 행렬 포인터</param>
/// <param name="width">X축 길이</param>
/// <param name="height">Y축 길이</param>
void print_maze(int** maze, int width, int height)
{
	for (short y = 0; y < height; y++)
	{
		for (short x = 0; x < width; x++)
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
			default:
				printf("\ninvalid value.\n");
				return;
			}
		}
		printf("\n");
	}
}

/// <param name="maze">2차원 미로 행렬</param>
/// <param name="x">현재 x좌표</param>
/// <param name="y">현재 y좌표</param>
void backtracking(int** maze, int x, int y)
{
	//printf("%d, %d 방문\n", x, y);
	*(*(maze + y) + x) = 2; // 현재 셀 방문

	int availableCount = 0; // 방문가능한 인접 셀 개수
	Direction direction[4]{};
	if (*(*(maze + y) + x + 1) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// x + 2 (벽을 고려한 좌표계산)
		if (*(*(maze + y) + x + 2) == 1) direction[availableCount++] = Direction::E;
	}
	if (*(*(maze + y) + x - 1) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// x - 2
		if (*(*(maze + y) + x - 2) == 1) direction[availableCount++] = Direction::W;
	}
	if (*(*(maze + y + 1) + x) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// y + 2
		if (*(*(maze + y + 2) + x) == 1) direction[availableCount++] = Direction::S;
	}
	if (*(*(maze + y - 1) + x) != 4) // 허용되지 않은 인덱스 접근 제외
	{
		// y - 2
		if (*(*(maze + y - 2) + x) == 1) direction[availableCount++] = Direction::N;
	}
	if (availableCount == 0) return; // back

	// 방문 순서 섞기: 안 섞으면 동->서->남->북 순서대로 우선순위를 가짐
	for (int i = 0; i < availableCount; i++)
	{
		int random = i + rand() % (availableCount - i);
		Direction temp = direction[i];
		direction[i] = direction[random];
		direction[random] = temp;
	}

	for (int visit = 0; visit < availableCount; visit++)
	{
		switch (direction[visit])
		{
		case 0: // x + 1
			if (*(*(maze + y) + x + 2) == 1) // 방문하고자 한 셀이 아직 유효한가?
			{
				*(*(maze + y) + x + 1) = 2; // 벽 뚫기
				backtracking(maze, x + 2, y);
			}
			break;
		case 1: // x - 1
			if (*(*(maze + y) + x - 2) == 1)
			{
				*(*(maze + y) + x - 1) = 2; // 벽 뚫기
				backtracking(maze, x - 2, y);
			}
			break;
		case 2: // y + 1
			if (*(*(maze + y + 2) + x) == 1)
			{
				*(*(maze + y + 1) + x) = 2; // 벽 뚫기
				backtracking(maze, x, y + 2);
			}
			break;
		case 3: // y - 1
			if (*(*(maze + y - 2) + x) == 1)
			{
				*(*(maze + y - 1) + x) = 2; // 벽 뚫기
				backtracking(maze, x, y - 2);
			}
			break;
		default:
			break;
		}
	}
}

/// <param name="maze">2차원 미로 행렬</param>
void eller_algorithm(int** maze)
{
}