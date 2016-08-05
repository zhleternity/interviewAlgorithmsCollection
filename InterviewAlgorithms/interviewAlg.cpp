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
//求两个数中的最小值
int AllAlgorithms::min(int a, int b){
    return ((a+b) - abs(a-b))/2;
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
//空间换时间
void AllAlgorithms::strFullPermutation1(char *a, int size, int n){
    if (n == size-1) {
        _print((int *)a, size);
        return;
    }
    int dup[256] = {0};
    for (int i = 0; i < size; i ++) {
        if (dup[a[i] == 1]) {
            continue;
        }
        dup[a[i]] = 1;
        swap(a[i], a[n]);
        strFullPermutation1(a, size, n+1);
        swap(a[i], a[n]);
    }
}

//非递归算法
bool AllAlgorithms::getNextPermutation(int *a, int size){
    //后找
    int i = size - 2;
    while ((i >= 0) && (a[i] >= a[i+1])) {
        i --;
    }
    if (i < 0) {
        return false;
    }
    //小大
    int j = size - 1;
    while(a[j] <= a[i])
        j --;
    //交换
    swap(a[j], a[i]);
    //翻转
    reverseTwo(a+i+1, a+size-1);
    return true;
}

//翻转
void AllAlgorithms::reverseTwo(int *from, int *to){
    int t;
    while (from < to) {
        t = *from;
        *from = *to;
        *to = t;
        from ++;
        to --;
    }
}


//字符串查找问题
// 给定文本串text和模式串pattern,从文本串text中找出模 式串pattern第一次出现的位置。

//查找str中首次出现p的位置
int AllAlgorithms::bruteForceSearch(const char *str, const char *p){
    int i = 0;//当前匹配到的文本串首位
    int j = 0;//模式串的匹配位置
    int size = (int)strlen(p);
    int remindNum = (int)strlen(str) - size;
    while ((i <= remindNum) && (j < size)) {
        if (str[i+j] == p[j]) {
            j ++;//若匹配，模式串匹配位置后移
        }
        else{
            i ++;
            j = 0;//不匹配，比对下一个位置，模式串回到首位
        }
    }
    if (j >= size) {
        return i;
    }
    return -1;
}

//KMP算法求字符串匹配
//求next数组,前缀串和后缀穿的公共部分数
void AllAlgorithms::getNext(const char *p, int *next){
    int length = (int)strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < length - 1) {
        //此时，k即next[j-1],且p[k]表示前缀，p[j]表示后缀
        //注：k == -1 表示未找到k前缀与k后缀相等，首次分析可先忽略
        if (k == -1 || p[j] == p[k]) {
            ++ j;
            ++ k;
            next[j] = k;
        }
        else{//p[j]与p[k]匹配失败，则继续递归计算前缀p[next[k]]
            k = next[k];
        }
    }
}

//求next数组的改进版
void AllAlgorithms::getNext2(const char *p, int *next){
    int length = (int)strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < length - 1) {
        if (-1 == k || p[j] == p[k]) {
            ++ j;
            ++ k;
            if(p[j] == p[k])
                next[j] = next[k];
            else
                next[j] = k;
        }
        else{
            k = next[k];
        }
    }
}
int AllAlgorithms::KMPSearch(const char *text,const char *pattern,int *next,int n){
    int answer = -1;
    int i = 0,j = 0;
    int lengthPattern = (int)strlen(pattern);
    while (i < n) {
        if (-1 == j || text[i] == pattern[j]) {
            ++ i;
            ++ j;
        }
        else
            j = next[j];
        if (j == lengthPattern) {
            answer = i - lengthPattern;
            break;
        }
    }
    return answer;
}

//求最长回文子串--Manacher算法
//回文：顺着读和倒着读都一样的字符串
//回文子串的定义:
//给定字符串str,若s同时满足以下条件:
// s是str的子串
// s是回文串
// 则,s是str的回文子串。
// 该算法的要求,是求str中最长的那个回文子串。
//法1：枚举中心位置
int AllAlgorithms::longestPalindrome(const char *s, int n){
    int max,j;
    if (0 == s || n < 1) {
        return 0;
    }
    max = 0;
    
    for (int i = 0; i < n ; ++ i) {//i为回文串的中心
        for ( j = 0; ((i - j) >= 0) && ((i+j) < n); ++j) {//如果回文串的长度是奇数
            if (s[i-j] != s[i+j]) {
                break;
            }
            if ((j * 2 + 1) > max) {
                max = 2*j + 1;
                
            }
        }
        for (j = 0; ((i-j) >= 0) && ((i+j+1) < n); ++j) {//如果回文串的长度是偶数
            if (s[i-j] != s[i+j+1]) {
                break;
            }
            if ((j * 2 + 2) > max) {
                max = 2*j + 2;
                
            }

        }
    }
    return max;
    

}

