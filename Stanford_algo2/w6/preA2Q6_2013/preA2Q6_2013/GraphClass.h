//
//  GraphClass.h
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/23/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#ifndef __preA2Q6_2013__GraphClass__
#define __preA2Q6_2013__GraphClass__

#include <iostream>
#include <vector>
#include "GraphAdj.h"
using namespace std;



class GraphClass {
private:
    GraphAdj *adjG;
    GraphAdj *newG; //缩点后的无欢图
    
    vector<int> *contain; //新图中每个点都包含原图中的哪些点
    
    int vertexNum;    //节点个数。
    
    bool *InStack;
    
    
    //Tarjan dfs用到的变量
    int *dfn,  //深度优先搜索访问次序, 0为第一个访问的。
        *low, //能追溯到的最早的次序，也就是搜索子树的根。
        *dfnOrg;
    int cnt;  //发现节点的顺序索引
    int scnt;  //强联通分量的个数。
    int *stack, top; //堆栈,  *est, etop
    int *est, etop;
    
    int *InComponent;   //记录每个点在第几号强连通分量里
    
    void TarjanDfs(int);      //非递归
    void TarjanDfsR(int src); //递归实现
    
    
    void tsDfs(int);  //对新图拓补排序用到的函数
    void colorDfs(int);
    
    void initGraph(int num);
    void releaseGraph(int **&g);
    void copyGraph(int ** dstG, int **fromG);
    
public:
    GraphClass(int vtNum);
    ~GraphClass();
    
    void addEdgeInOrg(int start, int end);
    bool judge();
    void scR(bool isRecur);
    void mergeComponent(); //将强联通分量作为一个点构造新图
    void topologicalSort(); //拓补排序
    void color();
    void tagAnswer();
    void printAnswer();
    
    void printG();
    void printG(int **g, int(*reMap)(int));
    
    inline int getPointNum() {return vertexNum;};
    inline int * getLowPoint() {return low;};
    
};


#endif /* defined(__preA2Q6_2013__GraphClass__) */
