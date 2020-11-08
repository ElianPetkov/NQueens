#include "HelpingFunc.cpp"

using namespace std;

int solution(int* queens,int* rows,int* mainDiags,int* secDiags,int iter=0)
{
    if(iter > 2*N)
        return 0;

    int conflicts = getConflictsNumber(queens,rows,mainDiags,secDiags);
    if(conflicts==0)
    {
        printTable(queens);
        return 1;
    }

    tuple<int,int> queen= findQueenWithMaxConflicts(queens,rows,mainDiags,secDiags);
    int newQueenRow = findMinConflictedPositionForAQueen(queens,rows,mainDiags,secDiags,get<1>(queen));

    queens[get<1>(queen)]=newQueenRow;
    changeConflicts(rows,mainDiags,secDiags,queen,newQueenRow);

    iter++;
    solution(queens,rows,mainDiags,secDiags,iter);

}
int startGame()
{
    if( N <= 3 )
    {
        cout<<"No solution for table with size: "<<N;
        return 0 ;
    }

    int queens[N];
    initQueens(queens);

    int* rows=new int[N] {0};
    int* mainDiags=new int[2*N - 1] {0};
    int* secDiags=new int[2*N - 1] {0};
    setConflictsForTable(queens,rows,mainDiags,secDiags);

    if(solution(queens,rows,mainDiags,secDiags))
    {
        delete [] rows;
        delete [] mainDiags;
        delete [] secDiags;
        return 1;
    }
    else
    {
        startGame();
    }

    return 0;
}

int main()
{
    srand (time(NULL));
    input();
    startGame();


}
