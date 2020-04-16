#include "main.h"

char*  d_2      ="2     ";
string D_2      = d_2    ;
string D_4      ="4     ";
string D_8      ="8     ";
string D_16     ="16    ";
string D_32     ="32    ";
string D_64     ="64    ";
string D_128    ="128   ";
string D_256    ="256   ";
string D_512    ="512   ";
string D_1024   ="1024  ";
string D_2048   ="2048  ";
string D_4096   ="4096  ";
string D_8192   ="8192  ";
string D_16384  ="16384 ";
string D_32768  ="32768 ";
string D_65536  ="65536 ";
string D_131072 ="131072";
string D_262144 ="262144";
string D_524288 ="524288";

char slotIndicator[3];
char fileSlotIndicator[3];

void genNew2()
{
    while(1)
    {
        //generate a 2 before or after every moving||adding
        posX=rand()%grdX;
        posY=rand()%grdY;
        if(data[posX][posY]==EMP)     //if a block is empty, fill it; otherwise regenerate
        {
            gotoxy(codX[posX],codY[posY]);
            //base*=2;
            data[posX][posY]=base;
            Sleep(200);
            //textcolor(YELLOW);
            textbackground(YELLOW);
            cprintf(d_2);
            Sleep(100);
            flushMessage();
            return;
        }
    }
}
//------------------------------------------------------------------------------
void refreshStatus(int isNoFile)
{
#define InfoPos (codX[grdX-1]+9)
    textcolor(YELLOW);
    textbackground(BLUE);
    gotoxy(InfoPos,3);
    cprintf("Round");
    if(grdX>=7) gotoxy(InfoPos,5);
    else gotoxy(InfoPos+11,3);
    cprintf("Score");
    if(grdX>=7) gotoxy(InfoPos,7);
    else gotoxy(InfoPos,5);
    cprintf("Saveslots");
    if(grdX>=7) gotoxy(InfoPos,9);
    else gotoxy(InfoPos+11,5);
    cprintf("Filesaves");
    textcolor(WHITE);
    gotoxy(InfoPos,4);
    cprintf("      ");
    gotoxy(InfoPos,4);
    cprintf("%d",round);
    if(grdX>=7)
    {
        gotoxy(InfoPos,6);
        cprintf("      ");
        gotoxy(InfoPos,6);
    }
    else
    {
        gotoxy(InfoPos+11,4);
        cprintf("      ");
        gotoxy(InfoPos+11,4);
    }
    cprintf("%d",score);
    if(grdX>=7) gotoxy(InfoPos,8);
    else gotoxy(InfoPos,6);
    for(int i=1;i<=3;i++)
    {
        if(slotEmpty[i]==0)slotIndicator[i]='X';
        else slotIndicator[i]=' ';
    }
    cprintf("[%c][%c][%c]",slotIndicator[1],slotIndicator[2],slotIndicator[3]);
    if(isNoFile==1)
    {
        if(grdX>=7) gotoxy(InfoPos,10);
        else gotoxy(InfoPos+11,6);
        fileSlotStatus[0]=checkFile("1.424");
        fileSlotStatus[1]=checkFile("2.424");
        fileSlotStatus[2]=checkFile("3.424");
        for(int i=0;i<=2;i++)
        {
            if(fileSlotStatus[i]==1)fileSlotIndicator[i]='X';
            else fileSlotIndicator[i]=' ';
        }
        cprintf("[%c][%c][%c]",fileSlotIndicator[0],fileSlotIndicator[1],fileSlotIndicator[2]);
    }
    if(grdX>=7)
    {
        textcolor(YELLOW);
        gotoxy(InfoPos,11);
        cprintf("[P]toggle");
        gotoxy(InfoPos,12);
        cprintf("Overwrite");
        gotoxy(InfoPos,13);
        cprintf("Prompt");
        textcolor(WHITE);
        if(promptOnOverwrite==1) cprintf("[X]");
        else if (promptOnOverwrite==0) cprintf("[ ]");
    }
    else
    {
        textcolor(YELLOW);
        gotoxy(InfoPos,7);
        cprintf("Prompt on Overwrite");
        textcolor(WHITE);
        gotoxy(InfoPos,8);
        cprintf("[P] to toggle:  ");
        if(promptOnOverwrite==1) cprintf(" On");
        else if (promptOnOverwrite==0) cprintf("Off");
    }
    //else if
    #undef InfoPos
}
//------------------------------------------------------------------------------
void refreshDisplay()
{
    refreshStatus(NOFILE);
    for(int i=0;i<grdX;i++){
        for(int j=0;j<grdY;j++){
            if(data[i][j]>=0)
            {
                gotoxy(codX[i],codY[j]);
                //data[i][j]=524289;
                switch(data[i][j])
                {
                    //customize outputs of every number (max 6 asciis or 3 unicodes)
                    //function of reading these customizations from file is to be developed.

                    case 0:      cout<< "      "; break;
                    case 2:      cout<< D_2     ; break;
                    case 4:      cout<< D_4     ; break;
                    case 8:      cout<< D_8     ; break;
                    case 16:     cout<< D_16    ; break;
                    case 32:     cout<< D_32    ; break;
                    case 64:     cout<< D_64    ; break;
                    case 128:    cout<< D_128   ; break;
                    case 256:    cout<< D_256   ; break;
                    case 512:    cout<< D_512   ; break;
                    case 1024:   cout<< D_1024  ; break;
                    case 2048:   cout<< D_2048  ; break;
                    case 4096:   cout<< D_4096  ; break;
                    case 8192:   cout<< D_8192  ; break;
                    case 16384:  cout<< D_16384 ; break;
                    case 32768:  cout<< D_32768 ; break;
                    case 65536:  cout<< D_65536 ; break;
                    case 131072: cout<< D_131072; break;
                    case 262144: cout<< D_262144; break;
                    case 524288: cout<< D_524288; break;
                    //max 6 digits. if exceed, print something to indicate
                    //that the player is incredible.
                    default:
                        flushMessage();
                        system("title Console 2048 - you're incredible!");
                        cout<<"Exceeded number limit. You've reached 1048576."<<endl;
                        cout<<"You are an expert in playing 2048."<<endl;
                        cout<<"This game is too low-IQ for you!"<<endl;
                        cout<<"Press any key to exit...";
                        getch();
                        exit(1);
                }
            }
        }
    }
    flushMessage();
}
//------------------------------------------------------------------------------
void flushMessage()
{
    gotoxy(1,codY[grdY-1]+2);
    cout<<"                                                                              "<<endl;
    cout<<"                                                                              "<<endl;
    cout<<"                                                                              "<<endl;
    cout<<"                                                                              "<<endl;
    gotoxy(1,codY[grdY-1]+2);
}
//------------------------------------------------------------------------------
void paintGrid(int sizeX, int sizeY)
{
        grdX=sizeX;
        grdY=sizeY;
        clrscr();
        system("color 1f");
        gotoxy(1,1);
        system("title Console 2048 - game in progress");
        cout << "Use WASD to play, 8/9 to save/load, Z/0 to undo/back." <<endl;
        //paint the grid
        for(int i=1;i<=grdX;i++)
        {
            //output column number
            gotoxy(8*i,2);
            cout<<i;
        }
        cout<<endl;
        for(int i=0;i<=grdY;i++)
        {
            for(int j=1;j<=grdX;j++)
            {
                if (j==1) cout<<"   ";    //leave place for line number
                if (i==0||i==grdY) cout<<"========";    //topline
                else cout <<"--------";    //normal lines
                if (j==grdX&&(i==0||i==grdY)) cout<<'='<<endl<<endl;   //last char in topline
                else if (j==grdX&&i!=0) cout<<'-'<<endl<<endl;   //last char in normal line

            }
        }
        for(int i=0;i<=grdX;i++)
        {
            for(int j=0;j<grdY;j++)
            {
                for(int k=4,n=0;n<=grdX;k=k+8,n++)
                {
                    if(k==4){gotoxy(2,2*j+4);cout<<j+1;}   //output line number
                    gotoxy(k,2*j+4);    //vertical lines
                    cout<<'.';
                }   codY[j]=2*j+4;     //coordinates of each posY
            }
            if(i!=grdX)codX[i]=6+8*i;    //coordinates of each posX
        }
        //grid painting complete

}
//------------------------------------------------------------------------------
void refreshAll(int isNoFile)
{
    flushMessage();
    refreshStatus(isNoFile);
    refreshDisplay();
}
//------------------------------------------------------------------------------
void waitSec(int sec, char message[7])
{
    //waiting with graphics
    int nowTime=time(0);
    gotoxy(71,1);
    textcolor(YELLOW);
    textbackground(BLUE);
    cprintf("- %s", message);
    int waitSec_A=0;
    while(time(0)-nowTime<=sec)
    {
        gotoxy(71,1);
        Sleep(200);
        switch(waitSec_A)
        {
            case 0: cprintf("\\"); waitSec_A=1; break;
            case 1: cprintf("|");  waitSec_A=2; break;
            case 2: cprintf("/");  waitSec_A=3; break;
            case 3: cprintf("-");  waitSec_A=0; break;
        }
    }
    gotoxy(71,1);
    cout<<"         ";
}
//------------------------------------------------------------------------------
