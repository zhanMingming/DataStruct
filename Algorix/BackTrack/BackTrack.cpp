






/*
https://leetcode-cn.com/problems/path-sum-ii/
给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
说明: 叶子节点是指没有子节点的节点。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        pathSumToTarget(ret, vector<int>(), root, 0, sum);
        return ret;
    }
    
    void pathSumToTarget(vector<vector<int>>& ret, vector<int> temp, TreeNode* root, int val, int target) {
        if (!root) {
            return;
        }
        temp.push_back(root->val);
        val += root->val;
        if (val == target && !root->left && !root->right) {
            ret.push_back(temp);
        }
        pathSumToTarget(ret, temp, root->left, val, target);
        pathSumToTarget(ret, temp, root->right, val, target);
    }
};


/*
https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node-ii/
 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) {
            return root;
        }
        deque<Node*>  q;
        q.push_back(root);
        
        while(!q.empty()) {
            int size = q.size();
            Node* temp = nullptr;
            for (int index = 0; index < size; ++index) {
                temp =  q.front();
                q.pop_front();
                temp->next = q.empty() ? nullptr : q.front();
                
                if (temp->left) {
                    q.push_back(temp->left);
                }
                if (temp->right) {
                    q.push_back(temp->right);
                }
            }
            temp->next = nullptr;
        }
        return root;
        
    }
};










/*

https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node
填充每个节点的下一个右侧节点指针
 */
// Definition for a Node.
/*
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

// 完美二叉树 可以用这个解法：
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) {
            return root;
        }
        Node* left = root->left;
        Node* right = root->right;
        while(left) {
            left->next = right;
            left = left->right;
            right = right->left;
        }
        connect(root->left);
        connect(root->right);
        return root;
        
    }
};


/*
https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
无重复字符的最长子串
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> c;
        int i = 0, j = 0;
        int len = 0;
        while (i < s.size() && j < s.size()) {

            if (c.find(s[i]) == c.end()) {
                c.insert(s[i++]);
                len = max(len, i - j);
            } else {
                c.erase(s[j++]);
            }
            
        }
        return len;
    }
};

/*
https://leetcode-cn.com/problems/palindrome-linked-list
回文链表
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *pre = head, *ppre = nullptr;
        while (fast != nullptr && fast->next != nullptr ) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
            // reverse list
            pre->next = ppre;
            ppre = pre;
        }
        if (fast != nullptr ) {
            slow = slow->next;
        }
        //cout << "slow:" << slow->val << std::endl;
        while (pre != nullptr && slow != nullptr) {
            if (pre->val != slow->val) {
                return false;
            }
            pre = pre->next;
            slow = slow->next;
        }
        return true;
        
        
    }
};

/*
实现前缀树
https://leetcode-cn.com/problems/implement-trie-prefix-tree
*/

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = nullptr;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.size() < 1) {
            return;
        }
        if (root == nullptr) {
            root = new Trie_node();
        }
        int index = 0;
        Trie_node* location = root;
        char c;
        while (location != nullptr && index < word.size()) {
            if (word[index] >= 'A' && word[index] <= 'Z') {
                c = word[index] - 'A';
            } else if (word[index] >= 'a' && word[index] <= 'z') {
                c = word[index] - 'a';
            } else {
                return;
            }
            if (location->num_char[c] == nullptr) {
                location->num_char[c] = new Trie_node();
            }
            location =  location->num_char[c];
            ++index;
        }
        location->data =  word;

    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        int index = 0;
        Trie_node* location = root;
        while(location != nullptr  &&  index < word.size()) {
            char c;
            if (word[index] >= 'A' && word[index] <= 'Z') {
                c = word[index] - 'A';
            } else if (word[index] >= 'a' && word[index] <= 'z') {
                c = word[index] - 'a';
            } else {
                return false;
            }
            location = location->num_char[c];
            ++index;
        }

        if (location == nullptr || index != word.size()) {
            return false;
        }
        return location->data == word;
        
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        int index = 0;
        Trie_node* location = root;
        while(location != nullptr  &&  index < word.size()) {
            char c;
            if (word[index] >= 'A' && word[index] <= 'Z') {
                c = word[index] - 'A';
            } else if (word[index] >= 'a' && word[index] <= 'z') {
                c = word[index] - 'a';
            } else {
                return false;
            }
            location = location->num_char[c];
            ++index;
        }
        return location != nullptr && index == word.size();
    }
    
    struct Trie_node {
        Trie_node()
        {
            for (int index = 0; index < 26; ++index) {
                num_char[index] = nullptr;
            }
        }
        string data;
        Trie_node *num_char[26];
    };

    Trie_node *root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
