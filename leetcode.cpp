18
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int len = nums.size();
        int left=0,mid,right;
        sort(nums.begin(),nums.end());
        int sum;
        for(int i=0;i<len-3;i++)
        {
            sum = target-nums[i];
            if(i>0&&nums[i]==nums[i-1])
                continue;
            for(left=i+1;left<len-2;left++)
            {
                mid = left+1;
                right= len-1;
                int tmp = sum-nums[left];
                if(left>i+1&&nums[left]==nums[left-1])
                    continue;
                while(mid<right)
                {
                    if(nums[mid]+nums[right]==tmp)
                    {
                        int tmp_mid = nums[mid];
                        int tmp_right = nums[right];
                        int a[]={nums[i],nums[left],tmp_mid,tmp_right};
                        vector<int> v(a,a+4);
                        result.push_back(v);
                        while(mid<right&&nums[++mid]==tmp_mid);
                        while(mid<right&&nums[--right]==tmp_right);
                        
                    }
                    else if(nums[mid]+nums[right]>tmp)
                        right--;
                    else if(nums[mid]+nums[right]<tmp)
                        mid++;
                }
            }
        }
        return result;
    }
};
35.
static const auto speedup = []() {std::ios::sync_with_stdio(false); std::cin.tie(NULL); return 0; }();
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (nums.size() == 0) return 0;
		int low = 0;
		int high = nums.size() - 1;
		//使用二分查找
		while (low <= high)
		{
			int mid = low + (high - low) / 2;
			if (nums[mid] < target) low = mid + 1;
            else if (nums[mid] > target) high = mid - 1;
			else return mid;
		}
		return low;
    }
};

36.
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9][9]={0};
        int column[9][9]={0};
        int box[9][9]={0};
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(board[i][j]!='.')
                {
                    int num = board[i][j]-'0'-1;
                    int k = i/3*3+j/3;
                    if(rows[i][num]||column[j][num]||box[k][num])
                        return false;
                    else
                        rows[i][num]=1;
                        column[j][num]=1;
                        box[k][num]=1;
                }
            }
        }
        return true;
    }
};
37
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        util(board,0);
    }
    bool util(vector<vector<char>>& board,int pos)
    {
        if(pos>=81)
            return true;
        int i = pos/9;
        int j = pos%9;
        if(board[i][j]!='.')
            return util(board,pos+1);
        else
        {
            for(char c='1';c<='9';c++)
            {
                if(isValid(board,i,j,c))
                {
                    board[i][j]=c;
                    if(util(board,pos+1))
                        return true;
                    else
                        board[i][j]='.';
                }
            }
        }
        return false;
    }
