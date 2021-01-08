#include <stdio.h>          // printf(), scanf()
#include <stdlib.h>         // abs()

int puzz[3][3];
int temp[3][3];
int dx[4] = { 0, 1, 0,-1};
int dy[4] = { 1, 0,-1, 0};

void
empty(int *x, int *y)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (!puzz[i][j])
			{
				*x = j;
				*y = i;
				return;
			}
		}
	}
}

void
swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int
cal()
{
	int sum = 0;
	for (int i = 0; i < 9; ++i)
	{
		int a = puzz[i / 3][i % 3];
		if (a)
		{
			a--;
			sum += abs(i / 3 - a / 3) + abs(i % 3 - a % 3);
		}
	}

	return sum;
}

int
dfs(int x, int y, int p, int dep, const int lim)
{
	int h = cal();
	if (h == 0)
		return dep;

	if (dep + h > lim)
		return -1;

	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (p != -1 && i == (p + 2) % 4)
			continue;

		if (0 <= nx && nx < 3 && 0 <= ny && ny < 3)
		{
			swap(&puzz[y][x], &puzz[ny][nx]);
			int res = dfs(nx, ny, i, dep + 1, lim);
			if (res != -1)
				return res;

			swap(&puzz[y][x], &puzz[ny][nx]);
		}
	}

	return -1;
}

int
main(int argc, char **argv)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
			scanf("%d", &puzz[i][j]);
	}

	int x = 0, y = 0;
	empty(&x, &y);

	for (int l = 0; l < 100; ++l)
	{
		for (int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
				temp[i][j] = puzz[i][j];
		}

		int ans = dfs(x, y, -1, 0, l);
		if (ans != -1)
		{
			printf("%d\n", ans);
			break;
		}

		for (int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
				puzz[i][j] = temp[i][j];
		}

		ans = -1;
		if (l == 99)
			printf("%d\n", ans);
	}

	return 0;
}
