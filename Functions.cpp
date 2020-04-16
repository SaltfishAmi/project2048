#include "main.h"


int saveSlot[3][8][8], slotData[4][2];
int lastOverwritten[8][8], lastOverwrittenNumber=EOF, slotEmpty[4]={1,1,1,1};
//slotData[0=lastOverwritten,1=1,2=2,3=3][0=roundNumber, 1=score]
int promptOnOverwrite=0;
int fileSlotStatus[3];

void playerSave()
{
    flushMessage();
    cout<<"Press 1, 2 or 3 to select a save slot, 4 to cancel."<<endl;
    cout<<"Press F to save to a file.";
    int slotInput=getch()-48;
    if(slotInput+48=='F'||slotInput+48=='f')
    {
        playerSaveFile();
        flushMessage();
        return;
    }
    while(slotInput!=1&&slotInput!=2&&slotInput!=3&&slotInput!=4) slotInput=getch()-48;
    flushMessage();
    if(slotInput==4)
    {
        flushMessage();
        return;
    }
    while(slotEmpty[slotInput]==0&&promptOnOverwrite==1)
    {
        flushMessage();
        cout<<"Overwrite existing save slot?(y/n)"<<endl;
        char input=getch();
        if(input=='n'||input=='N')return;
        else if(input=='y'||input=='Y')break;
    }
    cout<<"Saving to slot "<<slotInput<<"...";
    waitSec(1, "Saving ");
    saveProgress(slotInput);
    refreshStatus();
    flushMessage();
    cout<<"Saved! Continue after 1 second...";
    waitSec(1, "       ");
    flushMessage();
}
//------------------------------------------------------------------------------
void playerLoad()
{
    flushMessage();
    cout<<"Press 1, 2 or 3 load from a save slot, F to load from file."<<endl;
    cout<<"Also 5 to load the data that you've overwritten most recently."<<endl;
    cout<<"To cancel, press 4.";
    char slotInput;
    int slotNum;
    while(1)
    {
        slotInput=getch();
        switch(slotInput)
        {
            case '5': slotNum=0; break;
            case '4':
                flushMessage();
                return;
            case '1': slotNum=1; break;
            case '2': slotNum=2; break;
            case '3': slotNum=3; break;
            case 'f': case 'F':
                playerLoadFile();
                flushMessage();
                return;
        }
        if(slotNum>=0&&slotNum<=3)break;
    }
    flushMessage();
    if(slotNum!=LAST_OVERWRITTEN) cout<<"Loading slot "<<slotNum<<"...";
    else cout<<"Loading last overwritten data...";
    if(slotEmpty[slotNum]==1) cout<<endl<<"Slot empty!! Continue after 1 second...";
    else
    {
        waitSec(1);
        loadProgress(slotNum);
        refreshStatus();
        flushMessage();
        cout<<"Loaded! Continue after 1 second...";
    }
    waitSec(1, "       ");
    flushMessage();
}
//------------------------------------------------------------------------------
void playerSaveFile()
{
    int fileSlot=0;
    flushMessage();
    cout<<"Press 1, 2 or 3 to select a file slot, 4 to cancel."<<endl;
    cout<<"This will save to a file that can be perserved permanently."<<endl;
    while(fileSlot!=1&&fileSlot!=2&&fileSlot!=3&&fileSlot!=4)
        fileSlot=getch()-48;
    switch(fileSlot)
    {
        case 4: return;
        case 1: fileSlotStatus[1]=checkFile("1.424");break;
        case 2: fileSlotStatus[2]=checkFile("2.424");break;
        case 3: fileSlotStatus[3]=checkFile("3.424");break;
    }
    while(fileSlotStatus[fileSlot]==1&&promptOnOverwrite==1)
    {
        flushMessage();
        cout<<"Overwrite existing save file?(y/n)"<<endl;
        char input=getch();
        if(input=='n'||input=='N')return;
        else if(input=='y'||input=='Y')break;
    }
    system("title Console 2048 - saving to file");
    waitSec(1, "Saving ");
    switch(fileSlot)
    {
        case 1: saveToFile("1.424"); break;
        case 2: saveToFile("2.424"); break;
        case 3: saveToFile("3.424"); break;
    }
    refreshStatus();
    flushMessage();
    system("title Console 2048 - game in progress");
    refreshStatus();
    cout<<"Saved to file! Continue after 1 second...";
    waitSec(1, "       ");
    flushMessage();
}
//------------------------------------------------------------------------------
void playerLoadFile()
{
    int fileSlot=0, result=0;
    flushMessage();
    cout<<"Press 1, 2 or 3 to select a file slot, 4 to cancel."<<endl;
    cout<<"This will load from a save file created by 2048 earlier."<<endl;
    while(fileSlot!=1&&fileSlot!=2&&fileSlot!=3&&fileSlot!=4)
        fileSlot=getch()-48;
    if(fileSlot==4)return;
    system("title Console 2048 - loading file");
    waitSec(1);
    switch(fileSlot)
    {
        case 1: result=loadFromFile("1.424"); break;
        case 2: result=loadFromFile("2.424"); break;
        case 3: result=loadFromFile("3.424"); break;
    }
    needRepaint*=fileSlot;
    if(result==0)
    {
    flushMessage();
    cout<<"Failed to open file! Continue after 1 second...";
    waitSec(1, "       ");
    return;
    }
    else if(result==2) return;
    else if(result==3) return;
    refreshStatus();
    flushMessage();
    system("title Console 2048 - game in progress");
    cout<<"Loaded from file! Continue after 1 second...";
    waitSec(1, "       ");
    flushMessage();
}
/*------------------------------------------------------------------------------
void enterDevMode()
{
    system("title Console 2048 - development mode");
    clrscr();
    gotoxy(1,1);
    cout<<"Specifying outputs? or press 0 to back.";
    if(getch()=='0')return;
    cout<<endl<<"Enter less than 6 Ascii or 3 Asian characters for each number."<<endl;
    for(int i=2;i<=524288;i*=2)cout<<i<<endl;

}
*/
//------------------------------------------------------------------------------
int confirmYN(int options)
//options
//1=flush
{
    char input;
    while(1)
    {
        if(options==1)flushMessage();
        cout<<"Confirm?(Y/N)";
        input=getch();
        cout<<input<<endl;
        if(input=='Y'||input=='y') return 1;
        else if(input=='N'||input=='n') return 0;
    }
}
