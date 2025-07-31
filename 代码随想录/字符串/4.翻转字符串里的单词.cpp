#include <string>
#include <algorithm>
using namespace std;

// 思路
// 1.先去除多余的空格
// 2.将整个字符串反转、
// 3.再将每个单词反转

class Solution
{
public:
    void reverse(string &s, int start, int end)
    { // 翻转，区间写法：左闭右闭 []
        for (int i = start, j = end; i < j; i++, j--)
        {
            swap(s[i], s[j]);
        }
    }

    void removeExtraSpaces(string &s)
    { // 去除所有空格并在相邻单词之间添加空格, 快慢指针。
        int slow = 0;
        for (int i = 0; i < s.size(); ++i)
        { 
            if (s[i] != ' ')
            { 
                //处理在第一次进入该循环时，其他情况下，每进入一次就说明遇到了一次空格需要手动添加一次。
                if (slow != 0)
                    s[slow++] = ' '; // 手动控制空格，给单词之间添加空格。slow != 0说明不是第一个单词，需要在单词前添加空格。
                while (i < s.size() && s[i] != ' ')
                { 
                    // 补上该单词，遇到空格说明单词结束。
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow); // slow的大小即为去除多余空格后的大小。
    }


    void removeExtraSpaces_test(string &s)
    {
        int slow=0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]!=' ')
            {
                if(slow!=0)
                {
                    s[slow++]=' ';  //先添加空格再++
                }
                while(i<s.size()&&s[i]!=' ')
                {
                    s[slow++]=s[i++];
                }
            }
        }
    }
   



    string reverseWords(string s)
    {
        removeExtraSpaces(s); // 去除多余空格，保证单词之间之只有一个空格，且字符串首尾没空格。
        reverse(s, 0, s.size() - 1);
        int start = 0; // removeExtraSpaces后保证第一个单词的开始下标一定是0。
        for (int i = 0; i <= s.size(); ++i)
        {
            if (i == s.size() || s[i] == ' ')
            {                             // 到达空格或者串尾，说明一个单词结束。进行翻转。
                reverse(s, start, i - 1); // 翻转，注意是左闭右闭 []的翻转。
                start = i + 1;            // 更新下一个单词的开始下标start
            }
        }
        return s;
    }
};