#include <bits/stdc++.h>

using namespace std;

int h[100001], a[100001];

int main() {
    int n;
    stack<int> s;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", h + i);
    }
    for (int i = n - 1; i >= 0; --i) {
        while(!s.empty() && h[s.top()] <= h[i]) {
            s.pop();
        }
        if (s.empty()) {
            a[i] = 0;
        } else {
            a[i] = s.top() + 1;
        }
        s.push(i);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", a[i]);
    }

    return 0;
}