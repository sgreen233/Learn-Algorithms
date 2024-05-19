# Learn-Algorithms
# 数组
## [轮转数组](https://leetcode.cn/problems/rotate-array/?envType=study-plan-v2&envId=top-interview-150)
**注意点：如果轮转长度超过数组长度，是取余而不是直接等于数组长度，这一点需要注意。**
方法二环状替换思路：
1. 替换思路：将temp和当前值进行替换，放的位置是 (0+k) mod n(0+k)
2. 循环结束条件：按照环形走，一次遍历完成后，可能没有遍历完，必须要遍历n，k的最大公约数次，才行，全部遍历过。

```cpp
int cnt = gcd(nums.size(), k);
        // cout<<"cnt: "<<cnt<<endl;
        for (int start = 0; start < cnt; ++start) {  //遍历次数
            int current = start;  //一次遍历的当前位置
            int prev = nums[start]; //一次遍历（可能是数组的多圈，但是不是全部结果的多圈）
            do {
                int next = (current + k) % n;
                swap(nums[next], prev);
                current = next;
                cout<<"start: "<<start<<" current: "<<current<<endl;
            } while (start != current);
        } 
```
方法三：reverse方法翻转，只需要会用reverse即可， 翻转思路还是比较简单的。


## [跳跃游戏](https://leetcode.cn/problems/jump-game/?envType=study-plan-v2&envId=top-interview-150)
在递归中，不要使用递归用的return 变量，这样会很乱，不如设置全局变量，然后退出标志是需要的，并需要一定的剪枝，这样最终一定是可以过的，只要好好的修改。

还有一种解法，就是很简单的思路转换（可能是最难的思路转换）
挨个跳，如果当前k值不满足我走到下一步，那么return false
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};
```
## [除自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/?envType=study-plan-v2&envId=top-interview-150)

有回头路的遍历方式，需要当前值和除了他之外的所有值，因此这种问题就不能用股票买卖问题来解决，需要使用L和R数组保存左边和右边的值，这样的话才能得到需要的值。

L和R数组，是相对反向的
![数组描述](https://img-blog.csdnimg.cn/direct/318edf981c274e0593199846eb399653.jpeg)
最后在遍历一次原数组，使用L[i]*R[i]，得到最终值。注意-1表示的是初始化为1，但是在原数组中下标索引为-1，表示前一个初始化用的元素。
## [股票买卖问题](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150)
不走回头路的一种遍历方式，可以保存当前最小值，并且循环一次，得到最后的值，很巧妙的做法
[股票买卖问题系列写法](https://leetcode.cn/circle/discuss/qiAgHn/)
对于股票买卖主要使用动态规划的写法，可以将交易次数，持有股票，当前i天作为标志，最终输出结果即可。要保证最终可以找得到这个结果。

 ## [加油站](https://leetcode.cn/problems/gas-station/description/?envType=study-plan-v2&envId=top-interview-150)
循环路线问题，找出可以满足环路的点，原本写的代码超时（模拟），然后照着题解写的代码，样例2一直过不了，这种思路问题还是没有很好的去写完成。
```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        //letf = gas - cost;
        int n = gas.size();
        //找letf最大的，然后遍历得到值
        //寻找起点
        //按环路走一遍
        int leftgas = 0, start = 0;
        while(start < n){
            int current = start;
            int cnt = 0;
            leftgas = gas[start];
            int cango = 1;
            do{
                cout<<current<<" ";
                int next = (current + cnt)%n;
                if(leftgas >= cost[current]){
                    leftgas += gas[next] - cost[current];
                    cnt++;
                }else {
                    cango = 0;
                    start = current + cnt + 1;
                    break;
                }
            }while(cnt < n);
            cout<<"寻找结束"<<endl;
            if(cango == 1)return start;    
        }
        return -1;
    }
};
```

两种区别：
1. 记录当前current和next，这时，可以使用leftgas来记录差值。
2. 当使用cnt作为步进，此时相当于是单指针模式，忌讳使用中间值的模式，因为中间值，无法访问到上一次的值，此时程序就不对了。可以使用一个累计值来记录，这样就包含上一次的了，就不会导致访问错误了。


## [罗马数字转整数](https://leetcode.cn/problems/roman-to-integer/?envType=study-plan-v2&envId=top-interview-150)
匹配规则需要看前一位的数字，不用最多重判断，只需要设置前向位即可，这样会更加简单。但是这个思路我没有想出来，简单题。。。。。。

## [整数转罗马数字](https://leetcode.cn/problems/integer-to-roman/solutions/774611/zheng-shu-zhuan-luo-ma-shu-zi-by-leetcod-75rs/?envType=study-plan-v2&envId=top-interview-150)
方法1和方法2都可以看看，对我有很大的帮助，其中比较重要的就是一些算法思想。

```cpp
class Solution {
public:

以下是索引表的形式，也可以为每个数位建立表格，这样只需要判断每个数位即可。