/*

岛屿数量
https://leetcode-cn.com/problems/number-of-islands

*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        
        int m = grid.size();
        if (m < 1) {
            return 0;
        }
        int n = grid[0].size();
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != '0') {
                    dfs(grid, i, j, m, n);
                    ++count;
                }
            }
        }
        return count;
    }
    
    void dfs(vector<vector<char>>& grid, int x, int y, int m, int n) {
        if (x < 0 || x >= m || y < 0 || y >=n || grid[x][y] == '0') {
            return;
        }
        grid[x][y] = '0';
        dfs(grid, x+1, y, m, n);
        dfs(grid, x-1, y, m, n);
        dfs(grid, x, y+1, m, n);
        dfs(grid, x, y-1, m, n);
        
    }
};


/*
https://leetcode-cn.com/problems/sliding-window-maximum
滑动窗口的最大值
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    
        if (nums.empty() || nums.size() < k) {
            return {};
        }
        deque<int> q;
        // 处理第一个窗口的最大值
        for (int index = 0 ; index < k; ++index) {
            while(!q.empty() && nums[index] > nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(index);
        }

        vector<int> ret;
        // 处理后续的窗口
        for (int index = k;  index < nums.size() ;  ++index) {
            ret.push_back(nums[q.front()]);
            
            while (!q.empty() && nums[index] > nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(index);
            // 处理超过窗口的下标
            while (!q.empty() &&  q.front() < index - k + 1) {
                q.pop_front();
            }
        }
        ret.push_back(nums[q.front()]);
        return ret;
    }
};


/*
三个数的最大乘积
https://leetcode-cn.com/problems/maximum-product-of-three-numbers
*/

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        if (nums.size() < 3) {
            return -1;
        }
        int min1 = INT_MAX, min2 = INT_MAX;
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        for (int index = 0; index < nums.size(); ++index) {
            if (nums[index] > max1) {
                max3 = max2;
                max2 = max1;
                max1 = nums[index];
            } else if (nums[index] > max2) {
                max3 = max2;
                max2 = nums[index];
            } else if (nums[index] > max3) {
                max3 = nums[index];

            }

            if (nums[index] < min1) {
                min2 = min1;
                min1 = nums[index];
            } else if (nums[index] < min2) {
                min2 = nums[index];
            }
        }

        return max(min1 * min2 * max1,  max1 * max2 * max3);
    }
};

/*
乘积的最大连续子序列
https://leetcode-cn.com/problems/maximum-product-subarray
 */

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() < 1) {
            return 0;
        }
        int ret = INT_MIN;
        int minVal = 1, maxVal = 1;
        for (int index = 0; index < nums.size(); ++index) {
            if(nums[index] < 0) {
                swap(minVal, maxVal);
            }
            maxVal = max(nums[index]* maxVal, nums[index]);
            minVal = min(nums[index]* minVal, nums[index]);

            ret = max(maxVal, ret);
        }

        return ret;
    }
};

/*
https://leetcode-cn.com/problems/rectangle-area/
矩阵相交的面积
*/

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        long area1 = abs(C - A) * abs(D - B);
        long area2 = abs(G - E) * abs(H - F);
        if (E >= C || A >= G || B >= H || F >= D) {
            return area1 + area2;
        }
        int lx = max(A, E);
        int ly = max(B, F);
        int rx = min(C, G);
        int ry = min(D, H);
        int common = abs(ry - ly) * abs(rx - lx);
        return area2 + area1 -  common;
    }
};

/*
https://leetcode-cn.com/problems/find-median-from-data-stream

数据流中的中位数

*/

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (((l.size() + r.size()) & 1) == 0) {
            
            if (!l.empty() && num < l.top()) {
                l.push(num);
                num = l.top();
                l.pop();
            }
            //cout << "r:" << num << endl;
            r.push(num);
        } else {
            if (!r.empty() && num > r.top()) {
                r.push(num);
                num = r.top();
                r.pop();
            }
            //cout << "l:" << num << endl;
            l.push(num);
        }
    }
    
    double findMedian() {
        if (((l.size() + r.size()) & 1) == 0) {
             return (l.top() + r.top()) / 2.0;
            
        } else {
            return (double)r.top();
        }
    }


    // 大顶堆
    priority_queue<int>   l;

    //小顶堆
    priority_queue<int, vector<int>,  std::greater<int>>   r;
};


/*

https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree
二叉树的最近公共祖先
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) {
            return nullptr;
        }
        map<TreeNode*, TreeNode*> parent;
        deque<TreeNode*>  que;
        parent[root] = nullptr;
        que.push_back(root);
        while( parent.find(p) == parent.end() || parent.find(q) == parent.end()) {
            
            TreeNode* root = que.front();
            que.pop_front();
            if (root->left) {
                parent[root->left] = root;
                que.push_back(root->left);
            }
            if (root->right) {
                parent[root->right] = root;
                que.push_back(root->right);
            }
        }
        set<TreeNode*>  s;
        while (p != nullptr) {
            s.insert(p);
            p = parent[p];
        }
        while (q != nullptr && s.find(q) == s.end()) {
            q = parent[q];
        }
        return q;
    }
};


/*
https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
买卖股票
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
    
        if (prices.size() < 1) {
            return 0;
        }
        int maxVal = 0, minVal = INT_MAX;
        for (int index = 0; index < prices.size(); ++index) {
            maxVal = max(maxVal, prices[index] - minVal);
            minVal = min(minVal, prices[index]);
        }
        return maxVal;
    }

};


/*

无序数组中快速找到中位数  类似topk的问题
 */
1. 快排
2. 堆排序



/*
在两个排序数组中找到第Ｋ小的数
*/

Todo: https://blog.csdn.net/peach90/article/details/45599843

/*
在数组中找到离value 最近的k 个数

 */

