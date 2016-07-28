//
//  interviewAlg.cpp
//  InterviewAlgorithms
//
//  Created by lingLong on 16/7/26.
//  Copyright © 2016年 ling. All rights reserved.
//

#include "interviewAlg.hpp"
#include <queue>
#include <stack>
#include <algorithm>


//求两个数中的最大值
int AllAlgorithms::max(int a, int b){
    return ((a+b) + abs(a-b))/2;
}
//直方图矩形最大面积
//给定n个非负整数,表示直方图的方柱的高 度,同时,每个方柱的宽度假定都为1;试 找出直方图中最大的矩形面积。如:给定高 度为:2,1,5,6,2,3,最大面积为10。
int AllAlgorithms::largestRectArea(vector<int> &height){
    height.push_back(0);//确保原数组height的最后一位能够计算的到
    
    int answer = 0;
    stack<int> stack;
    int temp;
    for (int i = 0; i < (int)height.size(); ) {
        if (stack.empty() || height[i] > height[stack.top()]) {
            stack.push(i);
            i ++;
        }
        else{
            temp = stack.top();
            stack.pop();
            answer = max(answer, height[temp] * (stack.empty() ? i : i - stack.top() - 1));
        }
    }
    return answer;
    
}

//收集雨水问题
//给定n个非负整数,表示直方图的方柱的高 度,同时,每个方柱的宽度假定都为1。若 使用这样形状的容器收集雨水,可以盛多少 水量?
//计算所有局部最低点,然后每个“洼坑”分 别计算,这种贪心的策略是不对的,因为, 有可能局部最高点被覆盖:
//如:6,3,2,0,3,2,0,1,5,6,4,3,7,5,4,0,3,2,5,8,2,4
//算法分析
//记最终盛水量为trap,初值为0;
//考察直方图最左边L和最右边R的两个方柱:
//它们两个本身,一定不可能存储雨水:因为在最边界;  记它们比较低的那个为X,与X相邻的方柱记做Y。
// 若Y≥X,可将X丢弃,且trap值不变;
// 若Y<X,则X-Y即为Y方柱最多盛水量;仍然丢弃X,
//且trap+=(X-Y)。
//无论如何,L或者R都将向中间靠近一步,重复上述过程,
//直至L==R。
int AllAlgorithms::gatherRain(vector<int> &A){
    int secondHeight = 0;//当前找到的第二大的数
    int left = 0;
    int right = (int)A.size() - 1;
    int volume = 0;//一次遍历每个方柱能装的雨水的容量
    while (left < right) {
        if (A[left] < A[right]) {
            secondHeight = max(A[left], secondHeight);
            volume = volume + (secondHeight - A[left]);
            left ++;
        }else{
            secondHeight = max(A[right], secondHeight);
            volume = volume + (secondHeight - A[right]);
            right --;
        }
    }
    return volume;
}

//拓扑排序
//对一个有向无环图(Directed Acyclic Graph, DAG)G进行拓扑排序,是将G中所有顶点排 成线性序列,使得图中任意一对顶点u和v, 若边(u,v)∈E(G),则u在线性序列中出现在v 之前。
//方法：1.从有向图中选择一个没有前驱(即入度为0)的 顶点并且输出它;2.从网中删去该顶点,并且删去从该顶点发出 的全部有向边;
//3.重复上述两步,直到剩余的网中不再存在没 有前驱的顶点为止。


//拓扑排序的本质是不断输出入度为0的点,该算法可 用于判断图中是否存在环;
//可以用队列(或者栈)保存入度为0的点,避免每次遍 历所有点;
//每次更新连接点的入度即可。
//拓扑排序其实是给定了结点的一组偏序关系。
// “拓扑”的涵义不限于此,在GIS中,它往往指点、 线、面、体之间的相互邻接关系,即“橡皮泥集 合” 。存储这些关系,往往能够对某些算法带来好 处。
//计算不自交的空间曲面是否能够围成三维体  提示:任意三维边都邻接两个三维曲面
//结点数为n，用邻接矩阵G[n][n]存储边权，用inDegree[n]存储每个结点的入度
void AllAlgorithms::topologic(vector<vector<int>> &G ,vector<int> & inDegree,vector<int> &toposort){
    int count = 0;//当前拓扑排序列表中有多少结点
    int n = (int)inDegree.size();
    queue<int> q;//保存入度为0的结点，还可以用栈甚至随机取
    for (int i = 0; i < n; i ++) {
        if (0 == inDegree[i]) {
            q.push(i);
        }
    }
    int curr;//当前入度为零的节点
    while (! q.empty()) {
        curr = q.front();
        q.pop();
        toposort[count ++] = curr;
        for (int j = 0; j < n; j ++) {
            if (G[curr][j]) {
                inDegree[j] --;
                if (0 == inDegree[j]) {
                    q.push(j);
                }
            }
        }
    }

}

