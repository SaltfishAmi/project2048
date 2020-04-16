#include <iostream>
//#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#define VERSION "1.2.14"
#define EMP 0
//#define EOF -1
#include <cstring>
using namespace std;

extern int grdX, grdY, posX, posY;
extern int codX[8], codY[8];
//prevXY?
extern int data[8][8];
extern int saveSlot[3][8][8], slotData[4][2];
#define ROUND 0
#define SCORE 1
extern int lastOverwritten[8][8], lastOverwrittenNumber, slotEmpty[4];
#define LAST_OVERWRITTEN 0
extern int fileSlotStatus[3];

extern int lastData[8][8];
extern int lastScore;

extern int round;
extern int score;

extern int promptOnOverwrite;

extern int needRepaint;

extern const int base;

void paintGrid(int sizeX, int sizeY);
#define NOFILE 1
void refreshStatus(int isNoFile=0);
void refreshDisplay();
void flushMessage();
void refreshAll(int isNoFile=0);

void waitSec(int sec, char message[7]="Loading");

void genNew2();

#define FLUSH 1
int confirmYN(int options=0);

int moveAll(int direction);
void moveLine(int direction, int lineNumber);
int addAll(int direction);

void saveProgress(int slotNumber);
int loadProgress(int slotNumber);
void cleanData();

void playerSave();
void playerLoad();

void saveToFile(char* fileName);
int loadFromFile(char* fileName);
int checkFile(char* fileName);
void cleanFile();

void playerSaveFile();
void playerLoadFile();

//void enterDevMode();
