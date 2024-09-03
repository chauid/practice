#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// <summary>
/// 방향: 동, 서, 남, 북
/// </summary>
enum Direction
{
	E, W, S, N
};

/// <summary>
/// 미로 초기화: 벽 생성
/// </summary>
void init_maze_with_wall(int** maze, int width, int height);

/// <summary>
/// 미로 행렬 출력
/// </summary>
void print_maze(int** matrix, int width, int height);

/// <summary>
/// 재귀적 백트래킹 (x,y > 0)
/// </summary>
void backtracking(int** matrix, int x, int y);

/// <summary>
/// Eller's Algorithm
/// </summary>
void eller_algorithm(int** maze);

#endif
