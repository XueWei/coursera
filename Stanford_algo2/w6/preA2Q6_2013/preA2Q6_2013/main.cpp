//
//  main.cpp
//  preA2Q6_2013
//
//  Created by Wei Xue on 10/23/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#include <iostream>
#include "2SATClass.h"

#define CASEPATH "/Users/xwei/study/course/course_algo2/w6/"

void doA2Q6()
{
    int  fileNum = 6;
    char result[7];
    memset(result, 0, sizeof(result));
    for (int i=1; i<=fileNum; i++) {
        char fileName[128];
        sprintf(fileName, "%s2sat%d.txt", CASEPATH, i);
        SATClass sat(fileName);
        sat.solve2SAT(false) ? result[i-1] = '1' : result[i-1] = '0';
    }
    cout << result << endl;
}

int main(int argc, const char * argv[])
{
    doA2Q6();
    return 0;
}

