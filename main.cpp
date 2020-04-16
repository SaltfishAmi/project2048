//
// COPYRIGHT (C) 2014 "Hinpbock Technologies Incorporated".
// ALL RIGHTS RESERVED.
// "HINPBOCK is not programmed based on classroom knowledge!"
// Version 1.2.14
//
//------------------------------------------------------------------------------
#include "main.h"
const int base=2;
int grdX, grdY, posX, posY;
int data[8][8];
int codX[8], codY[8];
int round;
int score;
int needRepaint=0;
//will be moved into Functions.cpp
int lastData[8][8];
int lastScore=0;
int noSL;
char input;
int firstRound=1, fr2=1, doMoved=0, doAdded=0;
void cPrepare(int sizeX, int sizeY)
{
//preparation
    randomize();
//initialization
    clrscr();
    gotoxy(1,1);
    system("color 1F");
    system("title Console 2048");
    //cout<<"Press D to enter Development Mode."<<endl;
    //cout<<"Note that Development Mode will require a mathematical password."<<endl;
    //if(input=='D'||input=='d')enterDevMode();
//stem circulation
//    for(;;)
//    {
        restart:
        cleanData();
        clrscr();
        system("color 1F");
        gotoxy(1,1);
        system("title Console 2048 - selecting grid size");
        cout<<"Please select the size of the grid, or press 0 anytime to quit:"<<endl;
        while(1)
        {
            cout<<"Press a number key in [3,8] to determine grid size -> ";
            input=getch();
            if(input=='0')return 0;
            cout<<input<<endl;
            //grdX=input-48;
            grdY=grdX=input-48;
            if (grdX>=3&&grdX<=8)break;
        }
        /*while(1)
        {
            cout<<"Then press a number key in [2,8] to determine lines.";
            input=getch();
            if(input=='0')return 0;
            cout<<input<<endl;
            grdY=input-48;
            if (grdY>=2&&grdY<=8)break;
        } */
        cout<<"Ok. Now your grid will be "<<grdX<<'x'<<grdY<<"."<<endl;
        while(1)
        {
            cout<<"Confirm?(Y/N)";
            input=getch();
            if(input=='0')return 0;
            cout<<input<<endl;
            if(input=='Y'||input=='N'||input=='y'||input=='n') break;
        }
        if (input=='N'||input=='n') goto restart;
        restartSame:
        waitSec(1);
        paintGrid(grdX, grdY);
        noSL=1;
        round=0;
        score=0;
//game start
//initializing data = 0
        for(int i=0;i<=7;i++)
            for(int j=0;j<=7;j++)
            {
                if(i<=grdX-1&&j<=grdY-1)
                        data[i][j]=0;
                else data[i][j]=EOF;
            }
//generate a 2 at the beginning
        posX=rand()%grdX;
        posY=rand()%grdY;
        data[posX][posY]=base;
//        gotoxy(codX[posX],codY[posY]);
//        cout<<data[posX][posY];
//        int firstRound, fr2;  // fr2==1 <==> Un-undo-able
                                  // including 1)firstRound
                                  //           2)already undo-ed this round
//        int doMoved, doAdded;
        //int gridFull=1;
        //int needGen=0;
        genNew2();
//    }
}
int cStep()
{
//    {
        while(1)
        {
//main game function
            int gridFull=1;
            for(int i=0;i<grdX;i++)
            {
                for(int j=0;j<grdY;j++)
                {
                    if(data[i][j]==0)gridFull=0;
                }
            }
            int roundPassed=0;
            if(firstRound==1||doMoved==1||doAdded==1)
            {
                roundPassed=1;
            //    needGen=1;
            }
            if(gridFull==1&&!roundPassed)
//determine gameover
            {
                refreshDisplay();
                flushMessage();
                system("color 4f");
                cout<<"You lose the game!!"<<endl;
                cout<<"Your score is: ";
                if(noSL==1)cout<<score<<endl;
                else cout<<score/2<<endl;
                cout<<"Press 0 to quit, R to restart, 9 to load data"<<endl;
                cout<<"or Q to quickly restart using previous settings."<<endl;
                while(1)
                {
                    input=getch();
                    switch(input)
                    {
                        case '0': return 0;
                        case 'R': case 'r': goto restart;
                        case 'Q': case 'q': goto restartSame;
                        case '9':
                        playerLoad();
                        system("color 1f");
                        goto regetch;
                    }
                }
            }
            firstRound=0;
            if(roundPassed)
            {
                round++;
                refreshDisplay();
                if(doMoved==1||doAdded==1){
                //while(needGen==1)
                genNew2();
            }
//determine gameover again
                gridFull=1;
                for(int i=0;i<grdX;i++)
                {
                    for(int j=0;j<grdY;j++)
                    {
                        if(data[i][j]==0)gridFull=0;
                    }
                }
                int isAddable=0;
                for(int i=0;i<grdX;i++)
                {
                    for(int j=0;j<grdY-1;j++)
                    {
                        if(data[i][j]==data[i][j+1])isAddable=1;
                    }
                }
                for(int i=0;i<grdY;i++)
                {
                    for(int j=0;j<grdX-1;j++)
                    {
                        if(data[j][i]==data[j+1][i])isAddable=1;
                    }
                }
                if(isAddable==0&&gridFull==1)
                {
                    refreshDisplay();
                    flushMessage();
                    system("color 4f");
                    cout<<"You lose the game!!"<<endl;
                    cout<<"Your score is: ";
                    if(noSL==1)cout<<score<<endl;
                    else cout<<score/2<<endl;
                    cout<<"Press 0 to quit, R to restart, 9 to load data"<<endl;
                    cout<<"or Q to quickly restart using previous settings."<<endl;
                    while(1)
                    {
                        input=getch();
                        switch(input)
                        {
                            case '0': return 0;
                            case 'R': case 'r': goto restart;
                            case 'Q': case 'q': goto restartSame;
                            case '9':
                            playerLoad();
                            system("color 1f");
                            goto regetch;
                        }
                    }
                }
            }
            //for(int i=0;i<=7;i++)
            //    for(int j=0;j<=7;j++)
            //        lastData[i][j]=data[i][j];
            while(1)
            {
//accept inputs
                regetch: flushMessage();
                input=getch();
                if(input=='0')
                {
                    while(1)
                    {
                        flushMessage();
                        cout<<"Confirm on back?(Y/N)"<<endl;
                        cout<<"All your progress and saves, excluding file saves, will be cleared!"<<endl;
                        input=getch();
                        flushMessage();
                        cout<<"                       "<<endl;
                        if (input=='Y'||input=='y') goto restart;
                        else if (input=='N'||input=='n') break;
                    }
                    if (input=='N'||input=='n') continue;
                }
                int inpCorr=0;
                switch(input)
                {
                    case 'w': case 'W':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
                        for(int i=0;i<=7;i++)
                            for(int j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(0);
                        //refreshDisplay();
                        doAdded=addAll(0);
                        //refreshDisplay();

                        break;
                    case 's': case 'S':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
                        for(int i=0;i<=7;i++)
                            for(int j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(2);
                        doAdded=addAll(2);
                        break;
                    case 'a': case 'A':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
                        for(int i=0;i<=7;i++)
                            for(int j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(1);
                        //refreshDisplay();
                        doAdded=addAll(1);
                        //refreshDisplay();
                        break;
                    case 'd': case 'D':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
                        for(int i=0;i<=7;i++)
                            for(int j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(3);
                        doAdded=addAll(3);
                        break;
                    case '8': playerSave(); noSL=0; continue;
                    case '9': playerLoad(); noSL=0; continue;
                    case 'Z': case 'z':
                        if(fr2==1)
                        {
                            flushMessage();
                            cout<<"Unable to undo now."<<endl;
                            break;
                        }
                        fr2=1;
                        score=lastScore;
                        round--;
                        for(int i=0;i<=7;i++)
                            for(int j=0;j<=7;j++)
                                data[i][j]=lastData[i][j];
                                refreshDisplay();
                        continue;
                    case 'P': case 'p':
                        if(promptOnOverwrite==0)promptOnOverwrite=1;
                        else if(promptOnOverwrite==1)promptOnOverwrite=0;
                        refreshStatus(NOFILE);
                        continue;
                }
                if (needRepaint==1) goto restartSame;
                if (inpCorr==1)
                    break;
            }
            //main game function ends here
            //getch();
        }
//    }
}