//最长括号匹配
//给定字符串,仅包含左括号‘(’和右括号 ‘)’,它可能不是括号匹配的,设计算法, 找出最长匹配的括号子串,返回该子串的长 度。
//如:
// (():2
//()():4
//()(()):6
//(()()):6
int AllAlgorithms::getLongestParenthese(const char *p){
    int len = (int)strlen(p);
    stack<int> stack;
    int answer = 0;//最终解
    int start = -1;//左括号的前一个位置，初始匹配位置
    for (int i = 0; i < len; i ++) {
        if(p[i] == '('){//如果为左括号，压栈
            stack.push(i);
        }
        else{//如果为右括号，则一定与栈顶左括号匹配
            if(stack.empty())//如果栈为空，没有匹配的左括号
                start = i;
            else
            {
                stack.pop();//不为空，出栈，匹配了
                if (stack.empty()) {//这是如果栈空了，i-start就是匹配长度，并比较
                    answer = max(answer,i - start);
                    
                }
                else//如果这时栈不空，则当前元素是上次匹配的最后位置，比较大小
                    answer = max(answer, i - stack.top());
            }
                
        }
    }
    return answer;
    
}

//改进版
int AllAlgorithms::getLongestParenthese2(const char *p){
    int len = (int)strlen(p);
    int answer = 0;
    int start = -1;//最深的（deep = 0）左括号的前一个位置
    int deep = 0;//表示遇到了多少左扩号
    for (int i = 0; i < len; i ++) {//从左向右扫描
        if (p[i] == '(') {
            deep ++;
        }
        else{
            deep --;
            if (! deep ) {
                answer = max(answer, i - start);
            }
            else if (deep < 0)//右括号数大于左括号，初始化为for循环前
            {
                deep = 0;
                start = i;
            }
        }
    }
    deep = 0;//遇到了多少右括号
    start = len;//最深的右括号的位置
    for (int i = len - 1; i >= 0; i --) {//从右往左再扫描一次
        if (p[i] == ')') {
            deep ++;
        }
        else{
            deep --;
            if (! deep) {
                answer = max(answer, start - i);
            }
            else if (deep < 0)
            {
                deep = 0;
                start = i;
            }
        }
    }
    return answer;
}

//逆波兰表达式
//Reverse Polish Notation,即后缀表达式。
// 习惯上,二元运算符总是臵于与之相关的两 个运算对象之间,即中缀表达方法。波兰逻 辑学家J.Lukasiewicz于1929年提出了运算符 都臵于其运算对象之后,故称为后缀表示。
//如:
// 中缀表达式:a+(b-c)*d
// 后缀表达式:abc-d*+
int AllAlgorithms::reversePolishNotation(const char **p, int size){
    stack<int> stack;
    int a,b;
    const char *token;
    for (int i = 0; i < size; i ++) {
        token = p[i];
        if (! isOperator(token)) {
            stack.push(atoi(token));
        }
        else{
            b = stack.top();
            stack.pop();
            a = stack.top();
            stack.pop();
            if(token[0] == '+')
                stack.push(a + b);
            else if(token[0] == '-')
                stack.push(a - b);
            else if(token[0] == '*')
                stack.push(a * b);
            else 
                stack.push(a / b);



        }
    }
    return stack.top();
}

//判断是否为运算符
bool AllAlgorithms::isOperator(const char *token){
    return ((token[0] == '+') || (token[0] == '-') || (token[0] == '*') || (token[0] == '/'));
}

//字符串循环移位

//翻转某一段字符串
void AllAlgorithms::reverseString(string &str, int idxFrom, int idxTo){
    while (idxFrom < idxTo) {
        char tmp = str[idxFrom];
        str[idxFrom ++] = str[idxTo];
        str[idxTo --] = tmp;
    }
}

