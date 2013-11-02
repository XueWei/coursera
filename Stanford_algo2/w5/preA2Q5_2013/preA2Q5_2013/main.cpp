//
//  main.cpp
//  preA2Q5_2013
//
//  Created by Wei Xue on 11/2/13.
//  Copyright (c) 2013 Bill. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

#define INPUTFILENAME "/Users/xwei/study/course/course_algo2/w5/tsp.txt"
typedef struct
{
    float *x, *y;
    int n;
} MGraph;

MGraph  G;
int  src = 0;
float  **dp = NULL;
float  **adj = NULL;

float distance(float Ax, float Ay, float Bx, float By)
{
    return sqrt( (Ax-Bx)*(Ax-Bx) + (Ay-By)*(Ay-By) );
}

// initial status.
void preInit(int n, float **&dp)
{
    dp = new float*[1<<n];
    
    for (int i=0; i<(1<<n); i++)
        dp[i] = new float[n];
    
    for (int i=0; i<(1<<n); i++)
        for (int j=0; j<n; j++) {
            dp[i][j] = -1;
        }
    
    G.x = new float[n];
    G.y = new float[n];
}

void init(int n, float **&adj, float **dp)
{
    adj = new float*[n];
    for (int i=0; i<n; i++)
        adj[i] = new float[n];
    
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            adj[i][j] = distance(G.x[i], G.y[i], G.x[j], G.y[j]);
    
    for ( int i = 0; i < n; ++i )
		dp[ 1 << i ][ i ] = adj[ src ][ i ];
}

// TSP recursive
float TSP( int status, int x)
{
    if ( dp[ status ][ x ] != -1 )
        return dp[ status ][ x ];
    
    int newstate = status & (~(1<<x));
    dp[ status ][ x ] = 100000.0;
    for ( int i = 0; i < G.n; ++i )
        if (  (status & ( 1 << i )) && i != x)
            dp[status][x] = min(dp[status][x], TSP(newstate, i) + adj[i][x]);
    
    return dp[ status ][ x ];
}

void doA2Q5()
{
    int  i = 0;

    ifstream  inFile;
    
    inFile.open(INPUTFILENAME);
    
    inFile >> G.n;
    preInit(G.n, dp);
    while (!inFile.eof()) {
        inFile >> G.x[i] >> G.y[i];
        i++;
    }
    inFile.close();
    init(G.n, adj, dp);
    delete [] G.x;
    delete [] G.y;

	printf( "%f\n", TSP( (1 << G.n) - 1, src) );
    delete [] dp;
    delete [] adj;
}

int main(int argc, const char * argv[])
{

    doA2Q5();
    return 0;
}

