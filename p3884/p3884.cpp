#include <iostream>
#include <map>

struct Node
{
    int i;
    Node *p, *l, *r;
    Node(): i(-1), p(nullptr), l(nullptr), r(nullptr){}
    Node(int _i, Node *_p = nullptr, Node *_l = nullptr, Node *_r = nullptr):
    i(_i), p(_p), l(_l), r(_r){}
};

int *width;

Node* getCommonFather(Node *node, Node *a, Node *b)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->i == a->i)
        return a;
    if (node->i == b->i)
        return b;
    auto left = getCommonFather(node->l, a, b);
    auto right = getCommonFather(node->r, a, b);
    if (left != nullptr && right != nullptr)
        return node;
    return left == nullptr ? right : left;
}

int getDistance(Node *root, Node *sNode, Node *eNode)
{
    if (sNode == nullptr || eNode == nullptr)
    {
        return 0;
    }
    auto cf = getCommonFather(root, sNode, eNode);
    if (cf != nullptr)
    {
        int sPath = 0;
        auto sn = sNode;
        while(sn != cf)
        {
            sn = sn->p;
            sPath++;
        }

        int ePath = 0;
        auto en = eNode;
        while(en != cf)
        {
            en = en->p;
            ePath++;
        }
        return sPath * 2 + ePath;
    }
    return 0;
}

void getHeight(Node *node, int deep, int &max)
{
    if (node == nullptr)
    {
        return;
    }

    width[deep]++;

    if (deep > max)
    {
        max = deep;
    }
    getHeight(node->l, deep + 1, max);
    getHeight(node->r, deep + 1, max);
}

int getHeight(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int max = 0;
    getHeight(node, 1, max);
    return max;
}

int getWidth(int n)
{
    int max = 0;
    for (int i = 0; i < n; ++i)
    {
        if (width[i] > max)
            max = width[i];
    }
    return max;
}

int main()
{
    std::map<int, Node *> nodeCache;

    int N;
    Node *root, *start, *end;

    root = new Node(1);
    nodeCache.insert(std::make_pair(1, root));
    std::cin >> N;

    width = new int[N];
    for (int i = 0; i < N; ++i)
    {
        width[i] = 0;
    }

    for (int i = 0; i < N - 1; ++i)
    {
        int r, c;
        std::cin >> r >> c;

        auto currRootIter = nodeCache.find(r);
        Node *currRoot = nullptr;
        if (currRootIter == nodeCache.end())
        {
            currRoot = new Node(r);
            nodeCache.insert(std::make_pair(r, currRoot));
        }
        else
        {
            currRoot = currRootIter->second;
        }

        auto currChildIter = nodeCache.find(c);
        Node *currChild = nullptr;
        if (currChildIter == nodeCache.end())
        {
            currChild = new Node(c);
            nodeCache.insert(std::make_pair(c, currChild));
        }
        else
        {
            currChild = currChildIter->second;
        }

        currChild->p = currRoot;
        if (currRoot->l == nullptr)
        {
            currRoot->l = currChild;
        }
        else
        {
            currRoot->r = currChild;
        }
    }

    int s, e;
    std::cin >> s >> e;

    auto startIter = nodeCache.find(s);
    if (startIter != nodeCache.end())
    {
        start = startIter->second;
    }

    auto endIter = nodeCache.find(e);
    if (endIter != nodeCache.end())
    {
        end = endIter->second;
    }

    std::cout << getHeight(root) << std::endl;
    std::cout << getWidth(N) << std::endl;
    std::cout << getDistance(root, start, end) << std::endl;

    return 0;
}

