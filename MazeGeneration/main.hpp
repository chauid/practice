#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// <summary>
/// ����: ��, ��, ��, ��
/// </summary>
enum Direction
{
	E, W, S, N
};

/// <summary>
/// �̷� �ʱ�ȭ: �� ����
/// </summary>
void init_maze_with_wall(int** maze, int width, int height);

/// <summary>
/// �̷� ��� ���
/// </summary>
void print_maze(int** matrix, int width, int height);

/// <summary>
/// ����� ��Ʈ��ŷ (x,y > 0)
/// </summary>
void backtracking(int** matrix, int x, int y);

/// <summary>
/// Eller's Algorithm
/// </summary>
void eller_algorithm(int** maze);

#endif
