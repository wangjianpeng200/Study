#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    //输入
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    int result = 0;

    // 遍历每个点
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            //如果该地是陆地
            if (grid[i][j] == 1)
            {
                // 遍历上下左右四个方向
                for (int k = 0; k < 4; k++)
                { 
                    int x = i + direction[k][0];
                    int y = j + direction[k][1]; // 计算周边坐标x,y
                    //周围的四个方块
                    if (x < 0                    // x在边界上
                        || x >= grid.size()      // x在边界上
                        || y < 0                 // y在边界上
                        || y >= grid[0].size()   // y在边界上
                        || grid[x][y] == 0)      //是水域
                    { // x,y位置是水域
                        result++;
                    }
                }
            }
        }
    }
    cout << result << endl;
}