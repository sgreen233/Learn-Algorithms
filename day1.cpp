#include<iostream>
#include<unordered_map>
// 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

// 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。

 

// 示例 1:

// 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
// 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
// 示例 2:

// 输入: strs = [""]
// 输出: [[""]]
// 示例 3:

// 输入: strs = ["a"]
// 输出: [["a"]]
//首先效率不如直接排序的高，然后就是，map会自动声明一个vector我直接赋值就像
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if(strs.size() == 0)return res;
        unordered_map<string, vector<string>> mp;
        for(int i = 0;i<strs.size();i++){
            int words[26] = {0};
            for(int j = 0;j<strs[i].length();i++){
                words[strs[i][j] - 'a']++;
            }
            string countstr = "";
            for(int j = 0;j<26;j++){
                countstr += words[j] + '0';
            }
            if(!mp.count(countstr)){
                vector<string> ct;
                ct.push_back(strs[i])
                mp[countstr] = ct;
            }
            else mp[countstr].push_back(strs[i]);
        }
        for(auto row : mp){
            res.push_back(row.second);
        }
        return res;
    }
};

//排序版本
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if(strs.size() == 0)return res;
        unordered_map<string, vector<string>> mp;
        for(int i = 0;i<strs.size();i++){
            int words[26] = {0};
            string tmp = strs[i];
            sort(tmp.begin(),tmp.end());
            mp[tmp].push_back(strs[i]);
        }
        for(auto row : mp){
            res.push_back(row.second);
        }
        return res;
    }
};

// 编写一个算法来判断一个数 n 是不是快乐数。

// 「快乐数」 定义为：

// 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
// 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
// 如果这个过程 结果为 1，那么这个数就是快乐数。
// 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

 

// 示例 1：

// 输入：n = 19
// 输出：true
// 解释：
// 12 + 92 = 82
// 82 + 22 = 68
// 62 + 82 = 100
// 12 + 02 + 02 = 1
// 示例 2：

// 输入：n = 2
// 输出：false
 class Solution {
public:
    int getSum(int n){
        int sum = 0;
        while(n > 0){
            sum = pow(n%10, 2);
            n = n/10;
        }
        return sum;
    }
    bool isHappy(int n) {
        //有可能无限递归，不知道是多少了
        unordered_map <int, int> mp;
        while(1){
            int tmp = n;
            int sum = getSum(n);
            if(sum == 1)return true;
            if(mp.count(n) && mp[n] == sum)return false;
            else mp[n] = sum;
            n = sum;
        }
        return false;
    }
};