std::vector<int>  Knearest(const std::vector<int> &a, int value, int k) {
    if (k > a.size()) {
        return  std::vector<int>();
    }

    int pos = Position(a,  value);

    std::vector<int> ret;
    if (pos == 0) {

        ret.assign(a.begin(), a.begin() + k);
        return ret;
    }
    if (pos == a.size() - 1) {
        ret.assign(a.end() - k, a.end());
        return ret;
    }

    int posMid = abs(a[pos] - value) <= abs(a[pos+1] - value) ? pos  : pos + 1;

    int posBegin = posMid;
    int posEnd = posMid;

    int posPreBegin = posBegin - 1;
    int posNextEnd =  posEnd + 1;

    while (posEnd - posBegin <  k - 1) {
        if (abs(a[posPreBegin] - value) <= abs(a[posNextEnd] - value)) {
            posBegin = posPreBegin;
            if (posPreBegin > 0) {
                --posPreBegin;
            } else  {
                posEnd = posNextEnd;
                ++posNextEnd;
            }
        } else {
            posEnd = posNextEnd;
            if (posNextEnd < a.size() - 1) {
                ++posNextEnd;
            } else {
                posBegin =  posPreBegin;
                --posPreBegin;
            }
        }
    }

    ret.assign(a.begin()+posBegin, a.begin()+posEnd+1);
    return ret;
}


/*

https://leetcode-cn.com/problems/sort-list/
排序链表
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* pre = slow;
        while (fast != nullptr && fast->next != nullptr) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = nullptr;
        
        ListNode *l =  sortList(head);
        ListNode *r =  sortList(slow);
        
        return MergeList(l, r);
    }


    ListNode*  MergeList(ListNode* left, ListNode* right) {
        ListNode* head = nullptr;
        ListNode* p = nullptr;
        while (left != nullptr || right != nullptr) {
            int lval = left != nullptr ? left->val : INT_MAX;
            int rval = right != nullptr ? right->val : INT_MAX;
            ListNode* temp = lval < rval ? left : right;
            if (head == nullptr) {
                head = temp;
                p = temp;
            } else {
                p->next = temp;
                p = temp;
            }
            lval < rval ? left =  left->next : right = right->next;
        }
        return head;
    }
};



/*

https://leetcode-cn.com/problems/longest-increasing-subsequence/
最长上升子序列

*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        return lengthOfLIS2(nums, INT_MIN, 0);
    }

    int  lengthOfLIS2(vector<int>& nums, int prev, int pos) {
        if (pos >= nums.size()) {
            return 0;
        }
        int cond1 = 0, cond2 = 0;
        if (nums[pos] > prev) {
            cond1 =  1 + lengthOfLIS2(nums, nums[pos], pos + 1);
        } 
        cond2 = lengthOfLIS2(nums, prev, pos+1);
        return max(cond1, cond2);

    }
};



/*

https://blog.csdn.net/lxt_Lucia/article/details/81206439
解法2：贪心+二分：
思路：

新建一个 low 数组，low [ i ]表示长度为i的LIS结尾元素的最小值。对于一个上升子序列，显然其结尾元素越小，越有利于在
后面接其他的元素，也就越可能变得更长。因此，我们只需要维护 low 数组，对于每一个a[ i ]，如果a[ i ] > low [当前最长的LIS长度]，
就把 a [ i ]接到当前最长的LIS后面，即low [++当前最长的LIS长度] = a [ i ]。 
那么，怎么维护 low 数组呢？
对于每一个a [ i ]，如果a [ i ]能接到 LIS 后面，就接上去；否则，就用 a [ i ] 取更新 low 数组。具体方法是，
在low数组中找到第一个大于等于a [ i ]的元素low [ j ]，用a [ i ]去更新 low [ j ]。如果从头到尾扫一遍 low 数组的话，
时间复杂度仍是O(n^2)。我们注意到 low 数组内部一定是单调不降的，所有我们可以二分 low 数组，找出第一个大于等于a[ i ]的元素。
二分一次 low 数组的时间复杂度的O(lgn)，所以总的时间复杂度是O(nlogn)。

*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        for (int index = 0; index < nums.size(); ++index) {
            if (dp.empty() || nums[index] > dp[dp.size() - 1]) {
                dp.push_back(nums[index]);
            } else {
                dp[findGreaterThan(dp, 0, dp.size() - 1, nums[index])] =  nums[index];
            }
        }
        return dp.size();
    }

    int findGreaterThan(vector<int>& nums, int start, int end, int target) {
        while (start <= end) {
            int mid = (end - start)/2 + start;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                end = mid  - 1;
            } else {
                start = mid + 1;
            }
        }
        return start;
    }
};



/*

方法一：动态规划
算法：

假设对于以 nums[i] 结尾的序列，我们知道最长序列的长度 length[i]，以及具有该长度的序列的 count[i]。
对于每一个 i<j 和一个 A[i]<A[j]，我们可以将一个 A[j] 附加到以 A[i] 结尾的最长子序列上。
如果这些序列比 length[j] 长，那么我们就知道我们有count[i] 个长度为 length 的序列。如果这些序列的长度与 length[j] 相等，那么我们就知道现在有 count[i] 个额外的序列（即 count[j]+=count[i]）。


最长递增子序列的个数
https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence
 */

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.size() < 1) {
            return 0;
        }
        int n = nums.size();
        vector<int> length(n, 1);
        vector<int> count(n, 1);
        
        for (int j = 1; j < n;  ++j) {
            for (int i = 0; i < j; ++i) {
                if (nums[i] < nums[j]) {
                    if (length[i] >= length[j]) {
                        length[j] = length[i] + 1;
                        count[j] =  count[i];
                    } else if (length[i] + 1 == length[j]) {
                        count[j] += count[i];
                    }
                }
            }
        }
        int maxLen = 0;
        for (int index = 0; index < length.size(); ++index) {
            maxLen = max(length[index], maxLen);
        }

        int retCount = 0;
        for (int index = 0; index < length.size(); ++index) {
            if (length[index] == maxLen) {
                retCount += count[index];
            }
        }
        return retCount;
    }
};


