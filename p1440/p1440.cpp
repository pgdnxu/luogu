#include <bits/stdc++.h>

using namespace std;
int a[2000010];
int main() {
    deque<int> dq;
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            printf("0\n");
            continue;
        }
        while (!dq.empty() && a[i - 1] <= a[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i - 1);
        if (i >= m) {
            while (!dq.empty() && i - 1 - dq.front() >= m) {
                dq.pop_front();
            }
        }
        printf("%d\n", a[dq.front()]);
    }
    return 0;
}
