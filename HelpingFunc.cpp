#ifndef HELPINGFUNC_H
#define HELPINGFUNC_H

#include <iostream>
#include <time.h>
#include <vector>
#include <tuple>

using namespace std;

int N;
void input()
{
    cin>>N;
}

void printTable(int* queens)
{
    char table[N][N];
    for(int i=0; i<N; i++)
        table[queens[i]][i]='*';

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(table[i][j]!='*')
                cout<<"- ";
            else
                cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }
}

/*
    set conflicts in the 3 arrays for queensInitlized queens.
    @queensInitialized <= N(the maximum number of queens)
*/
void setConflictsForTable(int* queens,int* rows,int* mainDiags,int* secDiags,int queensInitialized = N)
{
    for( int i = 0; i < queensInitialized; i++ ) /// queens; each column contains one queen
    {
        rows[queens[i]]++;
        mainDiags[queens[i] - i + N - 1]++;//this formula generate indexes from 0 to N-1 and we use these as indexes in the array, so we don't make gaps in the array indexes
        secDiags[queens[i] + i]++;//analogically
    }

}

/*
    Calculate the number of conflicts for a table.If table has 0 conflicts the NQueens problem is solved
*/
int getConflictsNumber(int* queens,int* rows,int* mainDiags,int* secDiags)
{
    int conflictRows = 0;
    for(int i=0; i<N; i++)
        conflictRows+=rows[i]*(rows[i]-1);

    int conflictMainDiag=0;
    int conflictSecDiag=0;
    for(int i=0; i<N*2-1; i++)
    {
        conflictMainDiag+=mainDiags[i]*(mainDiags[i]-1);
        conflictSecDiag+=secDiags[i]*(secDiags[i]-1);
    }

    return conflictRows+conflictMainDiag+conflictSecDiag;
}

/*
find minimum conflicted place for the given queen .It's randomized if we have 2 possible places it will chose randomly 1 of them
*/
int findMinConflictedPositionForAQueen(int* queens,int* rows,int* mainDiags,int* secDiags,int col)
{
    vector<int> posiblePositions;
    int minConflicts=999999;//infinite
    for(int i=0; i<N; i++)
    {
        int currConflicts=0;
        if(rows[i]>0)
            currConflicts+=rows[i];

        if(mainDiags[i-col+N-1]>0)
            currConflicts+=mainDiags[i-col+N-1];

        if(secDiags[i+col]>0)
            currConflicts+=secDiags[i+col];

        if(minConflicts>currConflicts)
        {
            posiblePositions.clear();
            posiblePositions.push_back(i);
            minConflicts=currConflicts;
        }
        else if(minConflicts == currConflicts)
        {
            posiblePositions.push_back(i);
        }
    }
    return posiblePositions[rand()%(posiblePositions.size())];

}

/*
    initialize iterative the queens on the desk.It's optimized to find the minimum conflicted position for every queen
*/
void initQueens(int* queens)
{
    queens[0]=rand()%N;
    for(int i=1; i<N; i++)
    {
        int rows[N]= {0};
        int mainDiags[N*2-1]= {0};
        int secDiags[N*2-1]= {0};

        setConflictsForTable(queens,rows,mainDiags,secDiags,i);
        queens[i] = findMinConflictedPositionForAQueen(queens,rows,mainDiags,secDiags,i);
    }
}
/*
    this function find the queen with maximum conflicts
    it returns a pair (x,y) where x is the row and y is the column of the queen
    it's also randomized
*/
tuple<int,int> findQueenWithMaxConflicts(int* queens,int* rows,int* mainDiags,int* secDiags)
{
    vector<tuple<int,int>> queensWithMaxConflicts;
    int maxConflicts = -1;
    for(int i=0; i<N; i++)
    {
        int currConflicts=0;
        currConflicts+=rows[queens[i]];
        currConflicts+=mainDiags[queens[i]-i+N-1];
        currConflicts+=secDiags[queens[i]+i];

        if(maxConflicts < currConflicts)
        {
            queensWithMaxConflicts.clear();
            tuple<int,int> queen(queens[i],i);
            queensWithMaxConflicts.push_back(queen);
            maxConflicts=currConflicts;
        }
        else if(maxConflicts == currConflicts)
        {
            tuple<int,int> queen(queens[i],i);
            queensWithMaxConflicts.push_back(queen);
        }
    }
    return queensWithMaxConflicts[rand()%(queensWithMaxConflicts.size())];
}
/*
calculate the new conflicts of the queens
*/
void changeConflicts(int* rows,int* mainDiags,int* secDiags,tuple<int,int> queen,int newRow)
{
    rows[get<0>(queen)]--;
    rows[newRow]++;

    mainDiags[get<0>(queen) - get<1>(queen) + N - 1]--;
    mainDiags[newRow - get<1>(queen) + N - 1]++;

    secDiags[get<0>(queen) + get<1>(queen)]--;
    secDiags[newRow + get<1>(queen)]++;

    return;
}
#endif // HELPINGFUNC_
