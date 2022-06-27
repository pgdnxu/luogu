#include <iostream>
#include <map>

using namespace std;

int N, M;
int **dp;

struct Node 
{
    int i, v;
    Node *lc, *rb;
    Node(int _i):i(_i), v(0), lc(nullptr), rb(nullptr) {}
};

int work(Node *n, int m)
{
    if (n == nullptr || m < 0)
        return 0;

    auto &dpi = dp[n->i][m];
    if (m == 0)
        dpi = 0;

    if (dpi >= 0)
        return dpi;

    int max = 0, tmp = 0;

    tmp = work(n->rb, m);
    max = max > tmp ? max : tmp;
    
    for (int i = 1; i <= m; ++i)
    {
        tmp = work(n->lc, i - 1) + work(n->rb, m - i) + n->v;
        max = max > tmp ? max : tmp;
    }

    return dpi = max;
}

int main()
{
    cin >> N >> M;

    dp = new int *[N + 1];
    for (int i = 0; i <= N; ++i)
    {
        dp[i] = new int[M + 2];
        for (int j = 0; j <= M + 1; ++j)
            dp[i][j] = -1;
    }

    map<int, Node *> nodeCache;
    for (int i = 0; i <= N; ++i)
        nodeCache.insert(make_pair(i, new Node(i)));

    int x, v;
    for (int i = 1; i <= N; ++i)
    {
        cin >> x >> v;
        auto ii = nodeCache.find(i);
        auto xi = nodeCache.find(x);

        ii->second->v = v;
        auto tmp = xi->second->lc;
        xi->second->lc = ii->second;
        ii->second->rb = tmp;
    }

    cout << work(nodeCache.find(0)->second, M + 1) << endl;
    return 0;
}