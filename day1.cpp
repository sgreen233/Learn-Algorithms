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


//给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/' 开头），请你将其转化为更加简洁的规范路径。

// 在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。任意多个连续的斜杠（即，'//'）都被视为单个斜杠 '/' 。 对于此问题，任何其他格式的点（例如，'...'）均被视为文件/目录名称。

// 请注意，返回的 规范路径 必须遵循下述格式：

// 始终以斜杠 '/' 开头。
// 两个目录名之间必须只有一个斜杠 '/' 。
// 最后一个目录名（如果存在）不能 以 '/' 结尾。
// 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
// 返回简化后得到的 规范路径 。
// 示例 1：

// 输入：path = "/home/"
// 输出："/home"
// 解释：注意，最后一个目录名后面没有斜杠。 
// 示例 2：

// 输入：path = "/../"
// 输出："/"
// 解释：从根目录向上一级是不可行的，因为根目录是你可以到达的最高级。
// 示例 3：

// 输入：path = "/home//foo/"
// 输出："/home/foo"
// 解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。
// 示例 4：

// 输入：path = "/a/./b/../../c/"
// 输出："/c"

class Solution {
public:
    string simplifyPath(string path) {
        //path = "/home/"
        //1. 初始目录返回/../
        //2. 用一个路径表示当前有的目录层级
        stack<string> flod;
        string tmp = "";
        for(int i = 0;i<path.length();i++){
            if(path[i] == '/'){
                //做判断
                if(tmp == '..' && !flod.empty()){
                    flod.pop();
                }else if(tmp != "." && tmp != ""){
                    flod.push(tmp);
                }
                tmp = "";
            }else{
                tmp += path[i];
            }
        }
        //最后一个可能没有处理，需要加上
        if(tmp != ""&&tmp!="."){
            if(tmp == ".." && !flod.empty())flod.pop();
            else{flod.push(tmp);}
        }
        string res = "";
        if(flod.empty())return "/";
        while(!flod.empty()){
            //弹出
            res = "/" +flod.top() + res;
            flod.pop();
        }
        return res;
    }
};