/*

最长连续递增序列
https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/
*/

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.size() < 1) {
            return 0;
        }
        int maxLen = 1;
        int index = 0;
        while (index < nums.size() - maxLen) {
            int count = 0;
            int j = index;
            while(j + 1 < nums.size() && nums[j] < nums[j+1]) {
                ++count;
                ++j;
            }
            ++j;
            index = j;
            maxLen = max(count+1, maxLen);
        }
        return maxLen;
    }
};

/*
https://leetcode-cn.com/problems/rotate-array
旋转数组
 */
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
       k %= nums.size();
       reverse(nums.begin(), nums.end());
       reverse(nums.begin(), nums.begin() + k);
       reverse(nums.begin()+k, nums.end());
    }
};


/*
https://leetcode-cn.com/problems/linked-list-cycle

 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) {
            return false;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        while (slow != nullptr  && fast != nullptr) {
            slow = step(slow,  1);
            fast = step(fast, 2);
            if (slow != nullptr && fast != nullptr && slow == fast) {
                return true;
            }
        }
        return false;
    }
    ListNode *step(ListNode* node, int s) {
        if (!node) {
            return nullptr;
        }
        for (int index = 0; index < s; ++index) {
            if (node != nullptr) {
                node = node->next;
            } else {
                return nullptr;
            }
        }
        return node;
    }
};



/*

https://leetcode-cn.com/problems/binary-tree-maximum-path-sum

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxSum = INT_MIN;

    int maxPathSum(TreeNode* root) {
        if (!root) {
            return 0;
        }
        mps(root);
        return maxSum;
    }

    int mps(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int leftGain  = max(mps(root->left), 0);
        int rightGain = max(mps(root->right), 0);
        
        int total = leftGain + rightGain + root->val;
        maxSum =  total > maxSum ? total : maxSum;
        
        return  root->val + max(leftGain, rightGain);
    }
};




/*

https://leetcode-cn.com/problems/minimum-path-sum/
输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。

dp[i,j] =  grid[i, j] + min(dp[i+1, j], dp[i][j+1]);
 */
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() < 1) {
            return -1;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> mvec(m, vector<int>(n, 0));

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {

                int a = i+1 < m ? mvec[i+1][j] : INT_MAX;
                int b = j+1 < n ? mvec[i][j+1] : INT_MAX;
                if (a == INT_MAX && b == INT_MAX) {
                    mvec[i][j] =  grid[i][j];
                } else {
                    mvec[i][j] =  grid[i][j] + min(a, b);
                }
            }
        }
        return mvec[0][0];
    }
};


/*

三数之和接近某数
https://leetcode-cn.com/problems/3sum-closest
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        //vector<vector<int>> vec;
        if (nums.size() < 3) {
            return 0;
        }
        int minval = INT_MAX;
        //vector<int> temp;
        int ret = 0;
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i <= nums.size() - 3) {
            int j = i + 1;
            int k = nums.size() -  1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                
                if (sum == target) {
                    return sum;
                } else if (sum > target) {
                    if (abs(sum - target) < minval) {
                        minval = abs(sum - target);
                        ret = sum;
                    }

                    while (k > j + 1 && nums[k-1] == nums[k]) --k;
                    --k;

                } else  {

                    if (abs(sum - target) < minval) {
                        minval = abs(sum - target);
                        ret = sum;
                    }
                    while ( j + 1 < k && nums[j] == nums[j+1]) ++j;
                    ++j;
                }
                
            }
            
            while ( i< nums.size() -2 &&  nums[i] == nums[i+1]) ++i;
            ++i;
                
        }
        return ret;
    }
    
};


/*
三数之和等于某数
https://leetcode-cn.com/problems/3sum/
 */

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        return ThreeSum(nums, 0);
    }

    vector<vector<int>> ThreeSum(vector<int>& nums, int target) {
        vector<vector<int>> vec;
        if (nums.size() < 3) {
            return vec;
        }
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i <= nums.size() - 3) {
            int j = i + 1;
            int k = nums.size() -  1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                
                if (sum == 0) {
                    vec.push_back({nums[i], nums[j], nums[k]});
                    while (j+1 < k && nums[j] == nums[j+1])  ++j;
                    ++j;
                    while (k > j+1 && nums[k-1] == nums[k]) --k;
                    --k;
                } else if (sum > 0) {
                    while (k > j+1 && nums[k-1] == nums[k]) --k;
                    --k;
                }  else {
                    while (j+1 < k && nums[j] == nums[j+1])  ++j;
                    ++j;
                }        
            }
            
            while ( i< nums.size() -2 &&  nums[i] == nums[i+1]) ++i;
            ++i;
                
        }
        return vec;
    }

};



/*
https://leetcode-cn.com/problems/merge-k-sorted-lists
合并K个有序链表
 */

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() < 1) return nullptr;
        return mergeKLists(lists, 0, lists.size() -1);
    }

    ListNode* mergeKLists(vector<ListNode*>& lists, int start, int end) {
        if (start == end) {
            return lists[start];
        }
        int mid = (end - start) / 2 + start;
        
        ListNode *a = mergeKLists(lists, start, mid);
        ListNode *b = mergeKLists(lists, mid+1, end);
        return mergeTwoLists(a, b);
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* newHead = nullptr;
        ListNode* p = nullptr;
        while(l1 != nullptr  || l2 != nullptr) {
            int val1 = l1 != nullptr ? l1->val : INT_MAX;
            int val2 = l2 != nullptr ? l2->val : INT_MAX;
            ListNode* temp = val1 < val2 ? l1 : l2;
            if (newHead == nullptr) {
                newHead = temp;
                p = temp;
            } else {
                p->next = temp;
                p = temp;
            }
            val1 < val2 ? l1 = l1->next : l2 = l2->next;
        }
        return newHead;
    }
};



