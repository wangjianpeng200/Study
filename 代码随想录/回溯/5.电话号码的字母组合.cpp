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

//public:
//    vector<string> result;
//    string s;
//    void backtracking(const string& digits, int index) {
//        if (index == digits.size()) {
//            result.push_back(s);
//            return;
//        }
//        int digit = digits[index] - '0';        // 将index指向的数字转为int
//        string letters = letterMap[digit];      // 取数字对应的字符集
//        for (int i = 0; i < letters.size(); i++) {
//            s.push_back(letters[i]);            // 处理
//            backtracking(digits, index + 1);    // 递归，注意index+1，一下层要处理下一个数字了
//            s.pop_back();                       // 回溯
//        }
//    }
//    vector<string> letterCombinations(string digits) {
//        s.clear();
//        result.clear();
//        if (digits.size() == 0) {
//            return result;
//        }
//        backtracking(digits, 0);
//        return result;
//    }
//};



public:
    vector<string> result;
    string s;
    void backtracking(const string& digits, int index) 
    {
        if (index >= digits.size())
        {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap(digit);
        for (int i = 0; i < letters.size(); i++)
        {
            s.push_back(letters[i]);
            backtracking(digits, i + 1);
            s.pop_back();
        }
        return;
    }
    vector<string> letterCombinations(string digits) 
    {
        s.clear();
        result.clear();
        if (digits.size() = 0)
        {
            return result;
        }
        backtracking(digits, 0);
        return digits;
    }
};