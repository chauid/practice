#include "main.hpp"

int main()
{
	srand(time(NULL));

	int width, height, choose;
	printf("미로 가로 길이(벽 크기 제외): ");
	scanf_s("%d", &width);
	printf("미로 세로 길이(벽 크기 제외): ");
	scanf_s("%d", &height);

	// 벽을 포함한 미로의 1차원 길이 = input + (input + 1)
	width = 2 * width + 1;
	height = 2 * height + 1;
	int** maze = (int**)malloc(sizeof(int*) * height);
	if (maze == NULL) { printf("memory allocation error"); return 0; }
	for (short i = 0; i < height; i++)
	{
		maze[i] = (int*)malloc(sizeof(int) * width);
		if (maze[i] == NULL) { printf("memory allocation error"); return 0; }
	}
	init_maze_with_wall(maze, width, height);

	printf("미로 생성 알고리즘 선택(1.재귀적 백트래킹, 2.엘러 알고리즘): ");
	scanf_s("%d", &choose);
	switch (choose)
	{
	case 1:
		backtracking(maze, 1, 1); // 시작 위치 (1, 1)
		print_maze(maze, width, height);
		break;
	case 2:
		eller_algorithm(maze);
		print_maze(maze, width, height);
		break;
	default:

		break;
	}

	/* free memory */
	for (int y = 0; y < height; y++) free(maze[y]);
	free(maze);
	return 0;
}