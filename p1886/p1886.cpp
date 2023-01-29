#include <bits/stdc++.h>

using namespace std;
int a[1000000];

int main()
{
    deque<int> dq;
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++i) {
        while(!dq.empty() && a[i] <= a[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i + 1 >= k) {
            while(!dq.empty() && i - dq.front() >= k) {
                dq.pop_front();
            }
            printf("%d ", a[dq.front()]);
        }
    }
    printf("\n");
    dq.clear();
    for (int i = 0; i < n; ++i) {
        while(!dq.empty() && a[i] >= a[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i + 1 >= k) {
            while(!dq.empty() && i - dq.front() >= k) {
                dq.pop_front();
            }
            printf("%d ", a[dq.front()]);
        }
    }
    return 0;
}