#include <iostream>

using namespace std;

int n, m;

int map[50][50];
int cache[50][50][50][50];

int max(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
    {
        return 0;
    }
    if (cache[x1][y1][x2][y2] >= 0)
    {
        return cache[x1][y1][x2][y2];
    }
    int t1 = max(x1 - 1, y1, x2 - 1, y2);
    int t2 = max(x1 - 1, y1, x2, y2 - 1);
    int t3 = max(x1, y1 - 1, x2 - 1, y2);
    int t4 = max(x1, y1 - 1, x2, y2 - 1);

    int ret = 0;
    if (x1 == x2 && y1 == y2)
    {
        ret = map[x1][y1];
    }
    else
    {
        ret = map[x1][y1] + map[x2][y2];
    }

    int m1 = t1 > t2 ? t1 : t2;
    int m2 = t3 > t4 ? t3 : t4;
    int m3 = m1 > m2 ? m1 : m2;

    ret += m3;

    cache[x1][y1][x2][y2] = ret;
    return ret;
}

int main()
{
    cin >> m >> n;

    for (int a = 0; a < 50; ++a)
        for (int b = 0; b < 50; ++b)
            for (int c = 0; c < 50; ++c)
                for (int d = 0; d < 50; ++d)
                {
                    cache[a][b][c][d] = -1;
                }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int t;
            cin >> t;
            map[i][j] = t;
        }
    }

    cout << max(m - 1, n - 1, m - 1, n - 1);
    return 0;
}