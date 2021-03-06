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


using namespace std;


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
void HLBinaryTree::deleteChildless(MYTreeNode *pParent, MYTreeNode *pNode){
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

bool HLBinaryTree::Delete(int value){
    if(!pRoot)
        return false;
    MYTreeNode *pNode = pRoot;
    MYTreeNode *pParent = NULL;
    while (pNode) {
        if (value < pNode -> value) {
            pParent = pNode;
            pNode = pNode -> pLeft;
        }
        else if (value > pNode -> value)
        {
            pParent = pNode;
            pNode = pNode -> pRight;
        }
        else//找到待删除值
            break;
    }
    if(!pNode)//没有找到
        return false;
    if(! pNode -> pLeft && !pNode -> pRight)
        deleteChildless(pParent, pNode);
    else if (!pNode -> pLeft || !pNode -> pRight)
        deleteSingleSon(pParent, pNode);
    else
    {
        MYTreeNode *pCurr = pNode;//暂存待删除节点
        pParent = pNode;
        pNode = pNode -> pLeft;
        while (pNode -> pRight) {
            pParent = pNode;
            pNode = pNode -> pRight;
        }
        pCurr -> value = pNode -> value;//删除数据
        if(!pNode -> pLeft)//左孩子空
            deleteChildless(pParent, pNode);
        else
            deleteSingleSon(pParent, pNode);
        
    }
    return true;

}

//pre order visit

void HLBinaryTree::PreOrder(Visit visit)const{
    preOrderNot(visit);
}

void HLBinaryTree::preOrder(MYTreeNode *pRoot, Visit visit) const
{
    if (pRoot) {
        visit(pRoot -> value);
        preOrder(pRoot -> pLeft, visit);
        preOrder(pRoot -> pRight, visit);
        
    }
}

void HLBinaryTree::preOrderNot(Visit visit)const
{
    if(!pRoot)
        return;
    stack<MYTreeNode*> s;
    s.push(pRoot);
    MYTreeNode *pCurr;
    while (! s.empty()) {
        pCurr = s.top();
        s.pop();
        visit(pCurr -> value);
        if(pCurr -> pRight)
            s.push(pCurr -> pRight);
        else if (pCurr -> pLeft)
            s.push(pCurr -> pLeft);
    }
}

//middle order visit
void HLBinaryTree::MiddleOrder(Visit visit)const
{
    middleOrder(pRoot,visit);
}

void HLBinaryTree::middleOrder(MYTreeNode *pRoot, Visit visit) const{
    if (pRoot) {
        middleOrder(pRoot->pLeft, visit);
        visit(pRoot->value);
        middleOrder(pRoot->pRight, visit);
    }
}

void HLBinaryTree::middleOrderNot1(Visit visit)const{
    stack<MYTreeNode *> s;
    MYTreeNode *pCurr = pRoot;
    while (pCurr || !s.empty()) {
        while (pCurr) {//找最左孩子
            s.push(pCurr -> pLeft);
            pCurr = pCurr -> pLeft;
        }
        
        if (! s.empty()) {
            pCurr = s.top();//访问左孩子为空的节点
            s.pop();
            visit(pCurr -> value);
            pCurr = pCurr -> pRight;//转向右孩子
        }
    }
}

void HLBinaryTree::middleOrderNot2(Visit visit)const{
    if(!pRoot)
        return;
    stack<pair<MYTreeNode *, int>> s;
    s.push(make_pair(pRoot, 0));
    int times;
    MYTreeNode *pCurr;
    
    while (!s.empty()) {
        pCurr = s.top().first;
        times = s.top().second;
        s.pop();
        if (! times) {//第一次压栈
            if(pCurr ->pRight)
                s.push(make_pair(pCurr->pRight, 0));
            s.push(make_pair(pCurr, 1));//第二次压栈
            if (pCurr -> pLeft)
                s.push(make_pair(pCurr->pLeft, 0));
                
                
        }
        else
            visit(pCurr -> value);
    }
}


//post order visit
void HLBinaryTree::PostOrder(Visit visit)const{
    postOrder(pRoot, visit);
}

void HLBinaryTree::postOrder(MYTreeNode *pRoot, Visit visit) const
{
    if (pRoot) {
        postOrder(pRoot->pLeft, visit);
        postOrder(pRoot->pRight, visit);
        visit(pRoot->value);
    }
}

void HLBinaryTree::postOrderNot(Visit visit)const{
    if(!pRoot)
        return;
    
    stack<pair<MYTreeNode *, int>> s;
    s.push(make_pair(pRoot, 0));
    int times;
    MYTreeNode *pCurr;
    while (!s.empty()) {
        pCurr = s.top().first;
        times = s.top().second;
        s.pop();
        if (0 == times) {
            s.push(make_pair(pCurr, 1));
            if(pCurr -> pRight)
                s.push(make_pair(pCurr -> pRight, 0));
            if(pCurr -> pLeft)
                s.push(make_pair(pCurr -> pLeft, 0));
        }
        else
            visit(pCurr -> value);
    }
}

//given the middle and pre order , solve the post order
void HLBinaryTree::MiddlePre2Post(const char *pMiddle, const char *pPre, int length, char *pPost, int &idx){
    if(length <= 0)
        return ;
    if (1 == length) {
        pPost[idx] = *pPre;
        idx ++;
        return;
    }
    
    char root = *pPre;
    int nRoot = 0;
    for (; nRoot < length; nRoot ++) {
        if(pMiddle[nRoot] == root)
            break;
    }
    
    MiddlePre2Post(pMiddle, pPre + 1, nRoot, pPost, idx);
    MiddlePre2Post(pMiddle + nRoot + 1, pPre + nRoot + 1, length - nRoot - 1, pPost, idx);
    pPost[idx] = root;
    idx ++;
}

//givern the middle and post order, solve the pre order.
void HLBinaryTree::MiddlePost2Pre(const char *pMiddle, const char *pPost, int length, char *pPre, int &idx){
    if(length <= 0)
        return ;
    if (1 == length) {
        pPre[idx] = *pPost;
        idx ++;
        return;
    }
    
    char root = pPost[length + 1];
    pPre[idx] = root;
    idx ++;
    int nRoot = 0;
    for (; nRoot < length; nRoot ++) {
        if(pMiddle[nRoot] == root)
            break;
    }
    
    MiddlePost2Pre(pMiddle, pPost, nRoot, pPre, idx);
    MiddlePost2Pre(pMiddle+nRoot+1, pPost+nRoot, length -(nRoot+1), pPre, idx);
}

//determine whether can post order visit
bool HLBinaryTree::canPostOrder(const int *a, int size){
    if(size <= 1)
        return true;
    
    int root = a[size-1];
    int n_left = 0;
    while (n_left < size - 1) {
        if(a[n_left] > root)
            break;
        n_left ++;
    }
    
    int n_right = size - 2;//size-1 is root
    while (n_right >= 0) {
        if(a[n_right] < root)
            break;
        n_right --;
    }
    if(n_right != n_left - 1)
        return false;//can not partion into two sections by root
    return canPostOrder(a, n_left) && canPostOrder(a + n_left, size - n_left + 1);
    
}


//平衡二叉树*********************************
//*****************************************

//左左情况下的旋转
template <typename T>
void cBalanceTree<T>::singRorateLeft(TreeNode<T>* &k2) {
    TreeNode<T>* k1;
    k1 = k2 -> lson;
    k2 -> lson = k1 -> rson;
    k1 -> rson = k2;
//    k2 -> hight = 
}



