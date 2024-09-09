#include "main.hpp"

/// <param name="maze">2���� ��� ������</param>
/// <param name="width">�̷� ���� ����</param>
/// <param name="height">�̷� ���� ����</param>
void init_maze_with_wall(int** maze, int width, int height)
{
	// �� �ʱ�ȭ: �� �մ� �� = 4, ���� �� �ִ� �� = 3, �湮�� �� = 2, �湮���� ���� �� = 1
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

/// <param name="matrix">2���� ��� ������</param>
/// <param name="width">X�� ����</param>
/// <param name="height">Y�� ����</param>
void print_maze(int** maze, int width, int height)
{
	for (short y = 0; y < height; y++)
	{
		for (short x = 0; x < width; x++)
		{
			switch (*(*(maze + y) + x))
			{
			case 1:
				printf("��"); // �湮���� ���� ��
				break;
			case 2:
				printf("��"); // �湮�� ��
				break;
			case 3:
				printf("��"); // ��
				break;
			case 4:
				printf("��"); // ��
				break;
			default:
				printf("\ninvalid value.\n");
				return;
			}
		}
		printf("\n");
	}
}

/// <param name="maze">2���� �̷� ���</param>
/// <param name="x">���� x��ǥ</param>
/// <param name="y">���� y��ǥ</param>
void backtracking(int** maze, int x, int y)
{
	//printf("%d, %d �湮\n", x, y);
	*(*(maze + y) + x) = 2; // ���� �� �湮

	int availableCount = 0; // �湮������ ���� �� ����
	Direction direction[4]{};
	if (*(*(maze + y) + x + 1) != 4) // ������ ���� �ε��� ���� ����
	{
		// x + 2 (���� ����� ��ǥ���)
		if (*(*(maze + y) + x + 2) == 1) direction[availableCount++] = Direction::E;
	}
	if (*(*(maze + y) + x - 1) != 4) // ������ ���� �ε��� ���� ����
	{
		// x - 2
		if (*(*(maze + y) + x - 2) == 1) direction[availableCount++] = Direction::W;
	}
	if (*(*(maze + y + 1) + x) != 4) // ������ ���� �ε��� ���� ����
	{
		// y + 2
		if (*(*(maze + y + 2) + x) == 1) direction[availableCount++] = Direction::S;
	}
	if (*(*(maze + y - 1) + x) != 4) // ������ ���� �ε��� ���� ����
	{
		// y - 2
		if (*(*(maze + y - 2) + x) == 1) direction[availableCount++] = Direction::N;
	}
	if (availableCount == 0) return; // back

	// �湮 ���� ����: �� ������ ��->��->��->�� ������� �켱������ ����
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
			if (*(*(maze + y) + x + 2) == 1) // �湮�ϰ��� �� ���� ���� ��ȿ�Ѱ�?
			{
				*(*(maze + y) + x + 1) = 2; // �� �ձ�
				backtracking(maze, x + 2, y);
			}
			break;
		case 1: // x - 1
			if (*(*(maze + y) + x - 2) == 1)
			{
				*(*(maze + y) + x - 1) = 2; // �� �ձ�
				backtracking(maze, x - 2, y);
			}
			break;
		case 2: // y + 1
			if (*(*(maze + y + 2) + x) == 1)
			{
				*(*(maze + y + 1) + x) = 2; // �� �ձ�
				backtracking(maze, x, y + 2);
			}
			break;
		case 3: // y - 1
			if (*(*(maze + y - 2) + x) == 1)
			{
				*(*(maze + y - 1) + x) = 2; // �� �ձ�
				backtracking(maze, x, y - 2);
			}
			break;
		default:
			break;
		}
	}
}

/// <param name="maze">2���� �̷� ���</param>
void eller_algorithm(int** maze)
{
}