/*
    Number Shifting game

    In this game, You are given a 4x4 matrix with random values filled
    eg:-
        |10  7  5  3|
        | 6 15 11  4|
        | 9  1 13  8|
        |12 14  2   |

    You have to convert this random matrix to matrix which looks like this

        | 1  2  3  4|
        | 5  6  7  8|
        | 9 10 11 12|
        |13 14 15   |

    Game Rules :
        1. You can move only 1 step at a time with the arrow key.
        2. You can move numbers at an empty position only.
        3. For each valid move : your total number of moves will decrease by 1.

    This game is based on 2D array (Matrix) containing elements 1 to 15 but there a blank space required.
    In this code, I use elements 0 to 15 where 0 refers to the space.
    eg :-
    Actual Matrix
    |10  7  5  3|
    | 6 15 11  4|
    | 9  1 13  8|
    |12 14  2  0|

    Matrix displayed
    |10  7  5  3|
    | 6 15 11  4|
    | 9  1 13  8|
    |12 14  2   |

*/

/* Header files */
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*-----------------*/

/*  Function Prototype  */
/*-------------------------------------------------------------------------------*/
void generateMatrix(int[4][4]); //To generate random matrix with elements 0 to 15
void displayMatrix(int[4][4]); //To display matrix
void move(int[4][4]); //To perform moves in matrix
void swap(int*,int*); //To swap two elements of matrix
int compareMatrices(int[4][4],int[4][4]); //To compare two matrix
void terminate(); //To terminate the game
/*-------------------------------------------------------------------------------*/

int c=300; // Total number of moves

/*     Function Definitions    */
/*------------------------------------------------------------------------------*/
//Definition of main() function
int main()
{
    int mat[4][4];
    int rmat[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};//Winning situation matrix
    char name[20];//Player's Name
    char ch;
    /*First Page*/
    printf("\n\n\n\t\tWelcome to The Number Shifting Game... ");
    printf("\n\n\tEnter Your Name : ");
    fgets(name,20,stdin);
    name[strlen(name)-1]='\0';
    system("cls"); //Clear the whole screen
    /*----------------------*/
    /*Rules*/
    printf("\n\tHello %s, read rules of the game carefully...\n",name);
    printf("\n\n RULE OF THIS GAME\n");
    printf("\n 1. You can move only 1 step at a time by arrow key \n Move Up : By Up arrow key\n Move Down : By Down arrow key\n Move Left : By Left arrow key\n Move Right : By Right arrow key");
    printf("\n 2. You can move number at empty position only");
    printf("\n 3. For each valid move : your total number of move will decreased by 1");
    printf("\n 4. Winning situation : number in a 4*4 matrix should be in order from 1 to 15\n\n\t Winning situation : \n");
    displayMatrix(rmat);
    printf("\n 5. You can exit the game at any time by pressing \'E\' or \'e\'");
    printf("\n\n\t Happy gaming, Good Luck");
    printf("\n\nPress any key to start.....");
    getch();
    system("cls");
    generateMatrix(mat);
    /*----------------------*/
    /*Game playing area*/
    while(c>0 && !compareMatrices(mat,rmat))
    {
        printf("\n Hey %s, you have %d moves\n",name,c);
        displayMatrix(mat);
        move(mat);
        system("cls");
    }
    system("cls");
    displayMatrix(mat);
    if(c==0)//This block will be executed if player loses
    {
        system("COLOR 4");//To change font color to RED
        printf("\n\n\t Sorry %s,You Loss, Better luck next time !",name);
    }
    else //This block will be executed if player wins
    {
        system("COLOR A");//To change font color to Green
        printf("\n\n\t Congratulations %s, You Win",name);
    }
    printf("\n\n Press \'S\' or \'s\' to play again...");
    printf("\n\n Press \'E\' or \'e\' to exit...");
    //When game will be completed , this loop will be executed... if player wants to restart the game or exit the game
    while(1)
    {
        switch(getch())
        {
            case 'S': //If player wants to restart the game
            case 's':
                system("cls");
                system("COLOR 7"); //Font color shifted to white
                c=300; //Reinitialize the total number of moves
                main(); // Calling main() function to restart the game again
                break;
            case 'e': //If player wants to exit the game
            case 'E':
                terminate();

        }
    }
    /*------------------------------------*/
    return 0;
}

//Definition of generateMatrix() function
void generateMatrix(int m[4][4])
{
    int i,j,k=0,tmp,upper,lower;
    int elem[16];
    lower=0;
    upper=15;
    srand(time(NULL));
    for(i=0;i<16;i++)
    {
        tmp=(rand()%(upper-lower+1))+lower;
        for(j=0;j<i;j++)
        {
            if(tmp==elem[j])
                break;
        }
        if(i==j)
            elem[i]=tmp;
        else
            i--;
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            m[i][j]=elem[k++];
        }
    }
}

//Definition of displayMatrix() function
void displayMatrix(int m[4][4])
{
    int i,j;
    printf("-----------------\n");
    for(i=0;i<4;i++)
    {
        printf("|");
        for(j=0;j<4;j++)
        {
            if(m[i][j]==0) // For 0 (If element is 0 then print space)
                printf("   ");
            else if(m[i][j]/10==0) // For single digit numbers
                printf("%d  ",m[i][j]);
            else // For 2 digit numbers
                printf("%d ",m[i][j]);
            printf("|");
        }
        printf("\n");
    }
    printf("-----------------\n");
}

//Definition of move() function
void move(int m[4][4])
{
    int i,j,ch;
    // Finding the position of 0
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(m[i][j]==0)
                break;
        }
        if(j!=4)
            break;
    }
    ch=getch();
    /*
        The arrow keys return 0 or 224 first time based on if num lock is on or off.
        After returning 0 or 224 it returns the following values for these keys.
        72-> Up arrow
        80-> Down arrow
        75-> Left arrow
        77-> Right arrow
    */
    if(ch==0 || ch==224)
    {
        switch(getch())
        {
            case 72: // Up arrow
                if(i!=3)
                {
                    swap(&m[i][j],&m[i+1][j]);
                    c--;
                }
                break;
            case 80: // Down arrow
                if(i!=0)
                {
                    swap(&m[i][j],&m[i-1][j]);
                    c--;
                }
                break;
            case 75: //Left arrow
                if(j!=3)
                {
                    swap(&m[i][j],&m[i][j+1]);
                    c--;
                }
                break;
            case 77: //Right arrow
                if(j!=0)
                {
                    swap(&m[i][j],&m[i][j-1]);
                    c--;
                }
        }
    }
    else if(ch=='e' || ch=='E')// To terminate game in middle of the game
        terminate();
}

//Definition of swap() function
void swap(int *a,int *b)
{
    int t;
    t=*a;
    *a=*b;
    *b=t;
}


//Definition of compareMatrices() function
int compareMatrices(int m[4][4],int r[4][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(m[i][j]!=r[i][j])
                break;
        }
        if(j!=4)
            break;
    }
    if(i==4) // Check if Matrices matched
        return 1;
    else // Check if Matrices not matched
        return 0;
}

//Definition of terminate() function
void terminate()
{
    system("cls");
    system("COLOR 7");
    printf("\n Thank you for playing ...\n\n");
    exit(0);
}

/*------------------------------------------------------------------------------*/