private:
    bool isValid(vector<vector<char>>& board,int row,int col,char c)
    {
        for(int i=0;i<9;i++)
        {
            if(board[i][col]!='.'&&board[i][col]==c) return false;
            if(board[row][i]!='.'&&board[row][i]==c) return false;
            if(board[(row/3)*3+i/3][3*(col/3)+i%3]!='.'&&board[(row/3)*3+i/3][3*(col/3)+i%3]==c) return false;
        }
        return true;
}
};
38
class Solution {
public:
    string countAndSay(int n) {
        if(n==1)
            return "1";
        else
            return translate(countAndSay(n-1));
    }
private:
    string translate(string s)
    {
        string tmp="";
        int len = s.length();
        int i=1;
        int count=1;
        char a;
        while(i<len)
        {
            if(s[i]==s[i-1])
            {
                count++;
                i++;
            }
            else
            {
                a = '0'+count;
                tmp = tmp+a+s[i-1];
                i++;
                count = 1;
            }
            
        }
        a = '0'+count;
        tmp = tmp+a+s[i-1];
        return tmp;
    }
    
};
39
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> res;
        vector<int> combinations;
        combination_Sum(candidates,target,res,combinations,0);
        return res;
    }
    void combination_Sum(vector<int> &candidates,int target,vector<vector<int>> &res,vector<int> &combinations,int begin)
    {
        if(target==0)
        {
            res.push_back(combinations);
            return;
        }
        for(int i=begin;i!=candidates.size()&&target>=candidates[i];i++)
        {
            combinations.push_back(candidates[i]);
            combination_Sum(candidates,target-candidates[i],res,combinations,i);
            for(int j=0;j<combinations.size();j++)
                cout << combinations[j] << " ";
            cout << endl;
            combinations.pop_back();
        }
    }
};
40

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> res;
        vector<int> combinations;
        combinationSum(candidates,target,res,combinations,0);
        return res;
    }
    void combinationSum(vector<int>& candidates,int target,vector<vector<int>> &res,vector<int> &combinations,int begin)
    {
        if(target==0)
        {
            int flag=1;
            for(int i=0;i<res.size();i++)
            {
                if(res[i]==combinations)
                {
                    flag=0;break;
                }
            }
            if(flag==1)
                res.push_back(combinations);
            return;
        }
        for(int i=begin;i<candidates.size()&&target>=candidates[i];i++)
        {
            combinations.push_back(candidates[i]);
            combinationSum(candidates,target-candidates[i],res,combinations,i+1);
            combinations.pop_back();
        }
    }
};
41
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int len = nums.size();
        if(len==0)
            return 1;
        if(len==1)
        {
            if(nums[0]==1)
                return 2;
            else
                return 1;
        }
        else
        {
            int pos;
            pos=findPosition(nums)+1;
            int count=1;
            while(pos<len)//越界判断应该在其他判断条件之前 
            {
                while(pos<len-1&&nums[pos+1]==nums[pos])
                    pos++;
                if(nums[pos]!=count)
                {
                    break;
                }
                if(nums[pos]==count)
                {
                    pos++;
                    count++;
                }
                    
            }
            
            return count;
        }
    }
    private:
    int findPosition(vector<int>& num)
    {
        int left=0;
        int right = num.size()-1;
        int mid;
        if(num[0]>0)
            return -1;
        if(num[right]<=0)
            return right-1;
        else
        {
            while(left<right)
            {
                mid = (left+right)/2;
                if(num[mid]>0)
                    right=mid;
                if(num[mid]<=0&&num[mid+1]>0)              
                    return mid;
                if(num[mid+1]<=0)
                    left=mid+1;
                    
            }
            
        }
        return left;
    }
};
42
class Solution {
public:
    int trap(vector<int>& height) {
        int max = 0;
        int maxID = 0;
        int result = 0;
        for(int i=0;i<height.size();i++)
        {
            if(height[i]>max)
            {
                max = height[i];
                maxID = i;
            }
        }
        int preHigh =0;
        for(int i=0;i<maxID;i++)//from left to highest position;
        {
            if(height[i]>preHigh)
                preHigh = height[i];
            result += preHigh -height[i];
        }
        preHigh=0;
        for (int i=height.size()-1;i>maxID;i--)
        {
            if(height[i]>preHigh)
                preHigh = height[i];
            result += preHigh -height[i];
        }
        return result;
    }
};
43
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.length()-1;
        int n = num2.length()-1;
        int pos[m+n+2] = {0};
        for(int i=m;i>=0;i--)
            for(int j=n;j>=0;j--)
            {
                int mul = (num1[i]-'0')*(num2[j]-'0');
                int p1=i+j;
                int p2 = i+j+1;
                int sum = mul + pos[p2];
                pos[p1] += sum/10;
                pos[p2] = sum%10;
            }
        string res="";
        for(int p:pos)
        {
            if(p==0&&res.length()==0)
            {
                continue;
            }
            else
            {
                char c = '0'+p;
                res = res + c;
            }
                
        }
        return res.length()==0?"0":res;
    }
};
44
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        m = len(s)
        n = len(p)
        if m==0 and n==0:
            return True   
        P = [[False for i in range(n+1)] for j in range(m+1)]
        P[0][0] = True
        for i in range(0,m+1):
            for j in range(1,n+1):
                if p[j-1]=='*':
                    P[i][j] = P[i][j-1] or (i>0 and P[i-1][j])
                if p[j-1]!='*':
                    P[i][j] = i>0 and P[i-1][j-1] and (s[i-1]==p[j-1] or p[j-1]=='?')
        return P[m][n]
46

class Solution(object):
    
    def dfs(self,cur,nums,a,result):
        if cur == len(nums):
            result.append(a)
        for x in nums:
            ok=1
            for i in xrange(cur):
                if(a[i]==x):
                    ok=0;
            if ok==1:
                if len(a)==cur:
                    a.append(x)
                else:
                    a[cur] = x
                self.dfs(cur+1,nums,a[0:cur+1],result)
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        result = []
        a = []
        self.dfs(0,nums,[],result)
        return result
47
class Solution:
    def myPow(self, x: float, n: int) -> float:
        if n < 0:
            return 1/self.myPow(x,-n)
        if n == 0:
            return 1
        if n % 2:
            return x*self.myPow(x,n-1)
        return self.myPow(x*x,n/2)
