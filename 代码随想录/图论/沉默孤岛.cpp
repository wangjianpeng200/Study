#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void bfs(vector<vector<int>> &grid, int x, int y)
{
    queue<pair<int, int>> que;
    que.push({x, y});
    grid[x][y] = 0; // 只要加入队列，立刻标记
    while (!que.empty())
    {
        pair<int, int> cur = que.front();
        que.pop();
        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++)
        {
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size())
                continue; // 越界了，直接跳过
            if (grid[nextx][nexty] == 1)
            {
                que.push({nextx, nexty});
                grid[nextx][nexty] = 0; // 只要加入队列立刻标记
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    // 从左侧边，和右侧边 向中间遍历
    for (int i = 0; i < n; i++)
    {
        if (grid[i][0] == 1)
            bfs(grid, i, 0);
        if (grid[i][m - 1] == 1)
            bfs(grid, i, m - 1);
    }
    // 从上边和下边 向中间遍历
    for (int j = 0; j < m; j++)
    {
        if (grid[0][j] == 1)
            bfs(grid, 0, j);
        if (grid[n - 1][j] == 1)
            bfs(grid, n - 1, j);
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
                count++;
        }
    }

    cout << count << endl;
}