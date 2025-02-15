#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <functional>
#include <climits>
#include <cstdlib>
#include <numeric>

using namespace std;

class Solution {
private:
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };//二维数组

public:
    vector<string>  result;
    string path;
    void backtracking(const string& digits, int index)
    {
        if(index==digits.size())
        {
            result.push_back(path);
            return;
        }
        int digit=digits[index]-'0'; //将字符转换为数字
        string letters=letterMap[digit];
        for(int i=0;i<letters.size();i++)
        {
            path.push_back(letters[i]);
            backtracking(digits,index+1);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) 