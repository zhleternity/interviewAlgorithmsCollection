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
    const char *p = "(()())";
    int total = aa.getLongestParenthese(p);
    cout<<"最长匹配长度为："<<total<<endl;
    const char *pp[] = {"4","13","5","/","+"};
    int res = aa.reversePolishNotation(pp, 5);
    cout<<"计算结果为："<<res<<endl;
    
    string str = "beautiful";
    aa.leftRotateMoving(str, 9, 3);
    cout<<str<<endl;
    
    const char *str1 = "ABCBDAB";
    const char *str2 = "BDCABA";
    string res2;
    aa.longestCommonSequence(str1, str2, res2);
    cout<<"LCS："<<res2<<endl;
    
    int array[] = {1,4,5,6,2,3,8,9,10,11,12,12,1};
    int size = sizeof(array) / sizeof(int);
    int *pre = new int[size];
    int nIdx;
    int max = aa.longestIncreasingSequence(array, size, pre, nIdx);
    cout<<"LIS:"<<max<<endl;
    vector<int> list;
    aa.getLIS(array, pre, nIdx, list);
    delete [] pre;
    aa._print(&list.front(), (int)list.size());
    
    int a[] = {1,2,3,4};
    aa.recursionPermutation(a, sizeof(a)/sizeof(int), 0);
    
    int b[] = {1,2,2,3};
    int sz = sizeof(b)/sizeof(int);
    aa._print(b, sz);
    while(aa.getNextPermutation(b, sz))
        aa._print(b, sz);
    
    const char *text = "ABCDBABCA";
    const char *pattern = "BAB";
    int x1 = aa.bruteForceSearch(text, pattern);
    cout<<"暴力求解："<<x1<<endl;
    int n = (int)strlen(text);
    int next[n+1];
    aa.getNext(pattern, next);
    cout<<"next:"<<next<<endl;
    int x2 = aa.KMPSearch(text, pattern, next, n);
    cout <<"kmp:"<<x2<<endl;
    
    const char *str3 = "12212321";
    int max2 = aa.longestPalindrome(str3, (int)strlen(str3));
    cout<<"plaindrome:"<<max2<<endl;
    
    char *str4 = "12212321";
    int P[9];
    aa.Manacher2(str4, P);
    for (int i = 0; i < 9; i ++) {
        cout<<"Manacher:"<<P[i]<<endl;
    }
    
    
    const int in[8] = {1,8,4,3,9,0,3,4};
    int max3 = aa.getLocalMaximum(in, 8);
    cout<<"local max:"<<in[max3]<<endl;
    int c[] = {3,5,1,2,-3,7,4,8};
    int m = aa.findFirstMissNumber(c, sizeof(c)/sizeof(int));
    cout<<"miss number:"<<m<<endl;
    
    int roll[] = {4,6,7,0,2,3};
    int min1 = aa.findRollingMin(roll, sizeof(roll)/sizeof(int));
    cout<<"rolling array:"<<min1<<endl;
    
    const int sub[] = {1,-2,3,10,-4,7,2,-5};
    int min2 = aa.sumZeroSubArray(sub, sizeof(sub)/sizeof(int));
    cout<<"sub:"<<min2<<endl;
    const int sub2[] = {1,-2,3,10,-4,7,2,-5};
    int max4 = aa.sumMaxSubArray(sub2, sizeof(sub2)/sizeof(int));
    cout<<"max sub:"<<max4<<endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
