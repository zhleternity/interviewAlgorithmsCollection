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
#include "HLTree.hpp"

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
    const int sub1[] = {1,-4,7,2,-5,-2,3,10};
    int min2 = aa.sumZeroSubArray(sub, sizeof(sub)/sizeof(int));
    cout<<"sub:"<<min2<<endl;
    int from1,to1;
    aa.sumZeroSubArray2(sub1, sizeof(sub1)/sizeof(int), min2, from1, to1);
    cout<<"from_min:"<<from1<<","<<"to_min:"<<to1<<endl;
    int max4 = aa.sumMaxSubArray(sub, sizeof(sub)/sizeof(int));
    cout<<"max sub:"<<max4<<endl;
    int from ,to;
    int max5 = aa.sumMaxSubArray2(sub, sizeof(sub)/sizeof(int), from, to);
    cout<<"max5:"<<max5<<endl;
    cout<<"from:"<<from<<","<<"to:"<<to<<endl;
    
    int hol[] = {0,1,2,1,1,2,0,2,1,0};
    aa.hollandNationalFlag2(hol, sizeof(hol)/sizeof(int));
    for (int i = 0; i < 10; i ++) {
        cout<<hol[i];
//        cout<<endl;
    }
    
    const int buc[] = {1,7,14,9,4,13};
    int gap = aa.calcMaxGapOfArray(buc, sizeof(buc)/sizeof(int));
    cout<<"max gap:"<<gap<<endl;
    
    const int can[] = {3,4,1,2,1,0};
    int size2 = sizeof(can)/sizeof(int);
    int *origin = new int[size2];
    aa.cantorExpansion(can, origin, size2);
    aa._print(origin, size2);
    delete [] origin;
    
    int en[] = {1,2,3,4,5};
    int size3 = sizeof(en) / sizeof(int);
    int sum = 10;
    bool *x = new bool[size3];
    memset(x, 0, size3);
    aa.enumNUmber(en, x, size3, 0, 0, sum);
    delete [] x;
    
//    const char pPre[] = "GDAFEMHZ";
//    const char pMiddle[] = "ADEFGHMZ";
//    int len = sizeof(pMiddle) / sizeof(char);
//    char *pPost = new char[len];
//    int idx = 0;
//    HLBinaryTree hlbt;
//    hlbt.MiddlePre2Post(pMiddle, pPre, len, pPost, idx);
//    cout<<"post order :"<<pPost<<endl;
//    cout<<"idx:"<<idx<<endl;
    
    int fn[] = {1,2,3,4,5,6,7,8,9,10};
    int siz = sizeof(fn) / sizeof(int);
    bool *x_fn = new bool[siz];
    memset(x_fn, 0, size);
    int sum_fn = 40;
    int residue;
    aa.findNumber(fn, x_fn, 0, sum_fn, 0, residue);
    cout<<residue<<endl;
    delete [] x_fn;
    
//    char pPost[] = "AEFDHZMG";
//    char pMiddle[] = "ADEFGHMZ";
//    int size4 = sizeof(pMiddle) / sizeof(char);
//    char *pPre = new char[size4];
//    int idx = 0;
//    HLBinaryTree hlbt;
//    hlbt.MiddlePost2Pre(pMiddle, pPost, size4-1, pPre, idx);
//    pPre[size4 - 1] = 0;
//    cout<<pPre<<endl;
//    delete [] pPre;
    int merge[] = {3,56,2, 7,45, 8, 1};
    int size5 = sizeof(merge) / sizeof(int);
    aa.mergeSort(merge, 0, size5-1);
    aa._print(merge, size5);
    
    int count = 0;
    aa.mergeSortInversionNumber(merge, 0, size-1, count);
    cout<<count<<endl;
    
//    int gantt_a[] = {8,6,2,4};
//    int gantt_b[] = {3,1,3,12};
//    int size6 = sizeof(gantt_a) / sizeof(int);
//    int *gantt_c = new int[size6];
//    aa.ganttChart(gantt_a, gantt_b, gantt_c, size6);
//    aa._print(gantt_c, size6);
//    delete [] gantt_c;
    int number1,number2;
    bool flag = aa.findTwoNumberEqualToSum(merge, size5, 47, number1, number2);
    cout<<number1<<","<<number2<<endl;
    cout<<flag<<endl;
    
    
    int arr[4][MAXN] = {0};
    cout<<aa.solve1(arr[0], 100)<<endl;
    cout<<aa.solve2(arr[1], 100)<<endl;
    cout<<aa.solve3(arr[2], 100)<<endl;
    cout<<aa.solve4(arr[3], 100)<<endl;
    int ret = 0;
    for (int i = 2; i <= 100; i ++) {
        for (int j = 0; j < 4; j ++) {
            ret += arr[j][i];
        }
        if(ret % 4 != 0)
            cout<<"error! num:"<<i<<endl;
    }
    
    return 0;
}
