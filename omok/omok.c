#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <string.h>
#include <TCHAR.h>
#define size 10
void input();//�Է�
void change();//�Ϻ���
void pansu();//���ʱ�ȭ
void pan();//��
void check();//5��Ȯ��
void cominput();//��ǻ���Է�
void save();
void callsave();

char turn;
int se, ga, end = 0;
int firstcom;//��ǻ�Ͱ� ó���Ѷ��� ���Ѱ�
int re = 0;
char pans[size][size];
int comin;
char name[100];
int _tmain(int argc, _TCHAR* argv[])
{
	do
	{
		int menu;
		printf("�޴�\n");
		printf("1.���ӽ���\n");
		printf("2.���Ӻҷ�����\n");
		for (;;)
		{
			printf("�Է�:");
			scanf("%d", &menu);
			switch (menu) {
			case 1:
				firstcom = 0;
				turn = 'O';
				printf("�̸��Է�:");
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
				printf("%c�� �̰���ϴ�\n", turn);
				printf("�ٽ� �����Ϸ���:1,�����:0=>");
				scanf("%d", &re);
				if (re == 1)
				{
					end = 0;
				}
				break;
			case 2:
				firstcom = 1;
				printf("�̸��Է�:");
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
				printf("%c�� �̰���ϴ�\n", turn);
				printf("�ٽ� �����Ϸ���:1,�����:0=>");
				scanf("%d", &re);
				if (re == 1)
				{
					end = 0;
				}
				break;
			default:
				printf("�Է½���\n");
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
		printf("���Է�(0-9.0-9)save(100):");
		scanf("%d", &in);
		if (in == 100)
		{
			printf("���̺� �Ϸ�!\n");
			save();
		}
		se = in / size;
		ga = in % size;
		if (se<0 || se>size || ga<0 || ga>size || pans[se][ga] != '.')
		{
			printf("�ٽ��Է��ϼ���!\n");
			continue;
		}
		pans[se][ga] = turn;
		break;
	}
	return;
}

void cominput() {
	printf("��û�� ��ǻ��%d\n", comin);
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