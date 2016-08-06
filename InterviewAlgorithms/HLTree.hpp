//
//  HLTree.hpp
//  InterviewAlgorithms
//
//  Created by lingLong on 16/8/6.
//  Copyright © 2016年 ling. All rights reserved.
//

#ifndef HLTree_hpp
#define HLTree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>


//树的基本操作
//插入、删除、查找、前序遍历、中序遍历、后序遍历

typedef struct HLTreeNode{
    int value;
    HLTreeNode *pLeft;
    HLTreeNode *pRight;
    HLTreeNode(int v) : value(v),pLeft(NULL),pRight(NULL) {}
}MYTreeNode;

#endif /* HLTree_hpp */
