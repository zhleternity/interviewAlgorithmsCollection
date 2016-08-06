//
//  HLTree.cpp
//  InterviewAlgorithms
//
//  Created by lingLong on 16/8/6.
//  Copyright © 2016年 ling. All rights reserved.
//

#include "HLTree.hpp"
#include <stack>
#include <queue>
#include <algorithm>


//二分查找
MYTreeNode* HLBinaryTree::Find(int value) const{
    if(!pRoot)
        return NULL;
    MYTreeNode *pNode = pRoot;
    while (pNode) {
        if(value < pNode -> value)
            pNode = pNode -> pLeft;
        else if (value > pNode -> value)
            pNode = pNode -> pRight;
        else
            return pNode;
    }
    return NULL;
}

//insert
bool HLBinaryTree::Insert1(int value){
    return insert(pRoot, value);
}

bool HLBinaryTree::Insert2(int value){
    return insertNot(value);
}

bool HLBinaryTree::insert(MYTreeNode *&pRoot, int value){
    if (!pRoot) {
        pRoot = new MYTreeNode(value);
        return true;
    }
    if(value < pRoot -> value)
        return insert(pRoot -> pLeft, value);
    if(value > pRoot -> value)
        return insert(pRoot -> pRight, value);
    return false;
}

bool HLBinaryTree::insertNot(int value)
{
    if (!pRoot) {
        pRoot = new MYTreeNode(value);
        return true;
    }
    MYTreeNode *pNode = pRoot;
    MYTreeNode *pCurr = pRoot;
    while (pNode) {
        pCurr = pNode;
        if(value < pNode -> value)
            pNode = pNode -> pLeft;
        else if(value > pNode -> value)
            pNode = pNode -> pRight;
        else
            return false;
        
    }
    if(value < pCurr -> value)
        pCurr -> pLeft = new MYTreeNode(value);
    else if (value > pCurr -> value)
        pCurr -> pRight = new MYTreeNode(value);
    return true;
}

//delete
void HLBinaryTree::delteChildless(MYTreeNode *pParent, MYTreeNode *pNode){
    if(pNode == pRoot)
        pRoot = NULL;
    else if (pParent -> pLeft == pNode)
        pParent = NULL;
    else
        pParent -> pRight = NULL;
    delete pNode;
}


void HLBinaryTree::deleteSingleSon(MYTreeNode *pParent, MYTreeNode *pNode){
    MYTreeNode *pGrandSon = pNode -> pLeft ? pNode -> pLeft : pNode -> pRight;
    if(pNode == pRoot)
        pRoot = pGrandSon;
    else if (pParent -> pLeft == pNode)
        pParent -> pLeft = pGrandSon;
    else
        pParent -> pRight = pGrandSon;
    delete pNode;
}

bool 





























