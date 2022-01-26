#pragma once
using namespace std;

class Bug
{
public:
	int x;
	int y;
	int nx;
	int ny;
	int total_count;  // 이동 횟수
	int move_count;  // 타일을 모두 돌았는지 확인하는 횟수(최대 : 설정한 방의 크기)
	int Check(int move_count, int size);
	int CheckRange(int nx, int ny, int size);
	int Move(int x, int y, int nx, int ny, int move_count, int total_count, int size, int** Room);
};

class Result
{
public:
	int Acount; // 각 회차별 이동 횟수
	double Atime;  // 각 회차별 소요 시간
	int AllMoveCount;  // 총 이동 횟수
	double AllMoveTime;   // 총 소요 시간
	double Agecount;  // 평균 이동 횟수
	double Agetime;  // 평균 소요 시간
	void Final_Result(int AllMoveCount, double AllMoveTime, double Agecount, double Agetime);
};