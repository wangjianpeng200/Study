#include <iostream>
#include <vector>
using namespace std;

// 思路：从第一组边界和第二组边界逆势而上，将遍历过的路径都打上标记。如果该xy能被两组就遍历到，说明第一组
// 第二组他都能到达

int n, m;
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};

void dfs(vector<vector<bool>> &visited, vector<vector<int>> &grid, int x,int y)
{
    if (visited[x][y])
        return;
    visited[x][y] = true;

    for (int i = 0; i < 4; i++)
    {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m)
            continue;
        if (grid[x][y] < grid[nextx][nexty])  //逆流而上的条件
        {
            dfs(visited, grid, nextx, nexty);
        }
    }
}

int main()
{
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    vector<vector<bool>> firstBorder(n, vector<bool>(m, false));
    vector<vector<bool>> secondBorder(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
    {
        dfs(firstBorder, grid, i, 0);
        dfs(secondBorder, grid, i, m - 1);
    }

    for (int j = 0; j < m; j++)
    {
        dfs(firstBorder, grid, 0, j);      // 遍历最上行，接触第一组边界
        dfs(secondBorder, grid, n - 1, j); // 遍历最下行，接触第二组边界
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // 如果这个节点，从第一组边界和第二组边界出发都遍历过，就是结果
            if (firstBorder[i][j] && secondBorder[i][j])
                cout << i << " " << j << endl;
        }
    }
}
