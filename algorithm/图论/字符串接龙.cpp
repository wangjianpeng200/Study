#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

int mian()
{
    string beginStr, endStr, str;
    int n;
    cin >> n;
    unordered_set<string> strSet; // 存储字典中的单词
    cin >> beginStr >> endStr;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        strSet.insert(str);
    }

    unordered_map<string, int> visitMap; //<记录的字符串，路径长度>

    queue<string> que;
    que.push(beginStr); // 从beginwords开始搜索
    while (!que.empty())
    {
        string word = que.front();
        que.pop();
        int path = visitMap[word];            // 获取到当前单词的路径长度，如果不存在visitMap[word]则 自动创建visitMap[word] = 0;
        for (int i = 0; i < word.size(); i++) // 遍历单词的每一个字符
        {
            string newWord = word;            // 复制当前单词
            for (char c = 'a'; c <= 'z'; c++) // 将当前单词的每一个字符都替换成a-z的字符
            {
                if (newWord == endStr)
                {                             // 发现替换字母后，字符串与终点字符串相同
                    cout << path + 1 << endl; // 找到了路径
                    return 0;
                }
            }
            if (strSet.find(newWord) != strSet.end() && visitMap.find(newWord) == visitMap.end())  //如果新单词在字典中，并且没有被访问过
            // 注意：这里不能用visitMap[newWord] == 0来判断，因为visitMap[newWord]可能为0，但是没有被访问过
            {
                visitMap.insert(pair<string, int>(newWord, path + 1)); // 插入新单词和路径长度
                que.push(newWord);// 将新单词加入队列
            }
        }
    }
}