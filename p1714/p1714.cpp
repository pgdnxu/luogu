#include <bits/stdc++.h>

using namespace std;

int p[500001], a[500001];

int main() {
    int n, m;
    deque<int> dq;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", p + i);
        a[i] = 0;
    }
    a[0] = p[0];
    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1] + p[i];
    }
    int ans = -1e8;
    for (int i = 0; i < n; ++i) {

        while(!dq.empty() && i - dq.front() > m) {
            dq.pop_front();
        }

        if (dq.empty()) {
            ans = max(ans, a[i]);
        } else {
            ans = max(ans, a[i] - a[dq.front()]);
        }

        while(!dq.empty() && a[i] <= a[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    printf("%d\n", ans);
    return 0;
}