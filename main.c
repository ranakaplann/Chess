#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 8
#define ROW 8
#define COL 8



void createBoard(char board[ROW][COL]);
void printBoard(char board[ROW][COL]);
void movePawn();
void moveRook();
void moveBishop();
void moveKnight();
int gameNotFinished(char board[ROW][COL],int currentPlayer);
int sign();
void userMove(char board[ROW][COL], int currentPlayer);

int main(void) {
    printf("Welcome to the Chess Game! \n\n");


    char board[ROW][COL];
    int currentPlayer = 0;
    createBoard(board);
    printBoard(board);
    while (gameNotFinished(board,currentPlayer)) {
    userMove(board, currentPlayer);
    currentPlayer = (currentPlayer + 1 ) % 2;
    printBoard(board);
    }

    return 0;
}

void createBoard(char board[ROW][COL]){
  const char *initialRow1 = "rnbqkbnr";
  const char *initialRow2 = "pppppppp";
  const char *initialRow7 = "PPPPPPPP";
  const char *initialRow8 = "RNBQKBNR";


  for(int i =0 ; i < ROW ; i++){
      for(int j =0 ; j < COL ; j++){
       board[i][j]='.';
      }
  }

    for(int i =0 ; i < COL ; i++) {
        board[7][i]= initialRow8[i]; // black pieces //
        board[6][i]= initialRow7[i]; // black pawns //
        board[1][i]= initialRow2[i]; // white pawns //
        board[0][i]= initialRow1[i]; // white pieces //
    }
}

void printBoard(char board[ROW][COL]){
    printf("  a  b  c  d  e  f  g  h\n");
    for(int i =0 ; i < SIZE ; i++) {
        printf("%d", SIZE-i); // row numbers //
        for(int j =0 ; j < COL ; j++) {
            printf(" %c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}





void userMove(char board[ROW][COL], int currentPlayer) {
    char move[3];
    char piece;
    printf("Enter the starting position (e.g. A4, G2..) :    \n");
    scanf("%2s",move);
    getchar();
    int startRow = ROW - (move[1] - '0');
    int startCol = move[0] - 'A';

    printf("Start: %s -> Row: %d, Col: %d\n", move, startRow, startCol);

    printf("Enter the ending position (e.g. A5, G6..):    \n");
    scanf("%2s",move);
    getchar();

    int endRow = ROW - (move[1] - '0') ;
    int endCol = move[0] - 'A';

    printf("End: %s -> Row: %d, Col: %d\n", move, endRow, endCol);

    piece = board[startRow][startCol];
    printf("Selected piece: %c at row: %d , col: %d \n", piece, startRow, startCol);


    if ( piece == '.') {
        printf("No piece at the selected position! Try again.\n");
        userMove(board, currentPlayer);
        return;
    }


    if(piece == 'P' || piece == 'p'){
        movePawn(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'R' || piece == 'r'){
        moveRook(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'B' || piece == 'b') {
        moveBishop(board, startRow, startCol, endRow, endCol, currentPlayer);
    }
    else {
        printf("Invalid move, please try again!\n");
        userMove(board, currentPlayer);
    }
}




void movePawn(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer) {
    char piece = board[startRow][startCol];

    if (piece != 'P' && piece != 'p') {
        printf("No pawn at the starting position! Try again.\n");
        return;
    }
    if (currentPlayer == 0 ) { // user is white //
        if (piece != 'P') {
            printf("It's white's turn!\n");
            return;
        }
    if (endRow != startRow - 1 || endCol != startCol) {
        printf("Invalid move for white  pawn, pawns move  forward one square  \n");
        return;
        }
    }

    else {
        if (piece != 'p') {
            printf("It's black's turn!\n");
            return;
        }
        if (endRow != startRow + 1 || endCol != startCol) {
            printf("Invalid move for black  pawn, pawns move  forward one square  \n");
            return;
        }
    }
    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = '.';
}



void moveRook(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer) {
    char piece = board[startRow][startCol];
    char target =  board[endRow][endCol];

    if (startRow != endRow && startCol != endCol) {
        printf("Invalid move for rook. Rooks move only in straight lines.");
    }

    if (startRow == endRow) {
        int minCol = startCol < endCol ? startCol : endCol;
        int maxCol = startCol > endCol ? startCol : endCol;
        for (int col = minCol + 1; col < maxCol; col++) {
            if (board[startRow][col] != '.') {
                printf("Path blocked horizontally.\n");
                return;
            }
        }

    }

    else {
        int minRow = startRow < endRow ? startRow : endRow;
        int maxRow = startRow > endRow ? startRow : endRow;
        for (int row = minRow + 1; row < maxRow; row++) {
            if (board[row][startCol] != '.') {
                printf("Path blocked vertically.\n");
                return;
            }
        }
    }

    if (currentPlayer == 0 && !(piece >= 'A' && piece <= 'Z')) {
        printf("White's turn: You can't move black piece!\n");
        return;
    }

    if (currentPlayer == 1 && !(piece >= 'a' && piece <= 'z')){
        printf("Black's turn: You can't move white piece!\n");
        return;
    }

    if ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') || (piece >= 'a' && piece <= 'z') &&  (target >= 'a' && target <= 'z')) {
        printf("You can't capture your own piece.\n");
        return;
    }

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = '.';
}


void moveBishop(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer ) {
    char piece = board[startRow][startCol];
    char target = board[endRow][endCol];

    if (abs(endRow - startRow) != abs(endCol - startCol)) {
        printf("Invalid move for bishop. Try again.\n");
    }

    if (currentPlayer == 0 && !(piece >= 'A' && piece <= 'Z')) {
        printf("White's turn! You can't move a black piece.\n");
    }

    if (currentPlayer == 1 && !(piece >= 'a' && piece <= 'z')) {
        printf("Black's turn! You cant move a white piece.\n");
    }

    int stepRow = sign(endRow - startRow);
    int stepCol = sign(endCol - startCol);

    int c = startCol + stepCol;
    int r = startRow + stepRow;

    while (r != endRow && r != endCol  ) {
        if (board[r][c] != '.') {
            printf("Path blocked for bishop.\n");
            return;
        }
        r += stepRow;
        c += stepCol;
    }

    if ((currentPlayer == 0 && target >= 'A' && target <= 'Z') || (currentPlayer == 1 && !(target >= 'a' && target <= 'z'))) {
        printf("You can't capture your own piece!\n");
    }


    board[endRow][endCol] = piece;
    board[startRow][startCol] = '.';
}

int sign(int x) {
    if (x > 0) return 1;
    return -1;
}

void moveKnight() {


}

int gameNotFinished(char board[ROW][COL], int currentPlayer) {
    return 1;  ///  TO BE IMPLEMENTED TO CHECK IF THE GAME IS FINISHED (etc. MATE ,STALE MATE ..
}