void AllAlgorithms::Manacher(char *s, int *p){
    int size = (int)strlen(s);
    p[0] = 1;
    int id = 0,mx = 1;
    for (int i = 1; i < size; i ++) {
        if (mx > i) {
            p[i] = min(p[2*id - i], mx- i);
        }
        else
            p[i] = 1;
        for (; s[i+p[i]] == s[i- p[i]]; p[i] ++);
        
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
    }
    
}
//改进版
void AllAlgorithms::Manacher2(char *s, int *p)
{
    int size = (int)strlen(s);
    p[0] = 1;
    int id = 0,mx = 1;
    for (int i = 1; i < size; i++) {
        if (mx > i) {
            if (p[2*id- i] != mx- i) {
                p[i] = min(p[2*id- i], mx-i);
            }
            else{
                p[i] = p[2*id- i];
                for (; s[i+p[i]] == s[i-p[i]]; p[i] ++);
            }
        }
        else{
            p[i] = 1;
            for (; s[i+p[i]] == s[i-p[i]]; p[i] ++);
        }
        
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
    }
}



//BM算法,从尾部字符比较开始
//Boyer-Moore算法是1977年Robert S. Boyer和 J Strother Moore发明的字符串匹配算法,最 坏情况下的时间复杂度为O(N) ,在实践中 比KMP算法的实际效能高。
//BM算法不仅效率高,而且构思巧妙,容易 理解。

//求局部最大值
int AllAlgorithms::getLocalMaximum(const int *array,int n){
    int left = 0;
    int right = n - 1;
    int mid;
    while (left < right) {
        mid = (left + right) / 2;
        cout<<mid<<endl;
        if(array[mid] > array[mid + 1])
            right = mid;
        else
            left = mid + 1;
        
    }
    return array[left];
}


//找出第一个不在数组中的正整数
int AllAlgorithms::findFirstMissNumber(int *a, int size){
    a --;//第一个元素置零
//    for (int i = 0; i < size; i ++) {
//        cout<<a[i]<<endl;
//    }
    int i = 1;//从零开始数
    while (i <= size) {
        if (a[i] == i) {
            i ++;
        }
        else if ((a[i] < i) || (a[i] > size) || (a[i] == a[a[i]]))
        {
            a[i] = a[size];
            size --;
        }
        else{
            cout<<"a[i]:"<<a[i]<<endl;
            cout<<"a[a[i]]:"<<a[a[i]]<<endl;

            swap(a[a[i]], a[i]);
            cout<<"a[i]:"<<a[i]<<endl;
            cout<<"a[a[i]]:"<<a[a[i]]<<endl;
        }
    }
    return i;
    
}

//查找旋转数组的最小值
int AllAlgorithms::findRollingMin(int *a, int size){
    int low = 0;
    int high = size - 1;
    int middle;
    while (low < high) {
        middle = (high + low)/2;
        if (a[middle] < a[high]) {
            high = middle;//half-left section
        }
        else if (a[middle] > a[high])
            low = middle + 1;//half-right section
    }
    return a[low];
}

