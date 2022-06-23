#include <iostream>

using namespace std;

#define MIN_INT -100000
#define MAX_INT 100000

int N;
int *s;
struct Info
{
    int s;
    int min, max;
    bool isSet;
    Info():s(0), min(MAX_INT), max(MIN_INT), isSet(false) {}
    void reset()
    {
        s = 0;
        min = MAX_INT;
        max = MIN_INT;
        isSet = false;
    }
};
Info **dp;

void shiftLeft()
{
    int t = s[0];
    for (int i = 0; i < N - 1; ++i)
    {
        s[i] = s[i + 1];
    }
    s[N - 1] = t;
}

bool work(int a, int b)
{
    if (a > b)
    {
        return false;
    }
    if (dp[a][b].isSet)
    {
        return true;
    }
    if (a == b)
    {
        Info &t = dp[a][a];
        t.s = s[a];
        t.max = t.min = 0;
        t.isSet = true;
        return true;
    }
    for (int k = a; k < b; ++k)
    {
        bool isA = work(a, k);
        bool isB = work(k + 1, b);
        if (isA && isB)
        {
            auto &t = dp[a][b];
            int ss = dp[a][k].s + dp[k + 1][b].s;
            int min = dp[a][k].min + dp[k + 1][b].min + ss;
            int max = dp[a][k].max + dp[k + 1][b].max + ss;
            if (min < t.min)
            {
                t.min = min;
            }
            if (max > t.max)
            {
                t.max = max;
            }
            t.s = ss;
            t.isSet = true;
        }
    }
    return dp[a][b].isSet;
}

void reset()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            dp[i][j].reset();
        }
    }
}

int main()
{
    cin >> N;
    s = new int[N];
    dp = new Info*[N];
    for (int i = 0; i < N; ++i)
    {
        cin >> s[i];
        dp[i] = new Info[N];
    }
    reset();

    int max = MIN_INT;
    int min = MAX_INT;

    for (int i = 0; i < N; ++i)
    {
        work(0, N - 1);
        auto &t = dp[0][N - 1];
        if (t.min < min)
        {
            min = t.min;
        }
        if (t.max > max)
        {
            max = t.max;
        }
        reset();
        shiftLeft();
    }
    cout << min << endl
         << max;

    return 0;
}