#include "main.hpp"

/// <param name="maze">2���� ��� ������</param>
/// <param name="width">�̷� ���� ����(�� ����)</param>
/// <param name="height">�̷� ���� ����(�� ����)</param>
void init_maze_with_wall(int** maze, int width, int height)
{
	// �� �ʱ�ȭ: �� �մ� �� = 4, ���� �� �ִ� �� = 3, �湮�� �� = 2, �湮���� ���� �� = 1
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

/// <param name="matrix">2���� ��� ������</param>
/// <param name="width">�̷� ���� ����(�� ����)</param>
/// <param name="height">�̷� ���� ����(�� ����)</param>
/// /// <param name="is_step">�ܰ躰 ��� ����: �⺻�� = false(3)</param>
void print_maze(int** maze, int width, int height, int is_step)
{
	// �̷� �Ա� ����: �ܰ躰 ����� �ƴ� ���
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
			case 5:
				printf("��"); // Ư�� ���
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

/// <param name="maze">2���� �̷� ���</param>
/// <param name="x">���� x��ǥ</param>
/// <param name="y">���� y��ǥ</param>
/// <param name="width">����� ���� ��: �̷� ���� ����(�� ����)</param>
/// <param name="height">����� ���� ��: �̷� ���� ����(�� ����)</param>
/// <param name="is_step">�ܰ躰 ���: �⺻�� = false(3)</param>
void backtracking(int** maze, int x, int y, int width, int height, int is_step = 3)
{
	//printf("%d, %d �湮\n", x, y);
	*(*(maze + y) + x) = 5; // ���� �� �湮(���� ��ġ ǥ�ÿ�)

	int available_count = 0; // �湮������ ���� �� ����
	Direction direction[4]{};
	if (*(*(maze + y) + x + 1) != 4) // ������ ���� �ε��� ���� ����
	{
		// x + 2 (���� ����� ��ǥ���)
		if (*(*(maze + y) + x + 2) == 1) direction[available_count++] = Direction::E;
	}
	if (*(*(maze + y) + x - 1) != 4) // ������ ���� �ε��� ���� ����
	{
		// x - 2
		if (*(*(maze + y) + x - 2) == 1) direction[available_count++] = Direction::W;
	}
	if (*(*(maze + y + 1) + x) != 4) // ������ ���� �ε��� ���� ����
	{
		// y + 2
		if (*(*(maze + y + 2) + x) == 1) direction[available_count++] = Direction::S;
	}
	if (*(*(maze + y - 1) + x) != 4) // ������ ���� �ε��� ���� ����
	{
		// y - 2
		if (*(*(maze + y - 2) + x) == 1) direction[available_count++] = Direction::N;
	}
	if (available_count == 0) // ���ٸ� ��
	{
		if (is_step == 2) print_maze(maze, width, height, is_step);
		*(*(maze + y) + x) = 2; // ���� �� �湮
		return;
	}

	// �湮 ���� ����: �� ������ ��->��->��->�� ������� �켱������ ����
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
		*(*(maze + y) + x) = 2; // ���� �� �湮
		switch (direction[visit])
		{
		case 0: // x + 1
			if (*(*(maze + y) + x + 2) == 1) // �湮�ϰ��� �� ���� ���� ��ȿ�Ѱ�?
			{
				*(*(maze + y) + x + 1) = 2; // �� �ձ�
				backtracking(maze, x + 2, y, width, height, is_step);
			}
			break;
		case 1: // x - 1
			if (*(*(maze + y) + x - 2) == 1)
			{
				*(*(maze + y) + x - 1) = 2; // �� �ձ�
				backtracking(maze, x - 2, y, width, height, is_step);
			}
			break;
		case 2: // y + 1
			if (*(*(maze + y + 2) + x) == 1)
			{
				*(*(maze + y + 1) + x) = 2; // �� �ձ�
				backtracking(maze, x, y + 2, width, height, is_step);
			}
			break;
		case 3: // y - 1
			if (*(*(maze + y - 2) + x) == 1)
			{
				*(*(maze + y - 1) + x) = 2; // �� �ձ�
				backtracking(maze, x, y - 2, width, height, is_step);
			}
			break;
		default:
			break;
		}
	}

	if (is_step == 1)
	{
		*(*(maze + y) + x) = 5; // ���� �� �湮(���� ��ġ ǥ�ÿ�)
		print_maze(maze, width, height, is_step);
		*(*(maze + y) + x) = 2; // ���� �� �湮
	}
}

/// <param name="maze">2���� �̷� ���</param>
/// <param name="width">�̷� ���� ����(�� ����)</param>
/// <param name="height">�̷� ���� ����(�� ����)</param>
/// <param name="is_step">�ܰ躰 ���: �⺻�� = false(3)</param>
void eller_algorithm(int** maze, int width, int height, int is_step = 3)
{
	int x_width = (width - 1) / 2; // �� ���� �̷� ���� ����
	int* sets_count = (int*)calloc(x_width, sizeof(int)); // �� ���մ� ������ ��: �ִ� ���� ���� = ���� ������ �̷��� ���� ����
	int set = 6; // ���� ��Ī(����): ���տ� ������ ���� ��(���� ����: 1,2,3,4,5) �� ���� -> 6���� ����

	for (int y = 1; y < height; y += 2)
	{
		// ���տ� ������ ���� �� ���� ���ο� ���տ� �Ҵ�
		for (int x = 1; x < width; x += 2) if (*(*(maze + y) + x) == 1) *(*(maze + y) + x) = set++;

		// ������ ��
		if (y == height - 2)
		{
			for (int x = 1; x < width - 2; x += 2) // ������ ���� [x + 2] �ε����� ������� ����
			{
				if (*(*(maze + y) + x) != *(*(maze + y) + x + 2)) // ������ ���� ���� ������ �� �ձ�
				{
					*(*(maze + y) + x + 1) = 2; // ������ �� �ձ�
				}

				if (is_step == 1) print_maze(maze, width, height, is_step);
			}

		}
		else
		{
			int sets_count_index = 0; // �� ���մ� ���� �ε���
			int index_count = 1; // �� ���մ� ���� ī����: �ִ밪 = ������ ���� ���� �ִ밪, �ּҰ� = 1(���մ� ���Ҵ� �ּ� 1��)
			int sum_of_elements = 1; // �� ������ ���� ��: �ʱⰪ = 1(���մ� ���Ҵ� �ּ� 1��)

			// ���� �� ����
			for (int x = 1; x < width; x += 2)
			{
				if (*(*(maze + y) + x) == *(*(maze + y) + x + 2)) { sum_of_elements++; continue; } // ������ ���� ���� �����̸� �� ����

				if (rand() % 2 == 0 && x < width - 2) // ������ ���� [x + 2] �ε����� ������� ����
				{
					*(*(maze + y) + x + 1) = 2; // ������ �� �ձ�
					*(*(maze + y) + x + 2) = *(*(maze + y) + x); // ������ ���� -> ���� ���� ����
					sum_of_elements++;
				}
				else
				{
					*(sets_count + sets_count_index++) = sum_of_elements; // ���ӵ� ���� ������ �� ����
					sum_of_elements = 1; // ������ �� �ʱ�ȭ
				}

				if (is_step == 1) print_maze(maze, width, height, is_step);
			}

			sets_count_index = 0;
			// ���� �� ����
			for (int x = 1; x < width; x += 2)
			{
				//printf("index_count: %d, sets_count[%d] = %d\n", index_count, sets_count_index, *(sets_count + sets_count_index));
				// ���� �ε��� == ���մ� ���� ���� �� �迭�� �ε���: �� ���մ� ������ ���������� ����
				if (index_count == sets_count[sets_count_index])
				{
					if (*(sets_count + sets_count_index) == 1) // ������ �������� 1�� ��
					{
						*(*(maze + y + 1) + x) = 2; // �Ʒ��� �� �ձ�
						*(*(maze + y + 2) + x) = *(*(maze + y) + x); // �Ʒ��� ���� -> ���� ���� ����
					}
					else
					{
						int vertical_count = 0;
						// ���� �� ������ ������ ������ ������ ������ ���ҿ��� ���� ����
						for (int i = 1; i < *(sets_count + sets_count_index); i++) if (*(*(maze + y + 2) + x - i * 2) == *(*(maze + y) + x)) vertical_count++;
						if (vertical_count == 0)
						{
							*(*(maze + y + 1) + x) = 2; // �Ʒ��� �� �ձ�
							*(*(maze + y + 2) + x) = *(*(maze + y) + x); // �Ʒ��� ���� -> ���� ���� ����
						}
					}
					index_count = 1;
					sets_count_index++;
				}
				else
				{
					if (rand() % 2 == 1)
					{
						*(*(maze + y + 1) + x) = 2; // �Ʒ��� �� �ձ�
						*(*(maze + y + 2) + x) = *(*(maze + y) + x); // �Ʒ��� ���� -> ���� ���� ����
					}
					index_count++;
				}

				if (is_step == 1) print_maze(maze, width, height, is_step);
			}
			// ���� �迭 �ʱ�ȭ
			for (int i = 0; i < x_width; i++) *(sets_count + i) = 0;
		}

		if (is_step == 2) print_maze(maze, width, height, is_step);
	}
	free(sets_count);

	// ����� ���� �� �ʱ�ȭ: ��� ���� �湮 ���� ����
	for (int y = 1; y < height; y += 2) for (int x = 1; x < width; x += 2) *(*(maze + y) + x) = 2;
}