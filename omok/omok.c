#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <string.h>
#include <TCHAR.h>
#define size 10
void input();//입력
void change();//턴변경
void pansu();//판초기화
void pan();//판
void check();//5목확인
void cominput();//컴퓨터입력
void save();
void callsave();

char turn;
int se, ga, end = 0;
int firstcom;//컴퓨터가 처음둘때를 위한것
int re = 0;
char pans[size][size];
int comin;
char name[100];
int _tmain(int argc, _TCHAR* argv[])
{
	do
	{
		int menu;
		printf("메뉴\n");
		printf("1.게임시작\n");
		printf("2.게임불러오기\n");
		for (;;)
		{
			printf("입력:");
			scanf("%d", &menu);
			switch (menu) {
			case 1:
				firstcom = 0;
				turn = 'O';
				printf("이름입력:");
				scanf("%s", name);
				pansu();
				srand((unsigned)time(NULL));
				comin = rand() % 90 + 10;
				while (end == 0)
				{
					pan();
					if (turn == 'O')
					{
						input();
					}
					else if (turn == 'X')
					{
						cominput();
					}
					check();
					change();
				}
				change();
				pan();
				printf("%c가 이겼습니다\n", turn);
				printf("다시 시작하려면:1,종료는:0=>");
				scanf("%d", &re);
				if (re == 1)
				{
					end = 0;
				}
				break;
			case 2:
				firstcom = 1;
				printf("이름입력:");
				scanf("%s", name);
				callsave();
				while (end == 0)
				{
					pan();
					if (turn == 'O')
					{
						input();
					}
					else if (turn == 'X')
					{
						cominput();
					}
					check();
					change();
				}
				change();
				pan();
				printf("%c가 이겼습니다\n", turn);
				printf("다시 시작하려면:1,종료는:0=>");
				scanf("%d", &re);
				if (re == 1)
				{
					end = 0;
				}
				break;
			default:
				printf("입력실패\n");
				continue;
				break;
			}
		}

	} while (re == 1);
	return 0;
}

void input() {
	int in;
	for (;;)
	{
		printf("수입력(0-9.0-9)save(100):");
		scanf("%d", &in);
		if (in == 100)
		{
			printf("세이브 완료!\n");
			save();
		}
		se = in / size;
		ga = in % size;
		if (se<0 || se>size || ga<0 || ga>size || pans[se][ga] != '.')
		{
			printf("다시입력하세요!\n");
			continue;
		}
		pans[se][ga] = turn;
		break;
	}
	return;
}

void cominput() {
	printf("멍청한 컴퓨터%d\n", comin);
	for (;;)
	{
		se = comin / size;
		ga = comin % size;
		if (pans[se][ga] != 'O' && firstcom == 0)
		{
			pans[se][ga] = turn;
		}
		if (se >= 0 && se < size && ga >= 0 && ga < size && pans[se][ga] == 'X' && firstcom == 1)
		{
			if (pans[se + 1][ga] == '.')
			{
				comin = (se + 1) * 10 + ga;
				pans[se + 1][ga] = turn;
			}
			else if (pans[se - 1][ga] == '.')
			{
				comin = (se - 1) * 10 + ga;
				pans[se - 1][ga] = turn;
			}
			else if (pans[se][ga - 1] == '.')
			{
				comin = se * 10 + (ga - 1);
				pans[se][ga - 1] = turn;
			}
			else if (pans[se][ga + 1] == '.')
			{
				comin = se * 10 + (ga + 1);
				pans[se][ga + 1] = turn;
			}
			else if (pans[se - 1][ga - 1] == '.')
			{
				comin = (se - 1) * 10 + (ga - 1);
				pans[se - 1][ga - 1] = turn;
			}
			else if (pans[se + 1][ga + 1] == '.')
			{
				comin = (se + 1) * 10 + (ga + 1);
				pans[se + 1][ga + 1] = turn;
			}
			else if (pans[se + 1][ga - 1] == '.')
			{
				comin = (se + 1) * 10 + (ga - 1);
				pans[se + 1][ga - 1] = turn;
			}
			else if (pans[se - 1][ga + 1] == '.')
			{
				comin = (se - 1) * 10 + (ga + 1);
				pans[se - 1][ga + 1] = turn;
			}
			else
			{
				do {
					srand((unsigned)time(NULL));
					comin = rand() % 90 + 10;
					se = comin / size;
					ga = comin % size;
					if (pans[se][ga] == '.')
					{
						pans[se][ga] = turn;
					}
					else
					{
						continue;
					}
				} while (pans[se][ga] == turn);
			}
		}
		firstcom = 1;
		break;
	}

	return;
}

void change() {
	if (turn == 'O')
	{
		turn = 'X';
	}
	else
	{
		turn = 'O';
	}
}

void pansu() {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pans[i][j] = '.';
		}
	}
}

void pan() {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%c ", pans[i][j]);
		}
		printf("\n");
	}
}

void check() {
	int s[4] = { se, se, se, se };
	int g[4] = { ga, ga, ga, ga };
	int cnt[4] = { 0, 0, 0, 0 };
	while (pans[s[0]][g[0]] == turn)
	{
		s[0] += -1;
		cnt[0]++;
	}
	s[0] = se;
	while (pans[s[0]][g[0]] == turn)
	{
		s[0] += 1;
		cnt[0]++;
	}
	if (cnt[0] == 6)
	{
		end = 1;
	}


	while (pans[s[1]][g[1]] == turn)
	{
		g[1] += -1;
		cnt[1]++;
	}
	g[1] = ga;
	while (pans[s[1]][g[1]] == turn)
	{
		g[1] += 1;
		cnt[1]++;
	}
	if (cnt[1] == 6)
	{
		end = 1;
	}


	while (pans[s[2]][g[2]] == turn)
	{
		s[2] += -1;
		g[2] += -1;
		cnt[2]++;
	}
	s[2] = se;
	g[2] = ga;
	while (pans[s[2]][g[2]] == turn)
	{
		s[2] += 1;
		g[2] += 1;
		cnt[2]++;
	}
	if (cnt[2] == 6)
	{
		end = 1;
	}


	while (pans[s[3]][g[3]] == turn)
	{
		s[3] += -1;
		g[3] += 1;
		cnt[3]++;
	}
	s[3] = se;
	g[3] = ga;
	while (pans[s[3]][g[3]] == turn)
	{
		s[3] += 1;
		g[3] += -1;
		cnt[3]++;
	}
	if (cnt[3] == 6)
	{
		end = 1;
	}

}

void save() {
	char na[100] = "c:\\";
	strcat(na, name);
	strcat(na, ".txt");
	FILE* in;
	in = fopen(na, "w");

	fprintf(in, "%d", comin);
	fprintf(in, "%c", turn);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fprintf(in, "%c", pans[i][j]);
		}
	}
	fclose(in);
}

void callsave() {
	char na[100] = "c:\\";
	strcat(na, name);
	strcat(na, ".txt");
	FILE* call;
	call = fopen(na, "r");

	fscanf(call, "%d", &comin);
	fscanf(call, "%c", &turn);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fscanf(call, "%c", &pans[i][j]);
		}
	}
	fclose(call);
}