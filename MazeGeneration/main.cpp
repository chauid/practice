#include "main.hpp"

/*
* ��Ʈ��ŷ ����� ����, ���� ���� 78�� ������ ��Ÿ�� ����
* - ��Ȯ�� ������ ��
*/

int main()
{
	srand(time(NULL));

	int width, height, choose, is_step;
	printf("�̷� ���� ����(�� ũ�� ����): ");
	scanf_s("%d", &width);
	printf("�̷� ���� ����(�� ũ�� ����): ");
	scanf_s("%d", &height);

	// ���� ������ �̷��� 1���� ���� = input + (input + 1)
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

	printf("�̷� ���� �˰��� ����(1.����� ��Ʈ��ŷ, 2.���� �˰���): ");
	scanf_s("%d", &choose);
	printf("�ܰ躰�� ����ϱ�(1.������� ���, 2.�������� ���, 3.����): ");
	scanf_s("%d", &is_step);
	if (is_step < 1 || is_step > 3) is_step = 3;

	switch (choose)
	{
	case 1:
		backtracking(maze, 1, 1, width, height, is_step); // ���� ��ġ (1, 1)
		print_maze(maze, width, height, 3);
		break;
	case 2:
		eller_algorithm(maze, width, height, is_step);
		print_maze(maze, width, height, 3);
		break;
	default:
		printf("�ش� ������ ����.\n");
		break;
	}

	/* free memory */
	for (int y = 0; y < height; y++) free(maze[y]);
	free(maze);
	return 0;
}