/*



运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。
https://leetcode-cn.com/problems/lru-cache/
 */


class LRUCache {
public:

    typedef unordered_map<int, pair<int, list<int>::iterator>>  Cache;

    LRUCache(int capacity) {
        capacity_ = capacity;
    }
    
    int get(int key) {
        Cache::iterator iter = cache.find(key);
        if (iter != cache.end()) {
            update(iter);
            return iter->second.first;
        }
        return -1;
    }
    
    void put(int key, int value) {
        Cache::iterator iter = cache.find(key);
        if (iter != cache.end()) {
            update(iter);
        } else {

            if (lru.size() >= capacity_) {
                
                cache.erase( lru.back());
                lru.pop_back();
            }
            lru.push_front(key);
        }
        
        cache[key] = make_pair(value, lru.begin());
        
    }
    void update(Cache::iterator iter) {
        lru.erase(iter->second.second);
        lru.push_front(iter->first);
        iter->second.second = lru.begin();
    }

    list<int>  lru;
    int capacity_;
    //typedef unordered_map<int, pair<int, list<int>::iterator>>  Cache;
    Cache cache;
    
};





/*
https://leetcode-cn.com/problems/longest-common-prefix/
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() < 1) return "";
        return lcs(strs, 0, strs.size() - 1);
    }


    string lcs(vector<string>& strs, int left, int right) {
        if (left == right) {
            return strs[left];
        }
        int mid = (right - left)/2 + left;
        
        string l = lcs(strs, left, mid);
    
        string r = lcs(strs, mid+1, right);

        return lcs2(l, r);
    }

    string lcs2(const string& l, const string& r) {
        int i = 0, j = 0;
        while ( i < l.size() && j < r.size() && l[i] == r[j]) {
            ++i;
            ++j;
        }
        return l.substr(0, i);
    }
};


/*

https://leetcode-cn.com/problems/kth-largest-element-in-an-array
找第K大的数字， 可以转换成找第K小的数字

*/


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return findKmin(nums, 0, nums.size() - 1, nums.size() - k);
    }


    int partion(vector<int>& nums, int left, int right) {
        if (left >= right) return left;

        int ptor = nums[left];
        while (left < right) {
            while(left < right &&  nums[right] >= ptor) --right;
            nums[left] = nums[right];
            while(left < right && nums[left] <= ptor) ++left;
            nums[right] = nums[left];   
        }

        nums[left] = ptor;
        return left;
    }
    
    int findKmin(vector<int>& nums, int left, int right, int kmin) {
        if (left >= right) return nums[left];
        int index = partion(nums, left, right);
        if (index == kmin) {
            return  nums[index];
        } else if (index > kmin) {
            return findKmin(nums, left, index-1, kmin);
        } else {
            return findKmin(nums, index+1, right, kmin);
        }

    }
};


/**
 * 查找 搜索二叉树中的 第K小的元素
 * 基本思路：中序遍历
 * https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int res = 0;
        bool find = false;
        int index = 0;
        dfs(root, k, find, res, index);
        return res;
    }

    void dfs(TreeNode* root, int& k, bool& find, int& res, int& i) {
        if (root == nullptr || find) return;

        dfs(root->left, k, find, res, i);
        if (++i == k) {
            res = root->val;
            find = true;
            return;
        }
        dfs(root->right, k, find, res, i);
    }    
};



/*
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。
https://leetcode-cn.com/problems/subsets/

*/


class Solution {
public:

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        subs(0, nums, ret, vector<int>());
        return ret;
    }

    void subs(int index, vector<int>& nums, vector<vector<int>>& ret, vector<int> t) {
        ret.push_back(t);
        for (int i = index; i < nums.size(); ++i) {
            t.push_back(nums[i]);
            subs(i+1, nums, ret, t);
            t.pop_back();
        }
    }

};



/*

给定一个没有重复数字的序列，返回其所有可能的全排列。
https://leetcode-cn.com/problems/permutations/
全排列

*/

class Solution {
public:
    
    vector<vector<int>> vec;

    vector<vector<int>> permute(vector<int>& nums) {
        pme(vector<int>(), nums);
        return vec;
    }
    void  pme(vector<int> nums, vector<int> p) {
        if (p.empty()) {
            vec.push_back(nums);
            return;
        }
        for (int index = 0; index < p.size(); ++index) {
            nums.push_back(p[index]);
            vector<int> t(p);
            t.erase(t.begin() + index);
            pme(nums, t);
            nums.pop_back();
        }
    }
};


/**
 *
 * 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 * https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 * 
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) {
            return nullptr;
        }
        while (root != nullptr) {
            if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else {
                return root;
            }

        }
        return nullptr;

    }
};


/**
 *
 给定一个非空二叉树，返回其最大路径和。

本题中，路径被定义为一条从树中任意节点出

最大路径和， 从根节点到 任意一个节点的路径和
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    int maxPathSum(TreeNode* root) {
        
        if (root == nullptr) {
            return 0;
        }
        int ret = 0;
        mps(0, ret, root);
        return ret;
    }


    void mps(int val, int& maxVal, TreeNode* root) {
        

        maxVal = val > maxVal ? val : maxVal;
        if (root != nullptr) {
            mps(val + root->val, maxVal, root->left);
        
        
            mps(val + root->val, maxVal, root->right);
        }
        
        
    }
};



/*
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？



 */


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0;
        int two  =0;
        for (int index = 0; index < nums.size(); ++index) {
            one = one ^ nums[index] & ~two;
            two = two ^ nums[index] &  ~one;
        }
        return one;
    }
};

