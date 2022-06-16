#include <iostream>
#include <vector>

using namespace std;

int n = 0;
long long *ns;
long long ***cache;
int **rootCache;

long long MaxSubTreeSum(int root, int l, int r)
{

    if (l < 0 || r >= n)
    {
        return 0;
    }

    if (root < l || root > r)
    {
        return 0;
    }

    if (cache[root][l][r] >= 0)
    {
        return cache[root][l][r];
    }

    int maxL = 1;
    for (int li = l; li < root; li++)
    {
        int v = MaxSubTreeSum(li, l, root - 1);
        if (v > maxL)
        {
            rootCache[l][root - 1] = li;
            maxL = v;
        }
    }
    

    int maxR = 1;
    for (int ri = root + 1; ri <= r; ri++)
    {
        int v = MaxSubTreeSum(ri, root + 1, r);
        if (v > maxR)
        {
            rootCache[root + 1][r] = ri;
            maxR = v;
        }
    }
    

    int ret = maxL * maxR + ns[root];
    cache[root][l][r] = ret;
    return ret;
}

void Preorder(int l, int r)
{
    if (l < 0 || r >= n)
    {
        return;
    }
    if (l > r)
    {
        return;
    }

    int curr = rootCache[l][r];
    cout << curr + 1 << " ";
    if (curr < 0)
    {
        return;
    }


    Preorder(l, curr - 1);
    Preorder(curr + 1, r);
}

int main()
{
    cin >> n;
    ns = new long long[n];
    for (int i = 0; i < n; i++)
    {
        cin >> ns[i];
    }

    cache = new long long **[n];
    for (int i = 0; i < n; i++)
    {
        cache[i] = new long long *[n];
        for (int j = 0; j < n; j++)
        {
            cache[i][j] = new long long[n];
        }
    }

    rootCache = new int *[n];
    for (int i = 0; i < n; i++)
    {
        rootCache[i] = new int[n];
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (k == i)
            {
                rootCache[k][i] = k;
            }
            else
            {
                rootCache[k][i] = -1;
            }
            
            for (int j = 0; j < n; j++)
            {
                if (k == i && k == j)
                {
                    cache[k][i][j] = ns[k];
                }
                else
                {
                    cache[k][i][j] = -1;
                }
            }
        }
    }

    long long max = 0;
    for (int i = 0; i < n; i++)
    {
        long long v = MaxSubTreeSum(i, 0, n - 1);
        if (v > max)
        {
            rootCache[0][n - 1] = i;
            max = v;
        }
    }
    
    cout << max << endl;

    Preorder(0, n - 1);

    return 0;
}
