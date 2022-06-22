#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define MIN_INT -2147483648

int N;
int *dp;
bool *dpFlag;

struct Node
{
    int v;
    int i, fi;
    vector<Node *> c;
    Node(int _v, int _i, int _fi = -1):v(_v), i(_i), fi(_fi){}
};

int max(Node *node)
{
    if (node == nullptr)
    {
        return MIN_INT;
    }
    if (dpFlag[node->i])
    {
        return dp[node->i];
    }
    int ret = node->v;
    for (auto &i : node->c)
    {
        int m = max(i);
        if (ret + m > ret)
        {
            ret += m;
        }
    }
    dp[node->i] = ret;
    dpFlag[node->i] = true;
    return ret;
}

int main()
{
    map<int, Node *> nodeCache;
    cin >> N;
    dp = new int[N + 1];
    dpFlag = new bool[N + 1];
    for (int i = 0; i <= N; ++i)
    {
        dp[i] = 0;
        dpFlag[i] = false;
    }
    for (int i = 1; i <= N; ++i)
    {
        int v;
        cin >> v;
        nodeCache.insert(make_pair(i, new Node(v, i)));
    }
    for (int i = 0; i < N - 1; ++i)
    {
        int c, f;
        cin >> c >> f;
        auto ci = nodeCache.find(c);
        auto fi = nodeCache.find(f);
        ci->second->fi = fi->first;
        fi->second->c.push_back(ci->second);
    }

    int ans = MIN_INT;
    for (auto &i : nodeCache)
    {
        int m = max(i.second);
        ans = m > ans ? m : ans;
    }

    cout << ans;
    return 0;
}