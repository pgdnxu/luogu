#include <iostream>
#include <map>

using namespace std;

int N;
int MaxD;

struct Node
{
    Node *l, *r;
    Node():l(nullptr), r(nullptr) {}
};

void d(Node *n, int deep)
{
    if (n == nullptr)
        return;
    if (deep > MaxD)
        MaxD = deep;
    d(n->l, deep + 1);
    d(n->r, deep + 1);
}

int main()
{
    MaxD = 0;
    cin >> N;
    map<int, Node *> nodeCache;
    for (int i = 1; i <= N; ++i)
    {
        nodeCache.insert(make_pair(i, new Node()));
    }
    for (int i = 1; i <= N; ++i)
    {
        int l, r;
        cin >> l >> r;
        auto fi = nodeCache.find(i);
        if (l > 0)
        {
            auto li = nodeCache.find(l);
            fi->second->l = li->second;
        }
        if (r > 0)
        {
            auto ri = nodeCache.find(r);
            fi->second->r = ri->second;
        }
    }
    d(nodeCache.find(1)->second, 1);
    cout << MaxD;
    return 0;
}