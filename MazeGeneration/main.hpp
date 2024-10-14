#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
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
/// <param name="maze">2차원 행렬 포인터</param>
/// <param name="width">미로 가로 길이(벽 포함)</param>
/// <param name="height">미로 세로 길이(벽 포함)</param>
void init_maze_with_wall(int** maze, int width, int height);

/// <summary>
/// 미로 입구 생성 및 미로 행렬 출력
/// </summary>
/// <param name="matrix">2차원 행렬 포인터</param>
/// <param name="width">미로 가로 길이(벽 포함)</param>
/// <param name="height">미로 세로 길이(벽 포함)</param>
/// <param name="is_step">단계별 출력 여부: 기본값 = false(3)</param>
void print_maze(int** matrix, int width, int height, int is_step);

/// <summary>
/// 백트래킹: 시작 좌표 x,y (x,y > 0)
/// </summary>
/// <param name="maze">2차원 미로 행렬</param>
/// <param name="x">현재 x좌표</param>
/// <param name="y">현재 y좌표</param>
/// <param name="width">출력을 위한 값: 미로 가로 길이(벽 포함)</param>
/// <param name="height">출력을 위한 값: 미로 세로 길이(벽 포함)</param>
/// <param name="is_step">단계별 출력: 기본값 = false(3)</param>
void backtracking(int** matrix, int x, int y, int width, int height, int is_step);

/// <summary>
/// Eller's Algorithm: 이미 모든 벽이 존재한다는 가정
/// </summary>
/// <param name="maze">2차원 미로 행렬</param>
/// <param name="width">미로 가로 길이(벽 포함)</param>
/// <param name="height">미로 세로 길이(벽 포함)</param>
/// <param name="is_step">단계별 출력: 기본값 = false(3)</param>
void eller_algorithm(int** maze, int width, int height, int is_step);

#endif
