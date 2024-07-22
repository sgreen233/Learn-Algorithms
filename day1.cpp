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



// 给定一个  无重复元素 的 有序 整数数组 nums 。

// 返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。

// 列表中的每个区间范围 [a,b] 应该按如下格式输出：

// "a->b" ，如果 a != b
// "a" ，如果 a == b
// 示例 1：

// 输入：nums = [0,1,2,4,5,7]
// 输出：["0->2","4->5","7"]
// 解释：区间范围是：
// [0,2] --> "0->2"
// [4,5] --> "4->5"
// [7,7] --> "7"
// 示例 2：

// 输入：nums = [0,2,3,4,6,8,9]
// 输出：["0","2->4","6","8->9"]
// 解释：区间范围是：
// [0,0] --> "0"
// [2,4] --> "2->4"
// [6,6] --> "6"
// [8,9] --> "8->9"
 

// 提示：

// 0 <= nums.length <= 20
// -231 <= nums[i] <= 231 - 1
// nums 中的所有值都 互不相同
// nums 按升序排列
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        vector<string> res;
        int left = 0, right = 1;
        while(left < n && right < n){
            if(nums[right] == nums[right - 1] + 1 && right!= n - 1)right++;
            else{
                if(left == right - 1)strig tmp = to_string(nums[left]);
                else string tmp += to_string(nums[left])+"->"+to_string(nums[right - 1]);
                res.push_back(tmp);
                left = right;
                right = left + 1;
            }
        }
        return res;
    }
};

//以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
//请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

 

// 示例 1：

// 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
// 输出：[[1,6],[8,10],[15,18]]
// 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
// 示例 2：

// 输入：intervals = [[1,4],[4,5]]
// 输出：[[1,5]]
// 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 

// 提示：

// 1 <= intervals.length <= 104
// intervals[i].length == 2
// 0 <= starti <= endi <= 104
class Solution {
public:
    bool vectorSort(vector<int> a, vector<int> b){
        if(a.size() > 0 && b.size() > 0 && a[0] > b[0])return true;
        return false;
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //排序
        //直接左端点排序，然后用merge数组存储最终结果
        sort(intervals.begin(), intervals.end(), vectorSort);
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for(int i = 0;i<intervals.size();i++){
            if(intervals[i][0] > res[res.size() - 1][1])res.push_back(intervals[i]);
            else{
                res[res.size() -  1][1] = max(intervals[i][1], res[res.size() - 1][1]);
            }
        }
        return res;
    }
};

// 给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，其中 intervals[i] = [starti, endi] 表示第 i 
//个区间的开始和结束，并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 
//表示另一个区间的开始和结束。
// 在 intervals 中插入区间 newInterval，使得 intervals 依然按照 starti 升序排列，且区间之间不重叠
//（如果有必要的话，可以合并区间）。

// 返回插入之后的 intervals。

// 注意 你不需要原地修改 intervals。你可以创建一个新数组然后返回它。

 

// 示例 1：

// 输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
// 输出：[[1,5],[6,9]]
// 示例 2：

// 输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
// 输出：[[1,2],[3,10],[12,16]]
// 解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
 

// 提示：

// 0 <= intervals.length <= 104
// intervals[i].length == 2
// 0 <= starti <= endi <= 105
// intervals 根据 starti 按 升序 排列
// newInterval.length == 2
// 0 <= start <= end <= 105

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        //合并方向：左/右
        //合并区间跨度：一个/多个
        vector<vector<int>> res;
        int L = newInterval[0],R = newInterval[1];
        for(int i = 0;i<intervals.size();i++){
            //在区间之间

            //在区间之前[1,2] 2 [3,5] 
            
        }
    }
};

