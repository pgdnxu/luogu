#include <iostream>
#include <cmath>

using namespace std;

int N;
int *zz;

struct CacheItem
{
    int v;
    bool s;
};
CacheItem **cache;

void cleanCache()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cache[i][j].s = false;
            cache[i][j].v = 0;
        }
    }
}

void shiftLeftZZ()
{
    int f = zz[0];
    for (int i = 0; i < N - 1; ++i)
    {
        zz[i] = zz[i + 1];
    }
    zz[N - 1] = f;
}

int merge(int l, int r)
{
    if (l >= r)
    {
        return 0;
    }
    
    if (cache[l][r].s)
    {
        return cache[l][r].v;
    }

    int max = -1;
    for (int i = l; i < r; ++i)
    {
        int lv = merge(l, i);
        int rv = merge(i + 1, r);
        int value = zz[l] * zz[i + 1] * zz[(r + 1) % N] + lv + rv;
        if (value > max)
        {
            max = value;
        }
    }
    cache[l][r].v = max;
    cache[l][r].s = true;
    return max;
}

int main()
{
    cin >> N;
    zz = new int[N];
    for (int i = 0; i < N; ++i)
    {
        cin >> zz[i];
    }

    cache = new CacheItem *[N];
    for (int i = 0; i < N; ++i)
    {
        cache[i] = new CacheItem[N];
    }

    int max = -100000000;
    for (int i = 0; i < N; ++i)
    {
        cleanCache();
        int v = merge(0, N - 1);
        if (v > max)
        {
            max = v;
        }
        shiftLeftZZ();
    }
    cout << max;
}
