#include <iostream>

using namespace std;

int N;
int *A;

int main()
{
    cin >> N;
    A = new int[N];
    int sum = 0;
    int avg = 0;
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
        sum += A[i];
    }
    avg = sum / N;
    int time = 0;
    for (int i = 0; i < N - 1; ++i)
    {
        if (A[i] != avg)
        {
            A[i + 1] += A[i] - avg;
            A[i] = avg;
            time += 1;
        }
    }
    cout << time;
}