作者：jyd
链接：https://leetcode-cn.com/problems/single-number-ii/solution/single-number-ii-mo-ni-san-jin-zhi-fa-by-jin407891/
来源：力扣（LeetCode）



/*

https://leetcode.com/problems/wildcard-matching/

The most confusing part for me is how to deal with '*'. At first I couldn't figure out why the condition would be (dp[i-1][j] == true || dp[i][j-1] == true). Hope detailed DP description below helps!

dp[i][j]: true if the first i char in String s matches the first j chars in String p
Base case:
origin: dp[0][0]: they do match, so dp[0][0] = true
first row: dp[0][j]: except for String p starts with *, otherwise all false
first col: dp[i][0]: can't match when p is empty. All false.
Recursion:
Iterate through every dp[i][j]
dp[i][j] = true:
if (s[ith] == p[jth] || p[jth] == '?') && dp[i-1][j-1] == true
elif p[jth] == '*' && (dp[i-1][j] == true || dp[i][j-1] == true)
-for dp[i-1][j], means that * acts like an empty sequence.
eg: ab, ab*
-for dp[i][j-1], means that * acts like any sequences
eg: abcd, ab*

Start from 0 to len
Output put should be dp[s.len][p.len], referring to the whole s matches the whole p


*/

class Solution {
public:
    bool isMatch(string s, string p) {
        
        vector<vector<bool>>  vec(s.size() + 1, vector<bool>(p.size() + 1, false));
        vec[0][0] = true;
        for (int index = 1; index <= p.size(); ++index) {
            if (p[index-1] == '*') {
                vec[0][index] = true;
            } else {
                break;
            }
        }
        
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                if (s[i-1] == p[j-1]  ||  p[j-1] == '?') {
                    vec[i][j]  = vec[i-1][j-1];
                } else if (p[j-1] == '*') {
                    vec[i][j] =  vec[i-1][j] || vec[i][j-1];
                }
            }
        }
        return vec[s.size()][p.size()];
    }
};


/*
思考动态规划问题的四个步骤

一般解决动态规划问题，分为四个步骤，分别是

问题拆解，找到问题之间的具体联系， 与子问题之间的联系
状态定义
递推方程推导
实现
*/


/*
最长有效路径, 使用stack
https://leetcode.com/problems/longest-valid-parentheses
*/

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() < 1) {
            return 0;
        }
        stack<int> obstk;
        for (int index = 0; index < s.size(); ++index) {
            if (!obstk.empty() && s[obstk.top()] == '(' && s[index] == ')') {
                obstk.pop();
            } else {
                obstk.push(index);
            }
        }
        if (obstk.empty()) return s.size();
        int length = 0;
        int last = s.size();
        int pre = 0;
        while (!obstk.empty()) {
            pre = obstk.top();
            length = max(length,  last - 1 - pre);
            last = pre;
            obstk.pop();
        }
        return max(length, pre);
    }
};

/*
求两个有序数组 的中位数
https://leetcode.com/problems/median-of-two-sorted-arrays
具体思路见：https://zhuanlan.zhihu.com/p/70654378
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), l = 0, r = m;
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        while (l <= r) {
            int i = (l + r) / 2, j = (m + n + 1) / 2 - i;
            if (i && nums1[i - 1] > nums2[j]) {
                r = i - 1;
            } else if (i < m && nums2[j - 1] > nums1[i]) {
                l = i + 1;
            } else {
                int lmax = !i ? nums2[j - 1] : (!j ? nums1[i - 1] : max(nums1[i - 1], nums2[j - 1]));
                if ((m + n) % 2) {
                    return lmax;
                }
                int rmin = i == m ? nums2[j] : (j == n ? nums1[i] : min(nums1[i], nums2[j]));
                return 0.5 * (lmax + rmin);
            }
        }
        return 0.0;
    }
};




/*
利用栈 来实现 大的先出
https://leetcode.com/problems/largest-rectangle-in-histogram
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        
        stack<int>  obstk;
        
        heights.push_back(0);
        
        int area = 0;
        for (int index = 0; index < heights.size(); ++index) {
            
            while(!obstk.empty() && heights[obstk.top()] > heights[index]) {
                int high = heights[obstk.top()];
                
                obstk.pop();
                
                int silde = obstk.empty()? index : (index - obstk.top() - 1);
                area = max (area,  high * silde);
            }

            
            obstk.push(index);
        }
        return area;
    }
};

/*
https://leetcode.com/problems/maximal-rectangle/
*/


/*
https://leetcode.com/problems/multiply-strings
字符串数字 相乘  
比如 num1[i] * num2[j] =  得到的数字位于 num[i+j, i+j+1]

 */
class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size();
        int m = num2.size();
        vector<int>  vec(n+m, 0);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int num = (num1[i] - '0') * (num2[j] - '0');
                
                int p1 = i+j;
                int p2 = p1 + 1;
                num += vec[p2];
                vec[p1] += num / 10;
                
                vec[p2] = num % 10;
            }
        }
        string ret = "";
        int index = 0;
        while (index < vec.size() && vec[index] == 0)  ++index;
        
        if (index >= vec.size()) return "0";
        
        while (index < vec.size()) {
            ret += to_string(vec[index++]);
        }
        return ret;
    }
};



