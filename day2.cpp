//https://leetcode.cn/problems/candy/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> left(ratings.size());
        for (int i = 0; i < ratings.size(); i++) {
            if (i > 0 && ratings[i] > ratings[i - 1])
                left[i] = left[i - 1] + 1;
            else left[i] = 1;
        }
        int right = 0;
        int ret = 0;
        for(int i = ratings.size() - 1;i>=0;i--){
            if(i<ratings.size() - 1&& ratings[i] > ratings[i + 1]){
                right++;
            }
            else{
                right = 1;
            }
            ret += max(left[i], right);
        }
        return ret;
    }
};

//https://leetcode.cn/problems/trapping-rain-water/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> left(n, 0);
        for (int i = 0; i < n; i++) {
            if (i > 0 && height[i] < left[i - 1]) {
                left[i] = left[i - 1];
            } else {
                left[i] = height[i];
            }
        }
        int right = 0, ret = 0;
        for (int i = n - 1; i >= 0; i--) {
            if(height[i] > right)right = height[i];
            ret += min(left[i], right) - height[i];
        }
        return ret;
    }
};

//从2开始更新
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        //dp[i][0] =  dp[i - 1][0],dp[i - 1][1] + prices[i]
        //dp[i][1] = dp[i - 1][1],dp[i - 1][0] - prices[i] ==>   max
        dp[1][1] = -prices[0];
        for(int i = 1;i<=n;i++){
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }
};

//https://leetcode.cn/problems/copy-list-with-random-pointer/submissions/548806531/?envType=study-plan-v2&envId=top-interview-150

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        //记录所有被复制的节点，一遍查找
        unordered_map<Node*, Node*> oldTonew;
        Node* heads,* tails;
        heads = new Node(-1);
        heads->next = NULL;
        tails = heads;
        while(head != NULL){
            if(!oldTonew.count(head)){
                tails->next = new Node(head->val);
                tails = tails->next;
                oldTonew[head] = tails;
            }else{
                tails->next =  oldTonew[head];
                tails = tails->next;
            }
            //要做复制
            if(head->random == NULL)tails->random = NULL;
            else if(!oldTonew.count(head->random)){
                Node* tmp = new Node(head->random->val);
                tails->random = tmp;
                oldTonew[head->random] = tmp;
            }else{
                tails->random = oldTonew[head->random];
            }
            head = head->next;
        }
        // while(heads!= NULL){
        //     cout<<heads->val<<"  ";
        //     if(heads->random !=NULL)cout<<heads->random->val;
        //     else cout<<"NULL";
        //     cout<<endl;
        //     heads = heads->next;
        // }
        return heads->next;
    }
};