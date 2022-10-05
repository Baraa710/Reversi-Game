//
// Author:
//

//#include <reversi.h>
#include <stdio.h>
#include <stdbool.h>
const int dir[][2] = {{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};

void printBoard(char board[][26], int n) {
printf(" ");
  for (int row = 0; row <= n; row++){
    if(row == 0){printf(" ");}
    else {printf("%c ",'a'+(row-1));}
    for (int col = 0; col < n; col++){
      if(row==0){printf("%c",'a'+col);}
      else{printf("%c", board[row-1][col]);}
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col) {
  if (row < n && col < n && row >= 0 && col >=0){
    return true;
  }
  else {return false;}
}

int checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
    int opponentTiles = 0;
    char colour2 = 'B';
    if (colour=='B'){colour2 = 'W';}
    while(board[row+deltaRow][col+deltaCol] == colour2 && positionInBounds(n, row+deltaRow, col+deltaCol)){
      row+= deltaRow;
      col+= deltaCol;
      opponentTiles++; 
    }
    if(positionInBounds(n, row+deltaRow, col+deltaCol)){
      if (opponentTiles != 0 && board[row+deltaRow][col+deltaCol] == colour){
      return opponentTiles;}
      else {return 0;}
    }
    else{
      return 0;
    }
}
int findScore(char board[][26], int n, int row, int col, char colour){
    const int dir[][2] = {{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};
    int flips;
    int totalFlips = 0;
    if(board[row][col]=='U'){
        for(int i = 0; i < 8; i++){
            flips = checkLegalInDirection(board, n, row, col, colour, dir[i][0],dir[i][1]);
            totalFlips+=flips;
            }
        }
    else {return 0;}
    return totalFlips;
}

void compareScores(int n, char board[][26], char colour, int * bestrow, int* bestCol, bool * computerValidMoves){
    int score = 0;
    int maxScore = 0;
    int bestIndexRow, bestIndexCol;
    
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col]=='U'){
                score+= findScore(board, n, row, col, colour);
                if (score>maxScore){
                    maxScore = score;
                    bestIndexRow = row;
                    bestIndexCol = col;
                }
            }
        }  
    }
    *bestrow = bestIndexRow;
    *bestCol = bestIndexCol;
    if (maxScore == 0){ *computerValidMoves = false; }
    else{ *computerValidMoves = true;}
}
void computerMakesMove(int n, char board[][26], char colour, int row, int  col){
  int rowOg = row;
  int colOg = col;
  char colour2;
  
    for(int i = 0; i < 8; i++){
          if(checkLegalInDirection(board, n, rowOg, colOg, colour, dir[i][0],dir[i][1])){
            row = rowOg;
            col = colOg;
            (row)+=dir[i][0];
            (col)+=dir[i][1];
            colour2 = 'B';
            if (colour=='B'){colour2 = 'W';}
                while(board[row][col] == colour2){
                    board[row][col] = colour;
                    row+= dir[i][0];
                    col+=dir[i][1];
                }           
            }
         }
        board[rowOg][colOg] = colour;
          return;
  }
  
void initializeBoard(int * n, char board[][26], char * computerColour, char * playerColour){
  printf("Enter the board dimension: ");
  scanf("%d", n);
 
  for(int row = 0; row < *n; row++){
    for(int col = 0; col < *n; col++){
      board[row][col] = 'U';
    }
  }
  board[(*n/2)-1][(*n/2)-1] = 'W'; 
  board[(*n/2)-1][(*n/2)] = 'B'; 
  board[(*n/2)][(*n/2)-1] = 'B';
  board[(*n/2)][(*n/2)] = 'W';
  
  
  
}
bool playerHasLegalMoves(int n, char board[][26], char colour){
  const int dir[][2] = {{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};
  for(int row = 0; row < n; row++){
    for(int col = 0; col < n; col++){
      if(board[row][col]=='U'){
        for(int i = 0; i < 8; i++){
          if(checkLegalInDirection(board, n, row, col, colour, dir[i][0],dir[i][1])){
          return true;
          }
        }
      }  
    }
  }
  return false;
}
bool boardIsFull(int n, char board[][26]){
    for(int row = 0; row < n; row++){
        for(int col = 0; col<n; col++){
            if(board[row][col] == 'U') {return false;}
        }
    }
    return true;
}
char findWinner(int n, char board[][26]){
    int whites = 0;
    int blacks = 0;
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col]== 'W') { whites++;}
            else if(board[row][col] == 'B') {blacks++;}

        }
    }
    if(blacks > whites) {   return 'B';}
    else if(whites > blacks)    {return 'W';}
    else    {   return 'U';}
}
bool isGameOver(char board [][26], int n, bool computerLegalMoves, bool playerHasLegalMoves){
    if(!playerHasLegalMoves || !computerLegalMoves){ 
        return true;}
    if(boardIsFull(n, board)){return true;}

    return false;
}


