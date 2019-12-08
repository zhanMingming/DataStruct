/*
* @Author: zhanmingming
* @Date:   2019-11-25 22:40:36
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-12-08 00:05:12
*/

/*
思考动态规划问题的四个步骤

一般解决动态规划问题，分为四个步骤，分别是

问题拆解，找到问题之间的具体联系， 与子问题之间的联系
状态定义
递推方程推导
实现
*/




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
            if (nums[mid] >= nums[high]) {
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

*/





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