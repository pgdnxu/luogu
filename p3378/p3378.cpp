#include <bits/stdc++.h>

using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> pq;
    int n, v, op = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &v);
            pq.push(v);
        } else if (op == 2) {
            printf("%d\n", pq.top());
        } else if (op == 3) {
            pq.pop();
        }
    }

    return 0;
}