/*void boardConfig(int n, char board[][26]){
  char inputLine[3];
  int col, row;
  char colour;
  scanf("%s", inputLine);
  if (inputLine[0] == '!' && inputLine[1] == '!' && inputLine[2] == '!'){
    return;
  }
  else{  
    colour = inputLine[0];
    row = inputLine[1] - 'a';
    col = inputLine[2] - 'a';
    board[row][col] = colour;
    boardConfig(n, board);  
  }
}*/
bool humanMakeMove(int n, char board[][26], char colour){
  char move[2];
  printf("Enter move for colour %c (RowCol): ", colour);
  scanf("%s", move);
    int row = move[0]-'a';
    int col = move[1]-'a';
    int rowOg = row; 
    int colOg = col;
    const int dir[][2] = {{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};
    if(board[row][col]=='U'){
        for(int i = 0; i < 8; i++){
          if(checkLegalInDirection(board, n, rowOg, colOg, colour, dir[i][0],dir[i][1])){
            row = rowOg;
            col = colOg;
            
            row+=dir[i][0];
            col+=dir[i][1];
            char colour2 = 'B';
            if (colour=='B'){colour2 = 'W';}
                while(board[row][col] == colour2){
                    board[row][col] = colour;
                    row+= dir[i][0];
                    col+=dir[i][1];
                }           
            }
         }
        board[rowOg][colOg] = colour;
          return true;
    }
      else {
        printf("Invalid move.\n");
        
        return false;}
}
void startGame(int * n, char board[][26], char *computerColour, char *playerColour){
   printf("Computer plays (B/W): ");
   scanf("%c", computerColour);
  (*playerColour) = (*computerColour=='W')?'B':'W';

}
void playTurn(int n, char board[][26], char computerColour, char currentColour, char playerColour){
  char winner;
  
  bool computerHasLegalMoves;
  bool humanHasLegalMoves = playerHasLegalMoves(n, board, playerColour);
  bool gameOver = isGameOver(board, n, computerHasLegalMoves, humanHasLegalMoves);
  
  if(!gameOver){
    if(computerColour == currentColour){
      int bestrow = 0; int bestcol=0; 
      compareScores(n, board, computerColour, &bestrow, &bestcol, &computerHasLegalMoves);
      if(computerHasLegalMoves){
        computerMakesMove(n, board, computerColour, bestrow, bestcol);
        printf("Computer places %c at %c%c.", computerColour, 'a'+bestrow, 'a'+bestcol );
      }
    }
    else if(playerColour==currentColour){
      gameOver = humanMakeMove(n, board, playerColour);
      
    }
    if(currentColour=='W'){currentColour='B';}
    else(currentColour = 'W');
    playTurn(n, board, computerColour, currentColour, playerColour);
  }
  
  else{
    winner = findWinner(n, board);
    
    if( winner == 'U'){
      printf("Draw!");
    }
    else printf("%c player wins.", winner);
  }
}


int main(void) {
    int n;
    char board[26][26];
    char computerColour;
    char humanColour;
    bool alwaysTrue = true;
    initializeBoard(&n,board,&computerColour, &humanColour);
    startGame(&n, board, &computerColour, &humanColour);
   
    playTurn(n, board, computerColour, 'B', humanColour);

  
  
  printBoard(board, n);
  return 0;
}