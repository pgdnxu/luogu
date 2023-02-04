#include <bits/stdc++.h>
using namespace std;
int a[10001];
int main() {
    priority_queue<int, vector<int>, greater<int>> pq;
    int n, v, ans = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &v);
        pq.push(v);
    }
    while(pq.size() > 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        ans += a + b;
        pq.push(a + b);
    }
    printf("%d\n", ans);
}