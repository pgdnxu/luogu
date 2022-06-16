#include <iostream>

using namespace std;

int N;
int *h;
int *a, *b;

void reverseH()
{
    for (int i = 0; i < N / 2; ++i)
    {
        int t = h[i];
        h[i] = h[N - i - 1];
        h[N - i - 1] = t;
    }
}

void work(int *d)
{
    for (int i = 0; i < N - 1; ++i)
        for (int k = i + 1; k < N; ++k)
            if (h[k] > h[i] && d[i] + 1 > d[k])
                d[k] = d[i] + 1;
}

int main()
{
    cin >> N;
    h = new int[N];
    for (int i = 0; i < N; ++i)
        cin >> h[i];
    a = new int[N];
    b = new int[N];
    for (int i = 0; i < N; ++i)
    {
        a[i] = 0;
        b[i] = 0;
    }

    work(a);
    reverseH();
    work(b);

    int max = -1;
    for (int i = 0; i < N; ++i)
        if (a[i] + b[N - i - 1] > max)
            max = a[i] + b[N - i - 1];
            
    cout << N - max - 1;
}
