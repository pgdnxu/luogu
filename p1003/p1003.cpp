#include <iostream>

using namespace std;

struct Area {
    int a, b, g, k;
};

int n;
Area *areas;
int x, y;

int main()
{
    cin >> n;
    areas = new Area[n];
    for (int i = 0; i < n; ++i)
    {
        auto &t = areas[i];
        cin >> t.a >> t.b >> t.g >> t.k;
    }
    cin >> x >> y;

    int find = -1;
    for (int i = n - 1; i >= 0; --i)
    {
        auto &t = areas[i];
        if (x >= t.a && x <= t.a + t.g && y >= t.b && y <= t.b + t.k)
        {
            find = i + 1;
            break;
        }
    }
    cout << find;
    return 0;
}