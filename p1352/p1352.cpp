#include <iostream>
#include <map>
#include <vector>

class Node
{
public:
    int n;
    int h;
    bool hasF;
    std::vector<Node *> c;
    Node():n(-1), h(0), hasF(false){}
};

int n;
int *h;
std::map<int, Node*> nodeCache;

struct Cache
{
    int h;
    bool isSet;
    Cache() : h(0), isSet(false){}
};

Cache **hCache;

#define MAX(a, b) (a) > (b) ? (a) : (b)

Node* findNodeInCache(int i)
{
    auto iter = nodeCache.find(i);
    if (iter != nodeCache.end())
    {
        return iter->second;
    }
    return nullptr;
}

void addNodeInCache(int key, Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    nodeCache.insert(std::make_pair(key, node));
}

Node* findRoot()
{
    for(auto &iter : nodeCache)
    {
        if (!iter.second->hasF)
        {
            return iter.second;
        }
    }
    return nullptr;
}

int maxHappy(Node *node, int isJoin)
{
    int maxValue = 0;

    if (node == nullptr)
    {
        return maxValue;
    }

    if (hCache[node->n][isJoin].isSet)
    {
        return hCache[node->n][isJoin].h;
    }

    if (isJoin == 0)
    {
       for (auto &ci : node->c)
       {
           int join = maxHappy(ci, 1);
           int notJoin = maxHappy(ci, 0);
           maxValue += MAX(join, notJoin);
       }
    }
    else
    {
        maxValue = node->h;
        for (auto &ci : node->c)
        {
            maxValue += maxHappy(ci, 0);
        }
    }

    hCache[node->n][isJoin].h = maxValue;
    hCache[node->n][isJoin].isSet = true;
    return maxValue;
}

int main()
{
    std::cin >> n;
    h = new int[n];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> h[i];
    }

    hCache = new Cache *[n];
    for (int i = 0; i < n; ++i)
    {
        hCache[i] = new Cache[2];
    }

    for (int i = 0; i < n - 1; ++i)
    {
        int l, k;
        std::cin >> l;
        std::cin >> k;

        l -= 1;
        k -= 1;

        auto e = findNodeInCache(l);
        if (e == nullptr)
        {
            e = new Node();
            e->n = l;
            e->h = h[l];
            addNodeInCache(l, e);
        }

        auto b = findNodeInCache(k);
        if (b == nullptr)
        {
            b = new Node();
            b->n = k;
            b->h = h[k];
            addNodeInCache(k, b);
        }

        e->hasF = true;
        b->c.push_back(e);
    }

    auto root = findRoot();

    int a = maxHappy(root, 0);
    int b = maxHappy(root, 1);

    int max = MAX(a, b);
    std::cout << max;

    return 0;
}
