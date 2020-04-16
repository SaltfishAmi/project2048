#include "main.h"
void saveProgress(int slotNumber)
{
    if(slotEmpty[slotNumber]==0)
    {
        slotEmpty[LAST_OVERWRITTEN]=0;
        for(int i=0;i<=7;i++)
        {
            for(int j=0;j<=7;j++)
            {
                if(lastOverwrittenNumber==EOF)
                {
                    lastOverwritten[i][j]=0;
                    slotEmpty[LAST_OVERWRITTEN]=1;
                }
                else lastOverwritten[i][j]=saveSlot[slotNumber-1][i][j];
            }
        }
        slotData[LAST_OVERWRITTEN][ROUND]=slotData[slotNumber][ROUND];
        slotData[LAST_OVERWRITTEN][SCORE]=slotData[slotNumber][SCORE];
    }
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
            saveSlot[slotNumber-1][i][j]=data[i][j];
    slotData[slotNumber][ROUND]=round;
    slotData[slotNumber][SCORE]=score;
    slotEmpty[slotNumber]=0;
    lastOverwrittenNumber=slotNumber;
    refreshStatus();
}
//------------------------------------------------------------------------------
int loadProgress(int slotNumber)
{
    if(slotEmpty[slotNumber]==0)
    {
        for(int i=0;i<=7;i++)
        {
            for(int j=0;j<=7;j++)
            {
                if(slotNumber==LAST_OVERWRITTEN)data[i][j]=lastOverwritten[i][j];
                data[i][j]=saveSlot[slotNumber-1][i][j];
            }
        }
        round=slotData[slotNumber][ROUND];
        score=slotData[slotNumber][SCORE];
        refreshDisplay();
        return 1;
    }
    else return 0;
}
//------------------------------------------------------------------------------
void cleanData()
{
    for(int i=0;i<=7;i++)
    {
        if(i<=3)slotEmpty[i]=1;
        for(int j=0;j<=7;j++)
        {
            if(i<=3&&j<=1)slotData[i][j]=0;
            saveSlot[0][i][j]=0;
            saveSlot[1][i][j]=0;
            saveSlot[2][i][j]=0;
            lastOverwritten[i][j]=0;
        }
    }
}