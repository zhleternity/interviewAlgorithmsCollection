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






























