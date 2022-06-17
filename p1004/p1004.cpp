#include <iostream>

using namespace std;

int n;

int map[9][9];
int cache[9][9][9][9];

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
    cin >> n;

    for (int a = 0; a < n; ++a)
        for (int b = 0; b < n; ++b)
            for (int c = 0; c < n; ++c)
                for (int d = 0; d < n; ++d)
                {
                    cache[a][b][c][d] = -1;
                }

    while (true)
    {
        int x, y, v;
        cin >> x >> y >> v;
        if (x == 0 && y == 0 && v == 0)
            break;
        x -= 1;
        y -= 1;
        if (x >= 0 && x < n && y >= 0 && y < n)
        {
            map[x][y] = v;
        }
    }

    cout << max(n - 1, n - 1, n - 1, n - 1);
    return 0;
}