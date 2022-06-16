#include <iostream>

int N, K;
int *set;
int *rank;

void init(int n)
{
    set = new int[n * 3];
    rank = new int[n * 3];
    for (int i = 0; i < n * 3; ++i)
    {
        set[i] = i;
        rank[i] = 0;
    }
}

int find(int x)
{
    if (set[x] == x)
        return x;
    return set[x] = find(set[x]);
}

bool same(int x, int y)
{
    return find(x) == find(y);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x == y) return;

    if (rank[x] == rank[y])
    {
        set[y] = x;
        rank[x]++;
    }
    else
    {
        if (rank[x] > rank[y]) set[y] = x;
        if (rank[x] < rank[y]) set[x] = y;
    }
}

int main()
{
    std::cin >> N >> K;
    init(N);
    int ans = 0;
    int N2 = N * 2;
    for (int i = 0; i < K; ++i)
    {
        int t, x, y;
        std::cin >> t >> x >> y;
        x -= 1;
        y -= 1;
        if (x < 0 || x >= N || y < 0 || y >= N || t == 2 && x == y)
        {
            ans++;
            continue;
        }

        if (t == 1)
        {
            if (same(x, y + N) || same(x, y + N2))
            {
                ans++;
            }
            else
            {
                merge(x, y);
                merge(x + N, y + N);
                merge(x + N2, y + N2);
            }
        }
        else if (t == 2)
        {
            if (same(x, y) || same(x, y + N2))
            {
                ans++;
            }
            else
            {
                merge(x, y + N);
                merge(x + N, y + N2);
                merge(x + N2, y);
            }
        }
    }
    std::cout << ans;
    return 0;
}
