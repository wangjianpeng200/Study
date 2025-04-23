#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
int n, m;
int count;

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int mark) {
    if (visited[x][y] || grid[x][y] == 0) return; // 终止条件：访问过的节点 或者 遇到海水
    visited[x][y] = true; // 标记访问过
    grid[x][y] = mark; // 给陆地标记新标签
    count++;
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;  // 越界了，直接跳过
        dfs(grid, visited, nextx, nexty, mark);
    }
}

int main() {
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false)); // 标记访问过的点
    unordered_map<int ,int> gridNum;
    int mark = 2; // 记录每个岛屿的编号
    bool isAllGrid = true; // 标记是否整个地图都是陆地
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) isAllGrid = false;
            if (!visited[i][j] && grid[i][j] == 1) {
                count = 0;
                dfs(grid, visited, i, j, mark); // 将与其链接的陆地都标记上 true
                gridNum[mark] = count; // 记录每一个岛屿的面积
                mark++; // 记录下一个岛屿编号
            }
        }
    }
    if (isAllGrid) {
        cout << n * m << endl; // 如果都是陆地，返回全面积
        return 0; // 结束程序
    }

    // 以下逻辑是根据添加陆地的位置，计算周边岛屿面积之和
    int result = 0; // 记录最后结果
    unordered_set<int> visitedGrid; // 标记访问过的岛屿
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            count = 1; // 记录连接之后的岛屿数量
            visitedGrid.clear(); // 每次使用时，清空
            if (grid[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    int neari = i + dir[k][1]; // 计算相邻坐标
                    int nearj = j + dir[k][0];
                    if (neari < 0 || neari >= n || nearj < 0 || nearj >= m) continue;
                    if (visitedGrid.count(grid[neari][nearj])) continue; // 添加过的岛屿不要重复添加
                    // 把相邻四面的岛屿数量加起来
                    count += gridNum[grid[neari][nearj]];
                    visitedGrid.insert(grid[neari][nearj]); // 标记该岛屿已经添加过
                }
            }
            result = max(result, count);
        }
    }
    cout << result << endl;

}


void DFS(int i,int j ,vector<vector<int>>& grid, vector<vector<bool>>& visited, int& count) {
    if(visited[i][j] || grid[i][j]!=0) return; 
    visited[i][j] = true; // 标记访问过
    count++;
    for (int k = 0; k < 4; k++) {
        int nextx = i + dir[k][0];
        int nexty = j + dir[k][1]; 
    }
    if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;  // 越界了，直接跳过
    DFS(nextx,nexty,grid,visited,count);
}

void BFS(int i,int j,vector<vector<int>>& grid, vector<vector<bool>>& visited, int& count) {
    queue<pair<int,int>> q;
    que.push({i,j});
    visited[i][j] = true; // 标记访问过
    count++;
    while (!que.empty())
    {
        pair<int,int> cur = que.front();
        que.pop();
        int curx = cur.first;
        int cury = cur.second;
        for (int k = 0; k < 4; k++) {
            int nextx = curx + dir[k][0];
            int nexty = cury + dir[k][1];
            if(nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;  // 越界了，直接跳过  }
            if(visited[nextx][nexty] || grid[nextx][nexty]!=0) continue;  // 越界了，直接跳过  }
            que.push({nextx,nexty});
            visited[nextx][nexty] = true; // 标记访问过
            count++;
        }
    } 
}


int main() 
{
    cin>>n>>m;
    vector<vector<int>> grid(n,vector<int>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin>>grid[i][j];
        }
    }
    vector<vector<bool>> visited(n,vector<bool>(m,false)); // 标记访问过的点
    unordered_map<int,int> gridNum;
    int mark = 2; // 记录每个岛屿的编号
    bool isAllGrid = true; // 标记是否整个地图都是陆地
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(grid[i][j]==0) isAllGrid = false;
            if(!visited[i][j] && grid[i][j]==1) {
                count = 0;
                DFS(i,j,grid,visited,count); // 将与其链接的陆地都标记上 true
                gridNum[mark] = count; // 记录每一个岛屿的面积
                mark++; // 记录下一个岛屿编号
            }
        }
    }
    if(isAllGrid) 
    {
        cout<<n*m<<endl; // 如果都是陆地，返回全面积 
        return 0; // 结束程序
    } 


    int result = 0; // 记录最后结果
    for(int i = 0; i < n; i++) {
       for(int j = 0; j < m; j++) {
           count = 1; // 记录连接之后的岛屿数量
           if(grid[i][j]==0) {
               for(int k = 0; k < 4; k++) {
                   int neari = i + dir[k][1]; // 计算相邻坐标
                   int nearj = j + dir[k][0];
                   if(neari<0 || neari>=n || nearj<0 || nearj>=m) continue;
                   if(visitedGrid.count(grid[neari][nearj])) continue; // 添加过的岛屿不要重复添加
                   // 把相邻四面的岛屿数量加起来
                   count += gridNum[grid[neari][nearj]];
                   visitedGrid.insert(grid[neari][nearj]); // 标记该岛屿已经添加过
               } 
           }
       }
    }
    
}