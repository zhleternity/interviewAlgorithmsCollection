//
//  main.cpp
//  InterviewAlgorithms
//
//  Created by lingLong on 16/7/26.
//  Copyright © 2016年 ling. All rights reserved.
//

#include <iostream>
#include <vector>
#include "interviewAlg.hpp"

using namespace std;

int main() {
    vector<int> height;
    height.push_back(2);
    height.push_back(7);
    height.push_back(5);
    height.push_back(6);
    height.push_back(4);
    AllAlgorithms aa;
    int area = aa.largestRectArea(height);
    cout<<"最大矩形面积为："<<area<<endl;
    int vol = aa.gatherRain(height);
    cout<<"收集的雨水最多为："<<vol<<endl;
    return 0;
}
