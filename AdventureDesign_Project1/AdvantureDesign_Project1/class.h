#pragma once
using namespace std;

class Bug
{
public:
	int x;
	int y;
	int nx;
	int ny;
	int total_count;  // �̵� Ƚ��
	int move_count;  // Ÿ���� ��� ���Ҵ��� Ȯ���ϴ� Ƚ��(�ִ� : ������ ���� ũ��)
	int Check(int move_count, int size);
	int CheckRange(int nx, int ny, int size);
	int Move(int x, int y, int nx, int ny, int move_count, int total_count, int size, int** Room);
};

class Result
{
public:
	int Acount; // �� ȸ���� �̵� Ƚ��
	double Atime;  // �� ȸ���� �ҿ� �ð�
	int AllMoveCount;  // �� �̵� Ƚ��
	double AllMoveTime;   // �� �ҿ� �ð�
	double Agecount;  // ��� �̵� Ƚ��
	double Agetime;  // ��� �ҿ� �ð�
	void Final_Result(int AllMoveCount, double AllMoveTime, double Agecount, double Agetime);
};