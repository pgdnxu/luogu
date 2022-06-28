#include <iostream>
#include <string>

using namespace std;

int N, K;

struct HPNum
{
    int len;
    unsigned short *num;
    HPNum(int _len) : len(_len) 
    { 
        num = new unsigned short[_len + 1];
        for (int i = 0; i < _len + 1; ++i)
            num[i] = 0;
    }
    void print()
    {
        for (int i = len; i >= 1; --i)
            cout << num[i];
        cout << endl;
    }

};
HPNum *One;
HPNum ***dp;
int mul(unsigned short *a, int aLen, unsigned short *b, int bLen, unsigned short *prod)
{
    unsigned short carry = 0;
    for (int i = 1; i <= aLen; ++i)
    {
        carry = 0;
        for (int j = 1; j <= bLen; ++j)
        {
            prod[i + j - 1] = a[i] * b[j] + carry + prod[i + j - 1];
            carry = prod[i + j - 1] / 10;
            prod[i + j - 1] %= 10;
        }
        prod[bLen + i] = carry;
    }
    if (carry <= 0)
    {
        return aLen + bLen - 1;
    }
    return aLen + bLen;
}

HPNum *mul(HPNum *a, HPNum *b)
{
    if (a == nullptr || b == nullptr)
        return nullptr;
    auto ret = new HPNum(a->len + b->len);
    ret->len = mul(a->num, a->len, b->num, b->len, ret->num);
    return ret;
}

HPNum *get(unsigned short *n, int s, int e)
{
    if (e < s)
        return One;
    int len = e - s + 1;
    auto ret = new HPNum(len);
    for (int i = 1; i <= len; ++i)
    {
        ret->num[len - i + 1] = n[s + i - 1];
    }
    return ret;
}

HPNum *nmax(HPNum *a, HPNum *b)
{
    if (a == nullptr && b == nullptr)
        return nullptr;
    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;
    if (a->len > b->len)
        return a;
    else if (a->len < b->len)
        return b;
    for (int i = a->len; i >= 1; --i)
    {
        if (a->num[i] > b->num[i])
            return a;
        else if (a->num[i] < b->num[i])
            return b;
    }
    return a;
}

HPNum *work(unsigned short *num, int n, int k)
{
    if (dp[n][k] != nullptr)
        return dp[n][k];
    if (n == 0)
    {
        return nullptr;
    }
    if (k <= 1)
    {
        return get(num, 1, n);
    }
    HPNum *max = nullptr;
    for (int i = k - 1; i < n; ++i)
    {
        auto p = mul(work(num, i, k - 1), get(num, i + 1, n));
        max = nmax(max, p);
    }
    return dp[n][k] = max;
}

int main()
{
    cin >> N >> K;
    string s;
    cin >> s;
    N = s.length();
    unsigned short *n = new unsigned short[N + 1];
    for (int i = 0; i < N; ++i)
    {
        n[i + 1] = s[i] - '0';
    }
    One = new HPNum(1);
    One->num[1] = 1;
    dp = new HPNum **[N + 1];
    for (int i = 0; i <= N; ++i)
    {
        dp[i] = new HPNum*[K + 2];
        for (int j = 0; j <= K + 1; ++j)
        {
            dp[i][j] = nullptr;
        }
    }
    
    auto ans = work(n, N, K + 1);
    if (ans != nullptr)
    {
        ans->print();
    }

    return 0;
}