/*
对于递归、深度遍历、二分查找 首先要想好结束的条件
对于动态规划（最优子结构、重叠子问题）
将问题划分成子问题，想好状态转移方程。
*/


/*
求 最长子回文序列的长度
https://leetcode.com/problems/longest-palindromic-subsequence
dp[i][j]: the longest palindromic subsequence's length of substring(i, j), 
here i, j represent left, right indexes in the string

State transition:
dp[i][j] = dp[i+1][j-1] + 2 if s.charAt(i) == s.charAt(j)
otherwise, dp[i][j] = Math.max(dp[i+1][j], dp[i][j-1])
Initialization: dp[i][i] = 1

 */
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int size = s.size();
        
        vector<vector<int>> vec(size, vector<int>(size, 0));
        for (int i =  size - 1; i >= 0; --i) {
            vec[i][i] = 1;
            for (int j = i + 1; j < size; ++j) {
                if (s[i] == s[j]) {
                    vec[i][j] = vec[i+1][j-1] + 2;
                } else {
                    vec[i][j] = max(vec[i+1][j], vec[i][j-1]);
                }
            }
        }
        return vec[0][size-1];
    }
};

/*
https://leetcode.com/problems/longest-palindromic-substring
*/
class Solution {
public:
    string longestPalindrome(string s) {
        int maxLen = 0;
        int pos = 0;
        for (int index = 0; index < s.size() - maxLen/2; ++index) {
            int j = index;
            int k = index;
            
            while (k < s.size()-1 && s[k] == s[k+1]) k++;
            
            while (j > 0 && k < s.size()-1 && s[j-1] == s[k+1])  {
                --j;
                ++k;
            }
            if (maxLen < (k - j + 1)) {
                maxLen = k - j + 1;
                pos = j;
            }
        }
        
        return s.substr(pos, maxLen);
    }
};


/* 
求最长公共子序列

c[i,j] =  0                          如果 i = 0 或 j = 0
c[i,j] =  c[i-1, j-1] + 1            如果 i,j > 0 且 xi = yi
c[i,j] =  max(c[i, j-1], c[i-1, j])  如果 i,j > 0 且 xi != yi
*/

class Solution {
public:
    string lcs(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<string>> vec(n+1, vector<string>(m+1, ""));
        
        for(int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str1[i-1] == str2[j-1]) {
                    vec[i][j] = vec[i-1][j-1] + str1[i-1];
                } else {
                    vec[i][j] =  (vec[i-1][j]).size() > (vec[i][j-1]).size() ? vec[i-1][j] : vec[i][j-1];
                }
            }
        }
        return vec[n][m];
        
    }
};

/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/

具体 ：https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems


T[i][k][0] 代表在 第i天 经过K次交易 最后还剩0 个股票 在手上 的最大利润
T[i][k][1] 代表在 第i天 经过K次交易 最后还剩1 个股票 在手上 的最大利润


Base cases:
T[-1][k][0] = 0, T[-1][k][1] = -Infinity
T[i][0][0] = 0, T[i][0][1] = -Infinity

Recurrence relations:
T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i])

 */

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int T_ik0 = 0, T_ik1 = INT_MIN;
        for (int index = 0; index < prices.size(); ++index) {
            int T_ik0_old = T_ik0;
            T_ik0 = max(T_ik0, T_ik1+ prices[index]);
            T_ik1 = max(T_ik1, T_ik0_old - prices[index] - fee);
        }
        return T_ik0;
    }
};


/*
https://leetcode.com/problems/relative-sort-array/
在日常生活的可以用到的
给定arr1和arr2两个数组，arr2的元素是不同的，arr2中的所有元素也在arr1中。
对arr1的元素进行排序，使arr1中的项的相对顺序与arr2中的相同。不出现在arr2中的元素应按升序放置在arr1的末尾。
 */

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int>  umap;
        int length = arr1.size();
        for (int index = 0; index < arr1.size(); ++index) {
            umap[arr1[index]] = length + arr1[index]; 
        }
        for (int index = 0; index < arr2.size(); ++index) {
            umap[arr2[index]] =  index;
        }
        sort(arr1.begin(), arr1.end(), [&umap](int a, int b) {
            return umap[a] < umap[b];
        });
        return arr1;
    }
};



/*
 Find Minimum in Rotated Sorted Array

https://leetcode.com/problems/find-minimum-in-rotated-sorted-array

特殊例子 ：[2,1] 、 【3、1、2】
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        
        while (low < high) {
            /*  3  4 5 1 2 */
            if (nums[low] < nums[high]) {
                return nums[low];
            }
            
            int mid = (high-low)/2 + low;
            /* 2 1 */
            if (nums[mid] >= nums[low]) {
                low = mid + 1;
            } else {
                /* 7 0 1 2 */
                high = mid;
            }
        }
        return nums[low];
        
    }
};

/*
https://leetcode.com/problems/search-in-rotated-sorted-array
Search in roated sorted array

 */