    string intToRoman(int num) {
        //不必很麻烦的拆分数字，要考虑特殊的有哪些，然后去减即可
        //模拟法， 将值进行映射。
        unordered_map<int, string> mp;
        string res = "";
        mp[1000] = "M", mp[900] = "CM", mp[500] = "D";
        mp[400] = "CD", mp[100] = "C", mp[90] = "XC";
        mp[50] = "L", mp[40] = "XL", mp[10] = "X";
        mp[9] = "IX", mp[5] = "V", mp[4] = "IV", mp[1] = "I";
        int table[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4,1};
        for(int i = 0;i<13;i++){
            int cnt = num / table[i];
            while(cnt > 0){
                res += mp[table[i]];
                cnt --;
            }
            num %= table[i];
        }
        return res;
    }
};
```


## [分发糖果问题](https://leetcode.cn/problems/candy/submissions/525935435/?envType=study-plan-v2&envId=top-interview-150)
左右区间分别更新问题，主要还是一边是递增序列，一边是递减序列，需要分别去遍历才行。
也就是左区间和右区间的分别遍历。


## [接雨水问题](https://leetcode.cn/problems/trapping-rain-water/?envType=study-plan-v2&envId=top-interview-150)
双指针变体，主要看左右能不能搂住，所以用了左边遍历更新的边界，右边更新的边界，然后统计每个节点能存多少水，最后把整个输出出来。

## [最后一个单词的长度](https://leetcode.cn/problems/length-of-last-word/?envType=study-plan-v2&envId=top-interview-150)
问题，输入的最后可能先是非单词，我是直接统计的，导致错误。
没有好好的利用短路特性，导致


## [最长公共子串问题](https://leetcode.cn/problems/longest-common-prefix/?envType=study-plan-v2&envId=top-interview-150)
xxx边界问题，xxx！
# 贪心
## [跳跃游戏2](https://leetcode.cn/problems/jump-game-ii/solutions/230241/tiao-yue-you-xi-ii-by-leetcode-solution/?envType=study-plan-v2&envId=top-interview-150)
参数解释：
end表示通过当前步数，我到达的点是否遍历完了
maxpos表示当前遍历中选择到的下一个要跳的点
if(end == i)end = maxpos //预设了下一个点的坐标，也就是maxpos，这时直接跳到那个点，然后step++
这种类型的题目，类似于贪心，都有机会降到o(n)，但是考验做题能力不做考虑。
本题使用动态规划的话，需要o(n^2)，效率上不高，多复习，这种特殊做法。
```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int maxPos = 0, n = nums.size(), end = 0, step = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (maxPos >= i) {
                maxPos = max(maxPos, i + nums[i]);
                if (i == end) {
                    end = maxPos;
                    ++step;
                }
            }
        }
        return step;
    }
};
```

## [z字形变换](https://leetcode.cn/problems/zigzag-conversion/submissions/526122557/?envType=study-plan-v2&envId=top-interview-150)
超级可惜的一道题，我想出了2n - 2，但是没有想到接下来该怎么做。


# 哈希
## [O(1)时间插入删除和获取随机元素](https://leetcode.cn/problems/insert-delete-getrandom-o1/solutions/1411578/o1-shi-jian-cha-ru-shan-chu-he-huo-qu-su-rlz2/?envType=study-plan-v2&envId=top-interview-150)
在删除的时候需要注意，数组需要进行调换和删除最后一个元素，哈希表需要删除当前索引和更改最后一个元素的位置。
1. vector删除元素erase和pop_back
2. unordered_map删除元素erase


## [两数之和](https://leetcode.cn/problems/two-sum/?envType=study-plan-v2&envId=top-interview-150)

原先写法是两次遍历，先存到哈希表里面，然后再遍历，但是其实一次遍历就可以了，这个就是优化。
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
```



