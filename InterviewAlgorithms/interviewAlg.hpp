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
    int min(int a,int b);
    
public:
    int largestRectArea(vector<int> &height);
    int gatherRain(vector<int> &A);
    void topologic(vector<vector<int>> &G ,vector<int> & inDegree,vector<int> &toposort);
    int getLongestParenthese(const char *p);
    int getLongestParenthese2(const char *p);
    int reversePolishNotation(const char **p,int size);
    bool isOperator(const char *token);
    void reverseString(string &str,int idxFrom,int idxTo);
    void leftRotateMoving(string &str,int n,int m);
    void longestCommonSequence(const char *str1,const char *str2,string &res);
    int longestIncreasingSequence(const int *p,int length,int *pre,int& nInx);
    void getLIS(const int *arr,const int *pre,int nIdx,vector<int> &list);
    void _print(int *p,int size);
    void recursionPermutation(int *a,int size,int n);
    bool isDuplicate(const int *a,int n,int t);
    void strFullPermutation(int *a,int size,int n);
    void strFullPermutation1(char *a,int size,int n);
    void reverseTwo(int *from,int *to);
    bool getNextPermutation(int *a,int size);
    int bruteForceSearch(const char *str,const char *p);
    int KMPSearch(const char *text,const char *pattern,int *next,int n);
    void getNext(const char *p,int next[]);
    void getNext2(const char *p,int next[]);
    int longestPalindrome(const char *s,int n);
    void Manacher(char *s,int *p);
    void Manacher2(char *s,int *p);
    int getLocalMaximum(const int *array,int n);
    int findFirstMissNumber(int *a,int size);
    int findRollingMin(int *a,int size);
    int sumZeroSubArray(const int *a,int size);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};


#endif /* interviewAlg_hpp */
