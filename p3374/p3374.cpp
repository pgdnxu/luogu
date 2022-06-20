#include <iostream>

using namespace std;

int *BIT;
int n;

void add(int i, int v)
{
    while (i <= n)
    {
        BIT[i] += v;
        i += i & -i;
    }
}

int sum(int i)
{
    int ret = 0;
    while (i > 0)
    {
        ret += BIT[i];
        i -= i & -i;
    }
    return ret;
    ;
}

int main()
{
    int m;
    cin >> n >> m;
    BIT = new int[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        BIT[i] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        int v;
        cin >> v;
        add(i, v);
    }
    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            add(b, c);
        }
        else if (a == 2)
        {
            cout << sum(c) - sum(b - 1) << endl;
        }
    }

    return 0;
}