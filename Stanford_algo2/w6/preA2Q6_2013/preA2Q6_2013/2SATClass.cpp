//
//  2SATClass.cpp
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/23/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#include "2SATClass.h"

SATClass::SATClass(const char *inputFileName)
{
    ifstream  inFile;
    inFile.open(inputFileName);
    
    inFile>>n;
    inFile.close();
    g = new GraphClass(2*n);
    buildMap(inputFileName);
}

bool SATClass::buildMap(const char * fileName)
{
    int   tmpN;
    ifstream  inFile;
    inFile.open(fileName);
    
    inFile>>tmpN;
    while(!inFile.eof()) {
        int x,y;
        inFile>>x>>y; //x，y是互斥的。x所在组的另一点为X，y所在组的另一点为Y。原图中插入边x->Y和边y->X.
        
        g->addEdgeInOrg(mapVForA2Q6(x), mapVForA2Q6(-1*y));
        g->addEdgeInOrg(mapVForA2Q6(y), mapVForA2Q6(-1*x));
        
    }
    inFile.close();
    return true;
}


int  SATClass::mapVForA2Q6(int org) {
    if (org>0) return (org-1) * 2;
    else return (org*(-2) -1);
}

int  SATClass::demapVForA2Q6(int org) {
    if (org%2) return (org/2)*(-1)-1;
    else return (org/2+1);
}

void SATClass::printOneAnwser()
{
    int vnum = g->getPointNum();
    int *low = g->getLowPoint();
    for (int i=0,j=0; i < vnum; i++,j++)
        if (low[i]==1) {
            printf("%d", demapVForA2Q6(i));
            if (j != vnum/2-1)
                printf(" ");
            else
                printf("\n");
        }
}

bool SATClass::solve2SAT(bool isRecur)
{
    g->scR(isRecur);
    if (g->judge()) {
        //printf("YES\n");
        //getOneAnswer(); //get and print one solution.
        return true;
    } else {
        //printf("NO\n");
        return false;
    }
}

void SATClass::getOneAnswer()
{
    g->mergeComponent();
    g->topologicalSort();
    g->color();
    g->tagAnswer();
    printOneAnwser();
}