//零子数组：求对于长度为N的数组A,求连续子数组的 和最接近0的值
int AllAlgorithms::sumZeroSubArray(const int *a, int size){
    int *sum = new int[size + 1];//和
    sum[0] = 0;
    for (int i = 0; i < size; i ++) {
        sum[i+1] = sum[i] + a[i];
    }
    
    sort(sum, sum+size+1);
    int diff = abs(sum[1] - sum[0]);
    int result = diff;
    for (int i = 1; i < size; i ++) {
        diff = abs(sum[i+1] - sum[i]);
        result = min(diff, result);
    }
    delete [] sum;
    return result;
}
//返回零子数组
void AllAlgorithms::sumZeroSubArray2(const int *a, int size, int min,int &fromIdx, int &toIdx){
    if (! a || (size <= 0)) {
        fromIdx = -1;
        toIdx = -1;
    }
    vector<int> negIdx;
    for (int i = 0; i < size; i ++) {
        if(a[i] < 0)
           negIdx.push_back(i);
    }
    int n = (int)negIdx.size();
    for (int i = 0; i < n; i ++) {
        int from = negIdx[i % n];
        int to = negIdx[(i+1) % n];
        int sum = 0;
        for (int j = from; j <= to; j ++)
            sum = sum + a[j];
        if(sum  == min)
        {
            if(from < to)
            {
                fromIdx = from;
                toIdx = to;
            }
            else
            {
                swap(from, to);
                fromIdx = from;
                toIdx = to;
            }
            break;
        }
    }
    
}

//求和最大的连续子数组的和
int AllAlgorithms::sumMaxSubArray(const int *a, int size){
    if (! a || (size <= 0))
        return 0;
    int sum = a[0];//当前子串的和
    int result = sum;//当前找到的最优解
    for (int i = 1; i < size; i ++) {
        if(sum > 0)
            sum = sum + a[i];
        else
            sum = a[i];
        result = max(sum, result);
        
    }
    return result;
}
//求出最大和子数组
int AllAlgorithms::sumMaxSubArray2(const int *a, int size, int &fromIdx, int &toIdx){
    if(!a || (size <= 0))
    {
        fromIdx = toIdx = -1;
        return 0;
    }
    int sum = a[0];
    int result = sum;
    fromIdx = toIdx = 0;
    int newStart = 0;//新的子数组起点
    for (int i = 1; i < size; i ++) {
        if(sum > 0)
            sum += a[i];
        else
        {
            sum = a[i];
            newStart = i;
            
        }
        if (result < sum) {
            result = sum;
            fromIdx = newStart;
            toIdx = i;
        }
    }
    
    return result;
}

//荷兰国旗问题:red:0,white:1,blue:2

void AllAlgorithms::hollandNationalFlag(int *a, int length){
    int begin = 0;
    int current = 0;
    int end = length - 1;
    while (current <= end) {
        if (2 == a[current]) {
            swap(a[end], a[current]);
            end --;
        }
        else if (1 == a[current])
            current ++;
        else
        {
            if (begin == current) {
                begin ++;
                current ++;
            }
            else
            {
                swap(a[current], a[begin]);
                begin ++;
            }
        }
    }
}

//improvement1

void AllAlgorithms::hollandNationalFlag2(int *a, int length){
    int begin = 0;
    int end = length - 1;
    int curr = 0;
    while (curr <= end) {//until the end is recolosing to the curr
        if (1 == a[curr]) {
            curr ++;
        }
        else if (2 == a[curr]){
            swap(a[curr], a[end]);
            end --;
        }
        else{
            if (curr != begin)
                swap( a[begin], a[curr]);
            begin ++;
            curr ++;//because when begin is not equal to the curr,the begin must be equal to 1,after swapping,both begin and curr are equal to 1,hence,curr ++
        }
    }
}

//compute the max gap int an array
int AllAlgorithms::calcMaxGapOfArray(const int *a, int size){
    vector<tagSBucket> sbs;
    int sbMax = a[0];
    int sbMin = a[0];
    //find the max and min value
    for (int i = 1; i < size; i ++) {
        if(sbMax < a[i])
            sbMax = a[i];
        else if (sbMin > a[i])
            sbMin = a[i];
    }
    
    //push the data into the bucket
    int diff = sbMax - sbMin;
    int sbBucket;
    for (int i = 0; i < size; i ++) {
        sbBucket = (a[i] - sbMin) * size / diff;
        if(sbBucket >= size)
            sbBucket = size - 1;
        sbs[sbBucket].nAdd(a[i]);
    }
    //compute the gap
    int k = 0;
    
    int sbGap = diff / size;
    int gapTmp;
    for (int j = 1; j < size; j ++) {
        if (sbs[j].bValid) {
            gapTmp = sbs[j].nMin - sbs[k].nMax;
            if(sbGap < gapTmp)
                sbGap = gapTmp;
            k = j;
        }
    }
    return sbGap;
    
}





