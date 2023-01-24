
#include <queue>
#include <iostream>
#include <conio.h>
#include<windows.h>
#include <cstdlib>
#include <ctime>
#include "graphics.h"
/*------------------------------------------------------------------------------------------------------------------------------------*/
using namespace std;
int board[50][100];
struct snakeloc {
 int r;
 int c;
};
void eraseSnakeCell(int r , int c);
queue<snakeloc> snakeQueue;
queue<snakeloc> snakeQueue2;

char ch = 's';
char ch2 = 80;
/*------------------------------------------------------------------------------------------------------------------------------------*/

void wallCell(int r ,int c){
    r = r * 10;
    c = c * 10;
    setfillstyle(SOLID_FILL,LIGHTRED);
    bar(c,r,c+10,r+10);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    line(c+0,r+0,c+10,r+0);
    line(c+0,r+5,c+10,r+5);
    line(c+0,r+10,c+10,r+5);
}


void drawFruit(int r , int c){
    r = r*10;
    c = c*10;
    readimagefile("OIF.jpg",c,r,c+10,r+10);

}


void gameoverscreen(queue<snakeloc> *size,int r , int c)
{
    char PlayerScore[3];
    PlayerScore[0] = char(48 + size->size() / 10);
    PlayerScore[1] = char(48 + size->size() % 10);
    PlayerScore[2] = '\0';
    setlinestyle(DASHED_LINE,1,NORM_WIDTH);
    setcolor(12);
    settextstyle(10, 0, 7);
    outtextxy(c*5, r*5, "Score: ");
    outtextxy(c*5+60,r*5+50,PlayerScore);
}


void drawSnakeCell(int r , int c){
    r = r * 10;
    c = c * 10;
    setfillstyle(SOLID_FILL,YELLOW);
    bar(c,r,c+9,r+9);
}

void initboard() {
 for (int i = 0; i < 50; i++)
 {
  for (int j = 0; j < 100; j++)
  {
   if (i == 0  i == 49  j == 49  j == 0  j == 99) {
    board[i][j] = 1;
    wallCell(i ,j);
   }
   else {
    board[i][j] = 0;
    eraseSnakeCell(i,j);
   }
  }
 }
}

void generateFruit(queue<snakeloc>* snakeQueue1) {
 srand(time(NULL));
 int fruitC = rand() % 47 + 1;
 int fruitR = rand() % 22 + 1;
 if(snakeQueue1 == &snakeQueue){
        board[fruitR][fruitC] = 3;
 }
 if (snakeQueue1 == &snakeQueue2){
        board[fruitR][fruitC + 50] = 3;
 }
}


void initsnake() {

 snakeloc snake;
 snake.c = 25;
 snake.r = 12;
 snakeloc snake2;
 snake2.c = 75;
 snake2.r = 12;
 for (int i = 1; i < 5; i++)
 {
  board[snake.r][25] = 2;
  snakeQueue.push(snake);
  snake.r++;
  board[snake2.r][75] = 2;
  snakeQueue2.push(snake2);
  drawSnakeCell(snake.r,snake.c);
  drawSnakeCell(snake2.r,snake.c+50);
  snake2.r++;
 }

 generateFruit(&snakeQueue);
 generateFruit(&snakeQueue2);
}
void showBoard() {

 for (int i = 0; i < 50; i++)
 {
  for (int j = 0; j < 100; j++) {
    if (board[i][j] == 2) {
                cout<<'0';

   }
   else if (board[i][j] == 3){
                drawFruit(i,j);
    cout << '&';
  }}
  cout << "\n";
 }
}


void checkFruit(int r , int c, queue<snakeloc>* snakeQueue) {
 if (board[r][c] == 3) {
  snakeloc newLoc = snakeQueue->back();
  snakeQueue->push(newLoc);
  showBoard();
  generateFruit(snakeQueue);
 }
}


// functions that move snake
void moveSnake(char c, queue<snakeloc>* snakeQueue) {
 snakeloc head = snakeQueue->back();
 snakeloc tail = snakeQueue->front();
 board[tail.r][tail.c] = 0;
    eraseSnakeCell(tail.r,tail.c);
 if (c == 72  c == 'w') head.r = head.r - 1;
 if (c == 75  c == 'a') head.c = head.c - 1;
 if (c == 80  c == 's') head.r = head.r + 1;
 if (c == 77  c == 'd') head.c = head.c + 1;
 checkFruit(head.r, head.c, snakeQueue);
 drawSnakeCell(head.r,head.c);
 snakeQueue->push(head);
 board[head.r][head.c] = 2;
 snakeQueue->pop();
}


void eraseSnakeCell(int r , int c){
    r = r * 10;
    c = c * 10;
    setfillstyle(SOLID_FILL,BLACK);
    bar(c,r,c+9,r+9);
}


void score(queue<snakeloc> *size,int x){
    int score1 = size->size();
    char PlayerScore1[3];
    outtextxy(x,530,"score:");
    PlayerScore1[0] = char(48 + score1 / 10);
    PlayerScore1[1] = char(48 + score1 % 10);
    PlayerScore1[2] = '\0';
    outtextxy(x+60,530,PlayerScore1);
}



int main()
{

 initwindow(1000,600);
 //StartGame();
 initboard();
 initsnake();
 bool game_on = true;
 while (game_on) {
        showBoard();
  snakeloc head = snakeQueue.back();
  snakeloc tail = snakeQueue.front();
  snakeloc head2 = snakeQueue2.back();
  if (head.r == 49  head.r == 0  head.c == 49  head.c == 0){ game_on = false;
  break;}
  if (head2.r == 49  head2.c == 49  head2.r == 0  head2.c == 99){ game_on = false; break;}
  if (kbhit()) {
   char key;
   key = getch();

if (key == 'w'  key == 's'  key == 'd'  key == 'a') ch = key;
   else if (key == 72  key == 80  key == 75  key == 77) ch2 = key;

  }
  moveSnake(ch2, &snakeQueue2);
  moveSnake(ch, &snakeQueue);
        score(&snakeQueue,0);
        score(&snakeQueue2,500);
        Sleep(10);
  system("cls");
 }
 gameoverscreen(&snakeQueue,25,25);
 gameoverscreen(&snakeQueue2,25,120);
 while(!kbhit());
    closegraph();
 return 0;

}
