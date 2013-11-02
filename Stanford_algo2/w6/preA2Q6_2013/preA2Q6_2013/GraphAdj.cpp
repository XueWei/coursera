//
//  GraphAdj.cpp
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/26/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#include "GraphAdj.h"

GraphAdj::GraphAdj(int num): n(num)
{
    adjG = new int*[num];
    for (int i=0; i<num; i++) {
        adjG[i] = new int[STEP];
        adjG[i][0] = i;
    }
    
    adjIndex = new int[num];
    memset(adjIndex, 0, sizeof(int) * num);
    
    times = new int[num];
    for (int i=0; i<num; i++) {
        times[i] = 1;
    }
}

GraphAdj::~GraphAdj()
{
    if (adjG!=NULL) {
        for (int i=0; i<n; i++) {
            delete adjG[i];
        }
        delete [] adjG;
    }
    
    delete [] adjIndex;
    delete [] times;
}


void GraphAdj::pushEdge(int start, int end)
{
    adjIndex[start]++;
    
    if (adjIndex[start] >= times[start] * STEP) {
        int *tmp = new int[STEP * (times[start])];
        for (int i=0; i < STEP * (times[start]); i++)
            tmp[i] = adjG[start][i];
        delete [] adjG[start];
        
        adjG[start] = new int[STEP * (++times[start])];
        for (int i=0; i < STEP * (times[start]-1); i++)
            adjG[start][i] = tmp[i];
        delete [] tmp;
    }
    adjG[start][adjIndex[start]] = end;
}

void GraphAdj::printG()
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<=adjIndex[i]; j++)
            printf("%d  ", (adjG[i][j]) );
        printf("\n");
    }
}




