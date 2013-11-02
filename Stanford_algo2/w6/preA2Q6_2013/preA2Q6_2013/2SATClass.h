//
//  2SATClass.h
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/23/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#ifndef __preA2Q6_2013___SATClass__
#define __preA2Q6_2013___SATClass__

#include <iostream>
#include <fstream>
#include "GraphClass.h"
using namespace std;

class SATClass {

private:
    GraphClass  *g;
    int  m;  //conflict pair number
    int  n;  //element nummber.
    
    int  mapVForA2Q6(int org) ;
    int  demapVForA2Q6(int org) ;

    bool buildMap(const char * fileName);
    void printOneAnwser();
    
public:
    SATClass(const char* inputFileName);
    
    bool judge();
    bool solve2SAT(bool isRecur);
    void getOneAnswer();
};

#endif /* defined(__preA2Q6_2013___SATClass__) */
