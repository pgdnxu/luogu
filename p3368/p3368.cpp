#include <iostream>
#include <fstream>

using namespace std;

int N;
int *BIT, *a;

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
    int m;
    cin >> N >> m;

    BIT = new int[N + 1];
    a = new int[N + 1];
    for (int i = 0; i <= N; ++i)
    {
        BIT[i] = 0;
        a[i] = 0;
    }
    for (int i = 1; i <= N; ++i)
    {
        cin >> a[i];
        add(i, a[i] - a[i - 1]);
    }

    for (int i = 0; i < m; ++i)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            add(x, k);
            if (y < N)
            {
                add(y + 1, -k);
            }
        }
        else if (t == 2)
        {
            int x;
            cin >> x;
            cout << sum(x) << endl;
        }
    }
    return 0;
}