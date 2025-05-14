#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int count;
int n,m;
int div[4][2]={0,1,1,0,-1,0,0,-1};

void DFS(vector<vector<int>>& grid,vector<vector<bool>>& visit,int x,int y,int mark)
{
    if(visit[x][y] || grid[x][y]==0)
    {
        return;
    }
    visit[x][y]=true;
    grid[x][y]=mark;
    count++;
    for(int i=0;i<4;i++)
    {
        int nextx=x+div[i][0];
        int nexty=y+div[i][1];
        if(nextx < 0 || nextx >= n ||nexty<0 || nexty >= m) continue;
        DFS(grid,visit,nextx,nexty,mark);
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

    vector<vector<bool>> visit(n,vector<bool>(m,false));
    unordered_map<int,int> map
    int mark = 2;          // 记录每个岛屿的编号
    bool isAllGrid = true; // 标记是否整个地图都是陆地

     for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 0)
                isAllGrid = false;
            if (!visited[i][j] && grid[i][j] == 1)
            {
                count = 0;
                dfs(grid, visited, i, j, mark); // 将与其链接的陆地都标记上 true
                gridNum[mark] = count;      // 记录每一个岛屿的面积
                mark++;                         // 记录下一个岛屿编号
            }
        }
    }

    if (isAllGrid)
    {
        cout << n * m << endl; // 如果都是陆地，返回全面积
        return 0;              // 结束程序
    }

    int result = 0;                 // 记录最后结果
    unordered_set<int> visitedGrid; // 标记访问过的岛屿

     for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            count = 1;           // 记录连接之后的岛屿数量
            visitedGrid.clear(); // 每次使用时，清空
            if (grid[i][j] == 0)
            {
                for (int k = 0; k < 4; k++)
                {
                    int neari = i + dir[k][1]; // 计算相邻坐标
                    int nearj = j + dir[k][0];
                    if (neari < 0 || neari >= n || nearj < 0 || nearj >= m)
                        continue;
                    if (visitedGrid.count(grid[neari][nearj]))
                        continue; // 添加过的岛屿不要重复添加
                    // 把相邻四面的岛屿数量加起来
                    count += gridNum[grid[neari][nearj]];  //查找编号对应的
                    visitedGrid.insert(grid[neari][nearj]); // 标记该岛屿已经添加过
                }
            }
            result = max(result, count);
        }
    }
    cout << result << endl;

    
}