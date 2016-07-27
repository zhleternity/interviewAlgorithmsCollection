//
//  interviewAlg.hpp
//  InterviewAlgorithms
//
//  Created by lingLong on 16/7/26.
//  Copyright © 2016年 ling. All rights reserved.
//

#ifndef interviewAlg_hpp
#define interviewAlg_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class AllAlgorithms{
private:
    
    int max(int a,int b);
public:
    int largestRectArea(vector<int> &height);
    int gatherRain(vector<int> &A);
    void topologic(vector<vector<int>> &G ,vector<int> & inDegree,vector<int> &toposort);
    int getLongestParenthese(const char *p);
};

#endif /* interviewAlg_hpp */