48
class Solution(object):
    
    def permuteUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        nums.sort(reverse=False)
        def dfs(cur,n,num,a,ans):
            if n == cur:
                ans.append(a)
                return
            for i in xrange(len(num)):
                ok=1
                if i>0:
                    if num[i]==num[i-1]:
                        ok=0
                        continue
                if ok==1:
                    if len(a) == cur:
                        a.append(num[i])
                        dfs(cur+1,n,num[0:i]+num[i+1:],a[:cur+1],ans)  
                    else:
                        a[cur] = num[i]
                        
                        dfs(cur+1,n,num[0:i]+num[i+1:],a[:cur+1],ans)   
        ans=[]
        n = len(nums)
        dfs(0,n,nums,[],ans)
        return ans
49
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)
        for i in range(n):
            for j in range(i):
                matrix[i][j],matrix[j][i]=matrix[j][i],matrix[i][j]
        for i in range(n):
            matrix[i].reverse()
            
50
from collections import defaultdict
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        tmp = defaultdict(list)
        for s in strs:
            tmp[tuple(sorted(s))].append(s)
        ans=[]
        for k in tmp:
            ans.append(tmp[k])
        return ans
102
class Solution{
public:
    vector<vector<int> > levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        vector<int> level;
        list<TreeNode*> cur,next;
        if(root==nullptr)
            return result;
        cur.push_back(root);
        while(!cur.empty())
        {
            while(!cur.empty())
            {
                TreeNode *node = cur.front();
                cur.pop_front();
                level.push_back(node->val);
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                
            }
            result.push_back(level);
            level.clear();
            swap(cur,next);
        }
        return result;
    }
};
/*#include <cstdio>
#include <cstdlib>
#include <stack>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <exception>
#include <map>
#include <list>
#include <algorithm>
#include <ctime>
#include <string>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val):val(val), left(NULL),right(NULL){} ; 
};

TreeNode *constructTree(int *dat , int len)
{
    TreeNode *root = NULL;
    int index = 0;
    if(len > 0)
        root = new TreeNode(dat[index]);
    else
        return NULL;

    list<TreeNode *> node;
    node.push_back(root);
    index ++;
    while(index < len)
    {
        if(!node.empty())
        {
            TreeNode *root = node.front();
            if(index < len )
            {
                if(dat[index] != '#')
                {
                    root->left = new TreeNode(dat[index]);  
                    node.push_back(root->left);
                }
                index ++;
            }
            if(index < len )
            {
                if(dat[index] != '#')
                {
                    root->right = new TreeNode(dat[index]); 
                    node.push_back(root->right);
                }
                index ++;
            }
            node.pop_front();
        }
    }

    return root;
}

void traversal(TreeNode *node)
{
    if(!node)
        return;
    cout <<"\t"<< node->val;
    traversal(node->left);
    traversal(node->right);
}
void printvector(const vector<vector<int> > &v)
{
    for(int i=0;i<v.size();++i)
    {
        for(int j=0;j<v[i].size();++j)
            cout<<v[i][j]<<',';
        cout<<endl;
    }

}
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root)
    {
        std::vector<vector<int> > result;
        if(root==nullptr) return result;
        std::vector<int> level;
        queue<TreeNode *> current,next;
        current.push(root);
        while(!current.empty())
        {
            while(!current.empty())
            {
                TreeNode *node=current.front();
                current.pop();
                level.push_back(node->val);
                if(node->left!=nullptr) next.push(node->left);
                if(node->right!=nullptr) next.push(node->right);

            }

            result.push_back(level);
            level.clear();
            swap(current,next);

        }
        return result;
    }

};



int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout <<"Usage: ./createTreev 30 50 50 2 3 3 2"<<endl;
        exit(1);
    }

    int len = argc -1 ;
    cout << len <<endl;

    int *data = (int *)malloc(sizeof(int) * len);
    memset(data, 0, sizeof(char)*len);
    for(int i=1; i<argc; i++)
    {
        if(*argv[i] != '#')
            data[i-1] = atoi(argv[i]) ;
        else
            data[i-1] = '#';
    }
    for(int i=0; i < len ; i++)
        cout <<"\t"<< data[i] ;
    cout << endl;
    cout << endl;

    TreeNode *tree = NULL;
    tree = constructTree(data, len);

    //traversal(tree);
    //cout << endl;

    Solution s;
    printvector(s.levelOrder(tree));
}
*/
