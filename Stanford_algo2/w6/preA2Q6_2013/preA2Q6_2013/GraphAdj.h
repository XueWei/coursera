//
//  GraphAdj.h
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/26/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#ifndef __preA2Q6_2013__GraphAdj__
#define __preA2Q6_2013__GraphAdj__

#include <iostream>

#define STEP 4
class GraphAdj {
private:
    int n; //point number;
    int *times;
    
public:
    GraphAdj(int num);
    ~GraphAdj();
    
    int ** adjG;
    int *adjIndex;
    
    void pushEdge(int start, int end);
    int getAdjLinkSize(int point) {return adjIndex[point];} ;
    int getPointNum() {return n;} ;
    int getEndPointByEdge(int start, int edge) {return adjG[start][edge];};
    void printG();
};

#endif /* defined(__preA2Q6_2013__GraphAdj__) */
