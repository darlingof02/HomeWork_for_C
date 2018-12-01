#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#define N 5
int Table[N][N];
int Max;


void ShowTable()
{
    printf("=========2 0 4 8========\n");
    int i, j;
    for (i = 1; i <= 4; ++i) {
        printf("|___________________|\n");
        printf("|");
        for (j = 1; j <= 4; ++j) {
            printf("%-4d", Table[i][j]);
            if (j!=4) printf("|");
        }
        printf("|\n");
    }
    printf("|-------------------|\n");
}

void init()
{
    int i, j;
    for (i = 1; i <= 4; ++i) {
        for (j = 1; j <= 4; ++j) {
            Table[i][j] = 0;
        }
    }
    srand( (unsigned)time( NULL ) );
    int m=rand()%4+1;
    int n=rand()%4+1;
    int p=rand()%4+1;
    int q=rand()%4+1;
    Table[m][n] = Table[p][q] = 2;
    Max = 0;
}

int IfValid(int x)
{
    int i;
    int flag = 0;
    for (i = 1; i <= 11; ++i) {
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
    int i, j;
    int flag = 0;
    for (j = 1; j <= 4; ++j) {
        for (i = 4; i >= 2; --i) {
            if (Table[i][j] && IfValid(Table[i][j] + Table[i-1][j]))
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
    int i, j;
    int flag = 0;
    for (j = 1; j <= 4; ++j) {
        for (i = 1; i <= 3; ++i) {
            if (Table[i][j] && IfValid(Table[i+1][j] + Table[i][j]))
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
    int i, j;
    int flag = 0;
    for (i = 1; i <= 4; ++i) {
        for (j = 4; j >= 2; --j) {
            if (Table[i][j] && IfValid(Table[i][j-1] + Table[i][j]))
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

int testRight()
{
    int i, j;
    int flag = 0;
    for (i = 1; i <= 4; ++i) {
        for (j = 1; j <= 3; ++j) {
            if (Table[i][j] && IfValid(Table[i][j+1] + Table[i][j]))
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
    int i, j;
    srand((unsigned)time(NULL));
    int cnt= 0, tag = rand()%16, p, q;
    while (tag != cnt)
    {
        for (i = 1; i <= 4; ++i) {
            for (j = 1; j <= 4; ++j) {
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
    int i, j, k;
    if (testUp())
    {
        for (j = 1; j <= 4; ++j) {
            for (i = 2; i <=4 ; ++i) {
                for (k = i; k >= 2; --k) {
                    if (Table[k-1][j] == 0)
                    {
                        Table[k-1][j] = Table[k][j];
                        Table[k][j] = 0;
                    }
                }
            }
        }
        for (j = 1; j <= 4; ++j) {
            for (i = 2; i <= 4; ++i) {
                if (IfValid(Table[i-1][j] + Table[i][j]))
                {
                    Table[i-1][j] += Table[i][j];
                    Table[i][j] = 0;
                    Max = Max>Table[i-1][j]?Max:Table[i-1][j];
                }
            }
        }
        addNew();
    }
}



void downMove()
{
    int i, j, k;
    if (testDown())
    {
        for (j = 1; j <= 4; ++j) {
            for (i = 3; i >= 1; --i) {
                for (k = i; k <= 3; ++k) {
                    if (Table[k+1][j] == 0)
                    {
                        Table[k+1][j] = Table[k][j];
                        Table[k][j] = 0;
                    }
                }
            }
        }
        for (j = 1; j <= 4; ++j) {
            for (i = 3; i >=1 ; --i) {
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
    int i, j, k;
    if (testLeft())
    {
        for (i = 1; i <= 4; ++i) {
            for (j = 2; j <= 4; ++j) {
                for (k = j; k >= 2; --k) {
                    if (Table[i][k-1] == 0)
                    {
                        Table[i][k-1] = Table[i][k];
                        Table[i][k] = 0;
                    }
                }
            }
        }
        for (i = 1; i <= 4; ++i) {
            for (j = 2; j <= 4; ++j) {
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
    int i, j, k;
    if (testRight())
    {
        for (i = 1; i <= 4; ++i) {
            for (j = 3; j >= 1; --j) {
                for (k = j; k <= 3; ++k) {
                    if (Table[i][k+1] == 0)
                    {
                        Table[i][k+1] = Table[i][k];
                        Table[i][k] = 0;
                    }
                }
            }
        }
        for (i = 1; i <= 4; ++i) {
            for (j = 3; j >= 1; --j) {
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

char GetDir()
{

}

int main() {
    printf("Do you wanna play (≧v≦)\n");
    printf("Y/N\n");
    char c;
    Max = 0;
    c = getch();
    if (c == 'Y')
    {
        char dir;
        init();
        system("cls");
        ShowTable();
        while (IfLose() + IfWin() == 0)
        {
            dir = getch();
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
                system("cls");
                ShowTable();
                printf("MaxNum = %d\n", Max);
            }
            else if(dir == 'q')
            {
                break;
            }
            else
            {
                system("cls");
                ShowTable();
                printf("Uh, you push something wrong (òωó?)\n");
            }
            if (IfWin()) printf("Congratulations! （o^~^o)\n");
            else if (IfLose()) {
                printf("What a pity! (>…<。)~~\n");
                printf("your score is %d\n", Max);
            }
        }
    }
    printf("see ya (=￣ω￣=)\n");
    return 0;
}