class Solution1 {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        
        while (low < high) {
            if (nums[low] < nums[high]) {
                break;
            }
            int mid = (high - low) / 2 + low;
            if (nums[mid] >= nums[low]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        int roated = low;        
        low = 0;
        high = nums.size() - 1;
        while (low <= high) {
            int mid = ((high - low) / 2 + low);
            int realmid = (mid + roated) % nums.size();
            if (nums[realmid] == target) {
                return realmid;
            } else if (nums[realmid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return -1;
    }
};


class Solution2 {
public:
    int search(vector<int>& nums, int target) {
        
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high) {
            int mid = (high - low)/2 + low;
            if (nums[mid] == target) {
                
                return mid;
            } 
            /* 3 1 */

            if (nums[mid] >= nums[low]) {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
        
    }
};



/*
Merge Interval
https://leetcode.com/problems/merge-intervals
 */
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), compare);
        int index = 0;
        vector<vector<int>> ret;
        
        vector<int> temp(2, 0);
        
        while(index < intervals.size()) {
            temp[0] = intervals[index][0];
            temp[1] = intervals[index][1];
            
            while(index+1 < intervals.size() && temp[1] >= intervals[index+1][0]) {
                temp[0] = min(temp[0], intervals[index+1][0]);
                temp[1] = max(temp[1], intervals[index+1][1]);
                
                ++index;
            }
            
            ret.push_back(temp);
            ++index;
            
        }
        return ret;
    }
    
    static bool  compare(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    }
};


/*
Unique Path:
动态规划：
dp[0][j] = dp[i][0] = 1
dp[i][j] = dp[i-1][j] + dp[i][j-1]


Unique Path II
https://leetcode.com/problems/unique-paths-ii/

*/

class Solution {            
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<long>>  vec(m, vector<long>(n, 0));
        for (int i = 0; i < m; ++i) {
            if (!obstacleGrid[i][0]) {
                vec[i][0] = 1;
                
            } else {
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!obstacleGrid[0][i]) {
                vec[0][i] = 1;
            } else {
                break;
            }
        }
        
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (!obstacleGrid[i][j]) {
                    vec[i][j] = vec[i-1][j] + vec[i][j-1];
                }
            }
        }
        return vec[m-1][n-1];
    }
};

Unique Path III
https://leetcode.com/problems/unique-paths-iii/






/*
碰到难题思路：
先用递归把做出来，结果显然，TLE。既然能用递归，就肯定可以用动态规划，
然后就把递归变成动态规划，变成动态规划后看能不能再优化空间，
如果不能，就直接return了，如果能就优化，这个现在已经成为套路了。
 */

/*

编辑距离：
dp[i][j] =   /    dp[i - 1][j - 1]                                                     if word1[i - 1] == word2[j - 1]

             \    min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1            else

 */


/*
求连续子数组中的最大和

maxSubArray(A, i) = （maxSubArray(A, i - 1) > 0 ? maxSubArray(A, i - 1) : 0）    +   A[i]; 
比如 -1， 2，4， -1， 2  这个数组中连续子数组的最大和为 2+4+（-1）+2 = 7
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int *dp = new int[nums.size()];
        dp[0] = nums[0];
        int Max = nums[0];
        for (int index = 1; index < nums.size(); ++index) {
            dp[index] = nums[index] + (dp[index-1] > 0 ? dp[index-1] : 0);
            Max = max(dp[index], Max);
        }
        return Max;
    }
};

/*
https://leetcode.com/problems/non-decreasing-array/
 
Non-decreasing Array
在 一个数组 比如 1 4 6 8 2 10， 最多改变一个数字，使之成为非递减的数组， 这里将2 改为8 即可

思路 :

 数组为：1 4 6 8 2 10  
 if (num[i-1] > num[i] && num[i-2] > num[i] ) then  num[i] = num[i-1] 
 
 数组为：1 2 3 6 4
 if (num[i-1] > num[i] && num[i-2] < num[i]) then num[i-1] = num[i]
 */
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        
        int count = 0;
        
        for(int index = 1; index < nums.size() && count <= 1; ++index) {
            if (nums[index - 1] > nums[index]) {
                if (index >= 2 && nums[index - 2] > nums[index]) {
                    nums[index] = nums[index-1];
                } else {
                    nums[index - 1] = nums[index];
                }
                ++count;
            }
        }
        return count <= 1;
    }
};


/*
Pow(x, n)
求阶乘
 */

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1;
        if (n < 0) {
            x = 1/x;
        }
        return  abs(n%2) == 1? x * myPow(x*x, abs(n/2)) : myPow(x*x, abs(n/2));
    }
};

/*
https://leetcode.com/problems/subsets
求集合的所有子集合
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> temp;
        backTrack(ret, temp, nums, 0);
        return ret;
        
    }
    
    void backTrack(vector<vector<int>>& a, vector<int>& temp, const vector<int>& num, int start) {
        a.push_back(temp);
        for (int index = start; index < num.size(); ++index) {
            temp.push_back(num[index]);
            backTrack(a, temp, num, index + 1);
            temp.pop_back();
        }
    }
};

/*
https://leetcode.com/problems/subarray-sum-equals-k/submissions/
求连续子数组之和等于K 的个数
 */

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int>  prefixSum;
        prefixSum[0] = 1;
        int retCount = 0;
        int sum = 0;
        for (int index = 0; index < nums.size(); ++index) {
            sum += nums[index];
            retCount += prefixSum[sum -k];
            ++prefixSum[sum];
        }
        return retCount;
    }
};

/*
https://leetcode.com/problems/continuous-subarray-sum/

 */


/*
Roate Image

 */
here give a common method to solve the image rotation problems.

/*
 * clockwise rotate
 * first reverse up to down, then swap the symmetry 
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
*/
void rotate(vector<vector<int> > &matrix) {
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}

/*
 * anticlockwise rotate
 * first reverse left to right, then swap the symmetry
 * 1 2 3     3 2 1     3 6 9
 * 4 5 6  => 6 5 4  => 2 5 8
 * 7 8 9     9 8 7     1 4 7
*/
void anti_rotate(vector<vector<int> > &matrix) {
    for (auto vi : matrix) reverse(vi.begin(), vi.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}