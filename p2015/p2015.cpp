#include <iostream>
#include <map>

using namespace std;

#define MIN_INT -2147483648
int N, Q;

struct Node
{
    long long v;
    int i, fi;
    Node *l, *r;
    Node(int _i):i(_i), fi(-1), v(0), l(nullptr), r(nullptr) {}
};

Node *root;

struct D
{
    bool isSet;
    long long v;
};
D **dp;

long long work(Node *node, int n)
{
    if (node == nullptr)
    {
        return 0;
    }

    if (n < 0)
    {
        return 0;
    }

    if (n == 0)
    {
        return node->v;
    }

    if (node->l == nullptr && node->r == nullptr)
    {
        return node->v;
    }

    if (dp[node->i][n].isSet)
    {
        return dp[node->i][n].v;
    }

    long long max = MIN_INT;
    for (int i = 0; i <= n; ++i)
    {
        long long lm = work(node->l, i - 1);
        long long rm = work(node->r, n - i - 1);
        if (lm + rm > max)
        {
            max = lm + rm;
        }
    }
    long long ret = 0;
    if (max >= 0)
    {
        ret = max + node->v;
    }
    if (ret > dp[node->i][n].v)
    {
        dp[node->i][n].v = ret;
        dp[node->i][n].isSet = true;
    }
    
    return ret;
}

int main()
{
    cin >> N >> Q;
    dp = new D *[N + 1];
    for (int i = 0; i <= N; ++i)
    {
        dp[i] = new D[Q + 1];
        for (int j = 0; j <= Q; ++j)
        {
            dp[i][j].v = MIN_INT;
            dp[i][j].isSet = false;
        }
    }

    map<int, Node *> nodeCache;
    for (int i = 1; i <= N; ++i)
    {
        nodeCache.insert(make_pair(i, new Node(i)));
    }
    for (int i = 0; i < N - 1; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        auto ia = nodeCache.find(a);
        auto ib = nodeCache.find(b);
        Node *f, *ch;
        if (a == 1)
        {
            root = ia->second;
            f = ia->second;
            ch = ib->second;
        }
        else if (b == 1)
        {
            root = ib->second;
            f = ib->second;
            ch = ia->second;
        }

        f = ia->second;
        ch = ib->second;

        ch->v = c;
        ch->fi = f->i;
        if (f->l == nullptr)
        {
            f->l = ch;
        }
        else
        {
            f->r = ch;
        }
    }
    
    cout << work(root, Q);

    return 0;
}
