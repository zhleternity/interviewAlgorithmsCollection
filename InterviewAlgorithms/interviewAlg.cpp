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



int AllAlgorithms::max(int a, int b){
    return ((a+b) + abs(a-b))/2;
}
//直方图矩形最大面积
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


































