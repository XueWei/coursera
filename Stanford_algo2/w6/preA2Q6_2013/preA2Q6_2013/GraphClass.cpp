//
//  GraphClass.cpp
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/23/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#include "GraphClass.h"

GraphClass::GraphClass(int vtNum)
{
    vertexNum = vtNum;
    adjG = new GraphAdj(vtNum);
    
    InStack = new bool[vtNum];
    for (int i=0; i<vtNum; i++) {
        InStack[i] = false;
    }
    
    stack = new int[vtNum];
    memset(stack, -1, sizeof(int)*vtNum);
    est = new int[vtNum];
    memset(est, -1, sizeof(int)*vtNum);
    dfn = new int[vtNum];
    memset(dfn, -1, sizeof(int)*vtNum);
    low = new int[vtNum];
    memset(low, -1, sizeof(int)*vtNum);
    dfnOrg = new int[vtNum];
    memset(dfnOrg, -1, sizeof(int)*vtNum);
    
    InComponent = new int[vtNum];
    memset(InComponent, -1, sizeof(int)*vtNum);
}

GraphClass::~GraphClass()
{
    delete adjG;
    delete newG;
    delete [] dfn;
    delete [] low;
    delete [] InComponent;
    delete [] InStack;
    delete [] stack;
    delete [] est;
    delete [] dfnOrg;
}

void GraphClass::addEdgeInOrg(int start, int end)
{
    adjG->pushEdge(start, end);
}

void GraphClass::copyGraph(int ** dstG, int **fromG)
{
    if (!dstG || !fromG) 
        return;
}

/*
 * Tarjan Implement.
 */
void GraphClass::TarjanDfsR(int src)
{
    int j;
    dfn[src] = low[src] = cnt++;
    InStack[src] = true;
    stack[++top] = src;
    
    int edge = adjG->getAdjLinkSize(src);
    
    
    for (; edge>0; edge--) {
        j = adjG->getEndPointByEdge(src, edge);
        if (dfn[j] == -1) {
            TarjanDfsR(j);
            low[src] = min(low[src], low[j]);
        } else if (InStack[j]) {
            low[src] = min(low[src], dfn[j]);
        }
    }
    
    if (low[src] == dfn[src]) {
        scnt++;
        do {
            j = stack[top--];
            InStack[j] = false;
            InComponent[j] = scnt;
        } while (j!=src);
    }
}

void GraphClass::TarjanDfs(int src)
{
    top = etop= 0;
    stack[top++] = src;
    
    while (top != 0) {
        int u = stack[top-1];
        if (dfn[u] == -1) {
            dfnOrg[u] = dfn[u] = low[u] = cnt++;
            est[etop++] = u;
        }
        
        int edge = adjG->getAdjLinkSize(u);
        for (; edge>0; edge--) {
            int  v = adjG->getEndPointByEdge(u, edge);
            if (dfn[v] == -1) {
                stack[top++] = v;
                break;
            }
            low[u] = min(low[u], low[v]);
        }
        if (edge > 0)
            continue;
        
        top--;
        if(dfn[u] != low[u]) {
            low[u] = min(dfn[u], low[u]);
            continue;
        }
        
        // 此时出栈的是搜索树的根节点c.
        int k;
        do {
            k = est[--etop];
            InComponent[k] = scnt;
            low[k] = vertexNum;
        } while(k != u);
        scnt++;

    }
    
}

void GraphClass::scR(bool isRecur)
{
    cnt = scnt = 0;
    for (int i=0; i<vertexNum; i++)
        if (dfn[i] == -1)
            isRecur ? TarjanDfsR(i) : TarjanDfs(i);
    
    // 统计每个强联通分量都包含哪些点
    contain = new vector<int>[scnt];
    for (int i=0; i<scnt; i++)
        contain[i].clear();
    for (int i = 0; i<vertexNum; i++) {
        contain[InComponent[i]].push_back(i);
    }
}


bool GraphClass::judge()
{
    for (int i=0; i<vertexNum; i+=2)
        if (InComponent[i] == InComponent[i+1]) {
            return false;
        }
    return true;
}

void GraphClass::mergeComponent()
{
    newG = new GraphAdj(scnt);
    
    for (int i=0; i<vertexNum; i++)
        for (int j = 0; j < adjG->getAdjLinkSize(j); j++) {
            int a = InComponent[i];
            int b = InComponent[adjG->getEndPointByEdge(i, j)];
            if (a!=b) {
                newG->pushEdge(b, a);
            }
        }
}
 
void GraphClass::tsDfs(int k)
{
    dfnOrg[k]=cnt++;
    for (int i=0; i<newG->getAdjLinkSize(k); i++) {
        int  w = newG->getEndPointByEdge(k, i);
        if (dfnOrg[w]==-1) {
            tsDfs(w);
        }
    }
    low[scnt++]=k;
}

/*
 * 函数topologicalSort和tsDfs是对新图进行拓扑排序，排序后的结果存在low数组中
 */
void GraphClass::topologicalSort()
{
    for (int i=0; i<scnt; i++) {
        dfnOrg[i]=-1;
        low[i]=-1;
    }
    int nn=scnt;
    cnt=scnt=0;
    for (int i=0; i<nn; i++) {
        if (dfnOrg[i]==-1)
            tsDfs(i);
    }
}

void GraphClass::colorDfs(int k)
{
    dfnOrg[k]=2;
    for (int i=0; i<newG->getAdjLinkSize(k); i++) {
        int  w = newG->getEndPointByEdge(k, i);
        if (dfnOrg[w]==-1) {
            colorDfs(w);
        }
    }
}

/*
 * 函数color和colorDfs是对新图进行着色，新图中着色为1的点组成一组可行解
 */
void GraphClass::color()
{
    for (int i=0; i<scnt; i++)
        dfnOrg[i]=-1;
    
    for (int i=scnt-1; i>=0; i--)
        if (dfnOrg[low[i]]==-1)
        {
            /*
             * 新图中low[i]着色为1后，它的矛盾点应标记为2
             */
            int a=contain[low[i]][0];
            //在原图中找一点属于强连通分量low[i]的点a，点a所属组的另一点b所属的强连通分量id[b]一定是low[i]矛盾点。
            int b;
            if (a%2==0)
                b=a+1;
            else
                b=a-1;
            dfnOrg[low[i]]=1;
            if (dfnOrg[InComponent[b]]==-1)
                colorDfs(InComponent[b]);    //由于依赖关系，有id[b]能达的点都是low[i]的矛盾点
        }
}

/*
 * 函数tagAnswer由新图对原图的点进行标记，得到原图的可行解
 */
void GraphClass::tagAnswer()
{
    for (int i=0; i<vertexNum; i++)
        low[i]=-1;
    for (int i=0;i<scnt;i++)
        if (dfnOrg[i]==1) {
            //i为新图中可行解包含的点，那么原图中强连通分量属于i的点都是原图中可行解的点
            for (int j=0;j<contain[i].size();j++)
                low[contain[i][j]]=1;
        }
 

}

/*
 * 函数printAnswer打印原图的可行解
 */
void GraphClass::printAnswer()
{
    for (int i=0,j=0; i<vertexNum; i++,j++)
        if (low[i]==1) {
            printf("%d",i);
            if (j != vertexNum/2-1)
                printf(" ");
            else
                printf("\n");
        }
}