# 字符串
## [判断回文字符串](https://leetcode.cn/problems/valid-palindrome/?envType=study-plan-v2&envId=top-interview-150)
```cpp
if(isalnum(s[i]))cmp += tolower(s[i]); //判断是否为一个数字或者一个字母
```



## [找出字符串中第一个匹配的子串](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/?envType=study-plan-v2&envId=top-interview-150)
```cpp
//预处理next数组
        for(int i = 2, j = 0; i <= m; i++){
            while(j and p[i] != p[j + 1]) j = next[j]; //匹配不成功，修改为上一个j值的地址
            cout<<"next[i] "<<next[j]<<endl;
            if(p[i] == p[j + 1]) j++;  //匹配成功，两者相加
            next[i] = j;
            cout<<"next[i] "<<next[j]<<endl;
        }
        //匹配过程
        for(int i = 1, j = 0; i <= n; i++){
            while(j and s[i] != p[j + 1]) j = next[j];
            if(s[i] == p[j + 1]) j++;
            if(j == m) return i - m;
        }
```

# 双指针
## [判断子序列](https://leetcode.cn/problems/is-subsequence/?envType=study-plan-v2&envId=top-interview-150)
```cpp
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.length(), m = t.length();
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return i == n;
    }
};

```
双指针这种代码写不明白，自己多写写。 我加了好多的额外条件，其实最终的代码非常的简单。

## [两数之和II](https://leetcode.cn/problems/is-subsequence/?envType=study-plan-v2&envId=top-interview-150)
双指针，秒了

## [盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/description/?envType=study-plan-v2&envId=top-interview-150)
将边界作为两个指针，更新条件是哪个边界小，说明里面有更好的面积，退出条件是两者指针重合的时候。
使用一个中间变量记录每次的maxarea值即可。


# 链表
## [判断链表是否有环](https://leetcode.cn/problems/linked-list-cycle/solutions/175734/yi-wen-gao-ding-chang-jian-de-lian-biao-wen-ti-h-2/?envType=study-plan-v2&envId=top-interview-150)
面试问题总结
无法高效获取长度，无法根据偏移快速访问元素，是链表的两个劣势。然而面试的时候经常碰见诸如获取倒数第k个元素，获取中间位置的元素，判断链表是否存在环，判断环的长度等和长度与位置有关的问题。这些问题都可以通过灵活运用双指针来解决。

Tips：双指针并不是固定的公式，而是一种思维方式~

先来看"倒数第k个元素的问题"。设有两个指针 p 和 q，初始时均指向头结点。首先，先让 p 沿着 next 移动 k 次。此时，p 指向第 k+1个结点，q 指向头节点，两个指针的距离为 k 。然后，同时移动 p 和 q，直到 p 指向空，此时 q 即指向倒数第 k 个结点。可以参考下图来理解：

