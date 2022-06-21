#include <iostream>
#include <algorithm>
#include <fstream>

int N, *BIT;
int *a, *b, *c;

void add(int i, int v)
{
    while(i <= N)
    {
        BIT[i] += v;
        i += i & -i;
    }
}

int sum(int i)
{
    int ret = 0;
    while(i > 0)
    {
        ret += BIT[i];
        i -= i & -i;
    }
    return ret;
}

int main()
{
    std::cin >> N;

    BIT = new int[N + 1];
    a = new int[N + 1];
    b = new int[N + 1];
    c = new int[N + 1];

    for (int i = 0; i <= N; ++i)
    {
        BIT[i] = 0;
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    for (int i = 0; i < N; ++i)
    {
        std::cin >> a[i];
        b[i] = a[i];
    }

    std::sort(b, b + N);
    
    int rcount = 1;
    c[rcount] = b[0];
    for (int i = 1; i < N; ++i)
    {
        if (b[i] != b[i - 1])
        {
            c[++rcount] = b[i];
        }
    }
    
    long long ans = 0;
    for (int i = N - 1; i >= 0; --i)
    {
        int j = std::lower_bound(c + 1, c + rcount + 1, a[i]) - c;
        ans += sum(j - 1);
        add(j, 1);
    }
    std::cout << ans << std::endl;
    return 0;
}