#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
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
/// <param name="maze">2���� ��� ������</param>
/// <param name="width">�̷� ���� ����(�� ����)</param>
/// <param name="height">�̷� ���� ����(�� ����)</param>
void init_maze_with_wall(int** maze, int width, int height);

/// <summary>
/// �̷� �Ա� ���� �� �̷� ��� ���
/// </summary>
/// <param name="matrix">2���� ��� ������</param>
/// <param name="width">�̷� ���� ����(�� ����)</param>
/// <param name="height">�̷� ���� ����(�� ����)</param>
/// <param name="is_step">�ܰ躰 ��� ����: �⺻�� = false(3)</param>
void print_maze(int** matrix, int width, int height, int is_step);

/// <summary>
/// ��Ʈ��ŷ: ���� ��ǥ x,y (x,y > 0)
/// </summary>
/// <param name="maze">2���� �̷� ���</param>
/// <param name="x">���� x��ǥ</param>
/// <param name="y">���� y��ǥ</param>
/// <param name="width">����� ���� ��: �̷� ���� ����(�� ����)</param>
/// <param name="height">����� ���� ��: �̷� ���� ����(�� ����)</param>
/// <param name="is_step">�ܰ躰 ���: �⺻�� = false(3)</param>
void backtracking(int** matrix, int x, int y, int width, int height, int is_step);

/// <summary>
/// Eller's Algorithm: �̹� ��� ���� �����Ѵٴ� ����
/// </summary>
/// <param name="maze">2���� �̷� ���</param>
/// <param name="width">�̷� ���� ����(�� ����)</param>
/// <param name="height">�̷� ���� ����(�� ����)</param>
/// <param name="is_step">�ܰ躰 ���: �⺻�� = false(3)</param>
void eller_algorithm(int** maze, int width, int height, int is_step);

#endif
