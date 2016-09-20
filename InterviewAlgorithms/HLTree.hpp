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

typedef void(*Visit) (int value);

class HLBinaryTree{
private:
    MYTreeNode *pRoot;
    //destroy
    void destroy(MYTreeNode *pRoot);
    //insert
    bool insert(MYTreeNode *&pRoot,int value);//recursion
    bool insertNot(int value);//non recursion
    //pre order visit
    void preOrder(MYTreeNode *pRoot,Visit visit) const;
    void preOrderNot(Visit visit) const;
    //middle order visit
    void middleOrder(MYTreeNode *pRoot,Visit visit) const;
    void middleOrderNot1(Visit visit) const;
    void middleOrderNot2(Visit visit) const;
    //post order visit
    void postOrder(MYTreeNode *pRoot,Visit visit) const;
    void postOrderNot(Visit visit) const;
    //delete
    void deleteChildless(MYTreeNode *pParent,MYTreeNode *pNode);//pNode无子
    void deleteSingleSon(MYTreeNode *pParent,MYTreeNode *pNode);//pNode是pParent唯一子节点
    
public:
    HLBinaryTree();
    ~ HLBinaryTree();
    bool Insert1(int value);
    bool Insert2(int value);
    bool Delete(int value);
    MYTreeNode* Find(int value) const;
    void PreOrder(Visit visit) const;
    void MiddleOrder(Visit visit) const;
    void PostOrder(Visit visit) const;
    void MiddlePre2Post(const char *pMiddle,const char *pPre,int length,char *pPost,int &idx);
    void MiddlePost2Pre(const char *pMiddle, const char *pPost, int length, char *pPre, int &idx);
    bool canPostOrder(const int *a, int size);
    
};

#endif /* HLTree_hpp */
