#include <bits/stdc++.h>
using namespace std;
int main() {
    priority_queue<int, vector<int>> a;
    priority_queue<int, vector<int>, greater<int>> b;

    int n, v;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &v);
        if (!a.empty() && v < a.top()) {
            a.push(v);
        } else if (!b.empty() && v > b.top()) {
            b.push(v);
        } else {
            a.push(v);
        }
        
        while(abs((int)(a.size() - b.size())) != 1) {
            if (a.size() > b.size()) {
                b.push(a.top());
                a.pop();
            } else {
                a.push(b.top());
                b.pop();
            }
            if (a.size() == b.size()) break;
        } 
        if (i % 2 == 1) {
            printf("%d\n", a.size() > b.size() ? a.top() : b.top());
        }
    }
    return 0;
}