```cpp
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *p = head, *q = head; //初始化
        while(k--) {   //将 p指针移动 k 次
            p = p->next;
        }
        while(p != nullptr) {//同时移动，直到 p == nullptr
            p = p->next;
            q = q->next;
        }
        return q;
    }
};
```
获取中间元素的问题。设有两个指针 fast 和 slow，初始时指向头节点。每次移动时，fast向后走两次，slow向后走一次，直到 fast 无法向后走两次。这使得在每轮移动之后。fast 和 slow 的距离就会增加一。设链表有 n 个元素，那么最多移动 n/2 轮。当 n 为奇数时，slow 恰好指向中间结点，当 n 为 偶数时，slow 恰好指向中间两个结点的靠前一个(可以考虑下如何使其指向后一个结点呢？)。
下述代码实现了 n 为偶数时慢指针指向靠后结点。
```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *p = head, *q = head;
        while(q != nullptr && q->next != nullptr) {
            p = p->next;
            q = q->next->next;
        }
        return p;
    } 
};
```
是否存在环的问题。如果将尾结点的 next 指针指向其他任意一个结点，那么链表就存在了一个环。
上一部分中，总结快慢指针的特性 —— 每轮移动之后两者的距离会加一。下面会继续用该特性解决环的问题。
当一个链表有环时，快慢指针都会陷入环中进行无限次移动，然后变成了追及问题。想象一下在操场跑步的场景，只要一直跑下去，快的总会追上慢的。当两个指针都进入环后，每轮移动使得慢指针到快指针的距离增加一，同时快指针到慢指针的距离也减少一，只要一直移动下去，快指针总会追上慢指针。根据上述表述得出，如果一个链表存在环，那么快慢指针必然会相遇。实现代码如下：
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast != nullptr) {
            fast = fast->next;
            if(fast != nullptr) {
                fast = fast->next;
            }
            if(fast == slow) {
                return true;
            }
            slow = slow->next;
        }
        return nullptr;
    }
};
```
最后一个问题，如果存在环，如何判断环的长度呢？方法是，快慢指针相遇后继续移动，直到第二次相遇。两次相遇间的移动次数即为环的长度。

## [优先队列与链表](https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6?tpId=295&tqId=724&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj)
优先队列自定义优先级进行比较，使用结构体和vector，结构体重构()操作符。
```cpp
struct compare{
        bool operator()(ListNode* &a, ListNode* &b){
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // write code here
        //优先队列，将较小的出，然后每次加入一个元素，直到最后队列为空
        priority_queue<ListNode*, vector<ListNode*>, compare> q;
        for(auto & list : lists){
            while(list != nullptr){
                q.push(list);
                list = list->next;
            }
        }
        ListNode* head = nullptr, *tail = nullptr;
        while(!q.empty()){
            ListNode* tmp = q.top();
            q.pop();
            if(head == nullptr)head = tail = new ListNode(tmp->val);
            else {
                tail->next = new ListNode(tmp->val);
                cout<<"next:"<<tail->val<<endl;
                tail = tail->next;
            }
        }
        return head;
    }
```

# 树
## [二叉树的最大深度（带返回值的dfs）](https://leetcode.cn/problems/maximum-depth-of-binary-tree/?envType=study-plan-v2&envId=top-interview-150)
```cpp
 int maxDepth(TreeNode* root) {
        if(root == nullptr)return 0;
        int maxdp = max(maxDepth(root->left), maxDepth(root->right));
        return maxdp + 1;
    }
```
## [判断两个数是否相同](https://leetcode.cn/problems/same-tree/description/?envType=study-plan-v2&envId=top-interview-150)
```cpp
 bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == nullptr && q == nullptr)return true;
        else if(p == nullptr || q == nullptr)return false;
        else if(p->val != q->val)return false;
        else{
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
    }
```
主要是我把他想的太麻烦了，导致代码很奇怪，需要自己总结下。

## [翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/?envType=study-plan-v2&envId=top-interview-150)
```cpp
TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
```

# 矩阵
## [有效矩阵](https://leetcode.cn/problems/valid-sudoku/?envType=study-plan-v2&envId=top-interview-150)
这一题不难，主要还是细心，然后不要小气数组的使用。


## [矩阵旋转](https://leetcode.cn/problems/rotate-image/?envType=study-plan-v2&envId=top-interview-150)
首先这道题主要是坐标转换，所以，需要自己多进行推导，在推导的时候，请不要带入具体的值，进行画图。
公式：
temp = matrix[row][col]
            matrix[row][col] = matrix[n - col - 1][row]
            matrix[n - col - 1][row] = matrix[n - row - 1][n - col - 1]
            matrix[n - row - 1][n - col - 1] = matrix[col][n - row - 1]
            matrix[col][n - row - 1] = temp
