#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 5
int Table[N][N];
int K = 1;
int Max;


void ShowTable()
{
    printf("=========2 0 4 8========\n");
    for (int i = 1; i <= 4; ++i) {
        printf("|___________________|\n");
        printf("|");
        for (int j = 1; j <= 4; ++j) {
            printf("%-4d", Table[i][j]);
            if (j!=4) printf("|");
        }
        printf("|\n");
    }
    printf("|-------------------|\n");
}

void init()
{
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            Table[i][j] = 0;
        }
    }
    srand( (unsigned)time( NULL ) );
    int m=rand()%4+1;
    int n=rand()%4+1;
    int p=rand()%4+1;
    int q=rand()%4+1;
    Table[m][n] = Table[p][q] = 2;
}

int IfValid(int x)
{
    int flag = 0;
    for (int i = 1; i <= 11; ++i) {
        if (x == pow(2, i))
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

int testUp()
{
    int flag = 0;
    for (int i = 4; i >=2 ; i--) {
        for (int j = 1; j <= 4; ++j) {
            if (IfValid(Table[i][j] + Table[i-1][j]))
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

int testDown()
{
    int flag = 0;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 4; ++j) {
            if (IfValid(Table[i][j] + Table[i+1][j]))
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

int testLeft()
{
    int flag = 0;
    for (int j = 4; j >= 2; --j) {
        for (int i = 1; i <= 4; ++i) {
            if (IfValid(Table[i][j - 1] + Table[i][j])) {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

int testRight()
{
    int flag = 0;
    for (int j = 1; j <= 3; ++j) {
        for (int i = 1; i <= 4; ++i) {
            if (IfValid(Table[i][j] + Table[i][j+1]))
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

void addNew()
{
    srand((unsigned)time(NULL));
    int cnt= 0, tag = rand()%16, p, q;
    while (tag != cnt)
    {
        for (int i = 1; i <= 4; ++i) {
            for (int j = 1; j <= 4; ++j) {
                if (Table[i][j] == 0)
                {
                    cnt ++;
                }
                if (cnt == tag)
                {
                    p = i;
                    q = j;
                    break;
                }
            }
            if (cnt == tag)
            {
                break;
            }
        }
    }
    Table[p][q] = pow(2, rand()%2+1);
}

void upMove()
{
    if (testUp())
    {
        for (int j = 1; j <= 4; ++j) {
            for (int i = 2; i <=4 ; ++i) {
                for (int k = i; k >= 2; --k) {
                    if (Table[k-1][j] == 0)
                    {
                        Table[k-1][j] = Table[k][j];
                        Table[k][j] = 0;
                    }
                }
            }
        }
        for (int j = 1; j <= 4; ++j) {
            for (int i = 2; i <= 4; ++i) {
                if (IfValid(Table[i-1][j] + Table[i][j]))
                {
                    Table[i-1][j] += Table[i][j];
                    Table[i][j] = 0;
                    Max = Max>Table[i-1][j]?Max:Table[i][j-1];
                }
            }
        }
    }
    addNew();
}



void downMove()
{
    if (testDown())
    {
        for (int j = 1; j <= 4; ++j) {
            for (int i = 3; i >= 1; --i) {
                for (int k = i; k <= 3; ++k) {
                    if (Table[k+1][j] == 0)
                    {
                        Table[k+1][j] = Table[k][j];
                        Table[k][j] = 0;
                    }
                }
            }
        }
        for (int j = 1; j <= 4; ++j) {
            for (int i = 3; i >=1 ; --i) {
                if (IfValid(Table[i][j] + Table[i+1][j]))
                {
                    Table[i+1][j] += Table[i][j];
                    Table[i][j] = 0;
                    Max = Max>Table[i+1][j]?Max:Table[i+1][j];
                }
            }

        }
        addNew();
    }
}

void leftMove()
{
    if (testLeft())
    {
        for (int i = 1; i <= 4; ++i) {
            for (int j = 2; j <= 4; ++j) {
                for (int k = j; k >= 2; --k) {
                    if (Table[i][k-1] == 0)
                    {
                        Table[i][k-1] = Table[i][k];
                        Table[i][k] = 0;
                    }
                }
            }
        }
        for (int i = 1; i <= 4; ++i) {
            for (int j = 2; j <= 4; ++j) {
                if (IfValid(Table[i][j-1] + Table[i][j]))
                {
                    Table[i][j-1] += Table[i][j];
                    Table[i][j] = 0;
                    Max = Max>Table[i][j-1]?Max:Table[i][j-1];
                }
            }
        }
        addNew();
    }
}

void rightMove()
{
    if (testRight())
    {
        for (int i = 1; i <= 4; ++i) {
            for (int j = 3; j >= 1; --j) {
                for (int k = j; k <= 3; ++k) {
                    if (Table[i][k+1] == 0)
                    {
                        Table[i][k+1] = Table[i][k];
                        Table[i][k] = 0;
                    }
                }
            }
        }
        for (int i = 1; i <= 4; ++i) {
            for (int j = 3; j >= 1; ++j) {
                if (IfValid(Table[i][j+1] + Table[i][j]))
                {
                    Table[i][j+1] += Table[i][j];
                    Table[i][j] = 0;
                    Max = Max>Table[i][j+1]?Max:Table[i][j+1];
                }
            }
        }
        addNew();
    }
}

int IfLose()
{
    if (testDown() + testUp() + testLeft() + testRight() == 0)
    {
        return 1;
    }
    else
        return  0;
}

int IfWin()
{
    return Max == 2048;
}

int main() {
    printf("Do you wanna play (≧∀≦)\n");
    printf("Y/N\n");
    char c;
    Max = 0;
    c = getchar();
    getchar();
    if (c == 'Y')
    {
        char dir;
        init();
        system("clear");
        ShowTable();
        while (IfLose() + IfWin() == 0)
        {
            dir = getchar();
            getchar();
            if (dir == 'a' || dir == 'd' || dir == 'w' || dir == 's')
            {
                switch(dir)
                {
                    case 'w':
                        upMove();
                        break;
                    case 's':
                        downMove();
                        break;
                    case 'a':
                        leftMove();
                        break;
                    case 'd':
                        rightMove();
                        break;
                    default:
                        break;
                }
                system("clear");
                ShowTable();
            }
            else if(dir == 'q')
            {
                break;
            }
            else
            {
                system("clear");
                ShowTable();
                printf("Uh, you push something wrong (ÒωÓױ)\n");
            }
        }
    }
    printf("see ya (｡ŐωŐฺ｡)ﾉﾞ\n");
    return 0;
}