void AllAlgorithms::leftRotateMoving(string &str, int n, int k){
    k = k % n;
    reverseString(str, 0, k-1);
    reverseString(str, k, n-1);
    reverseString(str, 0, n-1);
}
//最长公共子序列
void AllAlgorithms::longestCommonSequence(const char *str1, const char *str2, string &res){
    int length1 = (int)strlen(str1);
    int length2 = (int)strlen(str2);
    const char *s1 = str1 - 1;//从1开始
    const char *s2 = str2 - 1;
    vector<vector<int>> arrPair(length1 + 1,vector<int>(length2 + 1));
    for (int i = 0; i <= length1; i ++) {
        arrPair[i][0] = 0;
    }
    for (int i = 0; i <= length2; i ++) {
        arrPair[0][i] = 0;
    }
    
    for (int i = 1; i <= length1; i ++) {
        for (int j = 1; j <= length2; j ++) {
            if (s1[i] == s2[j]) {
                arrPair[i][j] = arrPair[i-1][j-1] + 1;
            }
            else
                arrPair[i][j] = max(arrPair[i][j-1], arrPair[i-1][j]);
        }
    }
    int m,n;
    m = length1;
    n = length2;
    while ((m != 0) && (n != 0)) {
        if(s1[m] == s2[n]){
            res.push_back(s1[m]);//赋给输出数组
            m --;
            n --;
        }
        else{
            if (arrPair[m][n-1] > arrPair[m-1][n])
                n --;
            else
                m --;
        }
    }
    reverse(res.begin(), res.end());
}

//LCS的应用：最长递增子序列LIS
//Longest Increasing Subsequence,LCS:
// 找出给定数组最长且单调递增的子序列。
// 如:给定数组{5,6,7,1,2,8},则其最长的单调
//递增子序列为{5,6,7,8},长度为4。
// 分析:其实此LIS问题可以转换成最长公子序列
//问题,为什么呢?

int AllAlgorithms::longestIncreasingSequence(const int *p, int length, int *pre, int &nIdx){
    int * longest = new int[length];
    for (int i = 0; i < length; i ++) {
        longest[i] = 1;//最长序列的长度
        pre[i] = -1;//前缀串的索引
    }
    int list = 1;//LIS的最长长度，至少会有自己本身，所以至少有1
    nIdx = 0;
    for (int i = 1; i < length; i ++) {
        for (int j = 0; j < i; j++) {
            if (p[j] <= p[i]) {
                if (longest[i] < longest[j] + 1) {
                    longest[i] = longest[j] + 1;
                    pre[i] = j;
                }
            }
        }
        if (list < longest[i]) {
            list = longest[i];
            nIdx = i;
        }
    }
    delete[] longest;
    return list;
}
//获取最长递增子序列
void AllAlgorithms::getLIS(const int *arr, const int *pre, int nIdx, vector<int> &list){
    while (nIdx >= 0) {
        list.push_back(arr[nIdx]);
        nIdx = pre[nIdx];
    }
    reverse(list.begin(), list.end());
}
//打印
void AllAlgorithms::_print(int *p, int size){
    for (int i = 0; i < size; i ++) {
        cout<<p[i]<<'\t';
        
    }
    cout<<endl;
}

//字符串的全排列
//给定字符串S[0...N-1],设计算法,枚举S的 全排列。
//递归算法

void AllAlgorithms::recursionPermutation(int *a, int size, int n){
    if (n == size -1 ) {
        _print(a, size);
        return;
    }
    for (int i = n; i < size; i ++) {
        swap(a[i], a[n]);
        recursionPermutation(a, size, n+1);
        swap(a[i], a[n]);
    }
}

//如果存在重复字符
//判断是否存在重复字符
bool AllAlgorithms::isDuplicate(const int *a, int n, int t){
    while (n < t) {
        if (a[n] == a[t]) {
            return false;
        }
        n ++;
    }
    return true;
}

void AllAlgorithms::strFullPermutation(int *a, int size, int n){
    if (n == size -1) {
        _print(a, size);
        return;
    }
    for (int i = n; i < size; i ++) {
        if (! isDuplicate(a, n, i)) {
            continue;
        }
        swap(a[i], a[n]);
        strFullPermutation(a, size, n + 1 );
        swap(a[i], a[n]);
    }
}









