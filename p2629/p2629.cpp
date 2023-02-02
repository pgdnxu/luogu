#include <bits/stdc++.h>

using namespace std;

int m[2000002], a[2000002];

int main() {
    int n, dn;
    deque<int> dq;
    scanf("%d", &n);
    dn = n * 2;
    for (int i = 0; i < n; ++i) {
        scanf("%d", m + i);
        m[n + i] = m[i];
    }
    a[0] = m[0];
    for (int i = 1; i < dn; ++i) {
        a[i] = a[i - 1] + m[i];
    }
    int ans = 0;
    for (int i = 0; i < dn; ++i) {
        while(!dq.empty() && a[i] <= a[dq.back()]) {
            dq.pop_back();
        }
        while(!dq.empty() && i - dq.front() >= n) {
            dq.pop_front();
        }
        dq.push_back(i);
        if (i >= n) {
            if (a[dq.front()] - a[i - n] >= 0) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}