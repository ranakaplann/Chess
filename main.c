#include <ctype.h>
#include <stdio.h>
#include <math.h>


#define SIZE 8
#define ROW 8
#define COL 8



void createBoard(char board[ROW][COL]);
void printBoard(char board[ROW][COL]);
int movePawn(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer);
int moveRook(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer);
int moveBishop(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer);
int moveKnight(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer);
int moveQueen(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer);
int moveKing(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer);
int gameNotFinished(char board[ROW][COL],int currentPlayer);
int sign(int x);
int userMove(char board[ROW][COL], int currentPlayer);
int isCheckmate(char board[ROW][COL], int currentPlayer);
int isInCheck(char board[ROW][COL], int currentPlayer);
int isStalemate(char board[ROW][COL], int currentPlayer);
int isMoveValid(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol);

int main(void) {
    printf("Welcome to the Chess Game! \n\nWhite starts first!\n\n");


    char board[ROW][COL];
    int currentPlayer = 0;
    createBoard(board);
    printBoard(board);
    while (gameNotFinished(board,currentPlayer)) {
        int success = userMove(board,currentPlayer);
    if (success) {
         currentPlayer = (currentPlayer + 1 ) % 2;
    }
    printBoard(board);
    }
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



int userMove(char board[ROW][COL], int currentPlayer) {
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
        return 0;
    }


    if(piece == 'P' || piece == 'p'){
       return movePawn(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'R' || piece == 'r'){
        return moveRook(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'B' || piece == 'b') {
        return moveBishop(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'N' || piece == 'n') {
        return moveKnight(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'Q' || piece == 'q') {
        return moveQueen(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else if (piece == 'K' || piece == 'k') {
        return moveKing(board, startRow, startCol, endRow, endCol, currentPlayer);
    }

    else {
        printf("Invalid move, please try again!\n");
        return 0;
    }
}




int movePawn(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer) {
    char piece = board[startRow][startCol];
    char target = board[endRow][endCol];

    if (piece != 'P' && piece != 'p') {
        printf("No pawn at the starting position! Try again.\n");
        return 0;
    }

    if (piece == 'P') {
        if (currentPlayer != 0) {
            printf("It's white's turn!\n");
            return 0;
        }

        if (endCol == startCol && endRow == startRow - 1 && target == '.') {
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '.';
            if(endRow == 0) {
                char choice;
                while (1){
                    printf("Pawn promoted! Choose a piece (Q , R, B ,N )\n");
                    scanf(" %c",&choice);
                    choice = toupper(choice);
                    if (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'N') {
                        board[endRow][endCol] = choice;
                        break;
                    }
                    else{
                        printf("Invalid choice, please try again!\n");
                    }
                }
            }
            return 1;
        }

        else if (startRow == 6 && endCol == startCol && endRow == startRow - 2 &&
                 board[startRow - 1][startCol] == '.' && target == '.') {
                    board[endRow][endCol] = board[startRow][startCol];
                    board[startRow][startCol] = '.';
            if(endRow == 0) {
                char choice;
                while (1){
                    printf("Pawn promoted! Choose a piece (Q , R, B ,N )\n");
                    scanf(" %c",&choice);
                    choice = toupper(choice);
                    if (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'N') {
                        board[endRow][endCol] = choice;
                        break;
                    }
                    else{
                        printf("Invalid choice, please try again!\n");
                    }
                }
            }
            return 1;
           }


        else if((endRow == startRow - 1) && (abs(endCol - startCol) == 1) && (target >= 'a' && target <= 'z')) {
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '.';
            if(endRow == 0) {
                char choice;
                while (1){
                    printf("Pawn promoted! Choose a piece (Q , R, B ,N )\n");
                    scanf(" %c",&choice);
                    choice = toupper(choice);
                    if (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'N') {
                        board[endRow][endCol] = choice;
                        break;
                    }
                    else{
                        printf("Invalid choice, please try again!\n");
                    }
                }
            }
            return 1;
        }

        else {
            printf("Invalid move for white pawn. Try again!\n");
            return 0;
        }
    }


    else if (piece == 'p') {
        if (currentPlayer != 1) {
            printf("It's black's turn!\n");
            return 0;
        }

        if (endCol == startCol && endRow == startRow + 1 && target == '.') {
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '.';
                if(endRow == 7) {
                    char choice;
                    while (1){
                    printf("Pawn promoted! Choose a piece (q , r, b ,n )\n");
                    scanf(" %c",&choice);
                        choice = toupper(choice);
                if (choice == 'q' || choice == 'r' || choice == 'b' || choice == 'n') {
                    board[endRow][endCol] = choice;
                    break;
                } else {
                    printf("Invalid choice, please try again!\n");
                    }
                }
            }
            return 1;
        }

        else if (startRow == 1 && endCol == startCol && endRow == startRow + 2 &&
                board[startRow + 1][startCol] == '.' && target == '.') {
                board[endRow][endCol] = board[startRow][startCol];
                board[startRow][startCol] = '.';
            if(endRow == 7) {
                char choice;
                while (1){
                    printf("Pawn promoted! Choose a piece (q , r, b ,n )\n");
                    scanf(" %c",&choice);
                    choice = toupper(choice);
                    if (choice == 'q' || choice == 'r' || choice == 'b' || choice == 'n') {
                        board[endRow][endCol] = choice;
                        break;
                    } else {
                        printf("Invalid choice, please try again!\n");
                    }
                }
            }
            return 1;
                }

        else if((endRow == startRow + 1) && (abs(endCol - startCol) == 1) && (target >= 'A' && target <= 'Z')) {
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '.';
            if(endRow == 7) {
                char choice;
                while (1){
                    printf("Pawn promoted! Choose a piece (q , r, b ,n )\n");
                    scanf(" %c",&choice);
                    choice = toupper(choice);
                    if (choice == 'q' || choice == 'r' || choice == 'b' || choice == 'n') {
                        board[endRow][endCol] = choice;
                        break;
                    } else {
                        printf("Invalid choice, please try again!\n");
                    }
                }
            }
            return 1;
        }

        else {
            printf("Invalid move for black pawn. Try again! \n");
            return 0;
        }
    }
}


int moveRook(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer) {
    char piece = board[startRow][startCol];
    char target =  board[endRow][endCol];

    if (startRow != endRow && startCol != endCol) {
        printf("Invalid move for rook. Rooks move only in straight lines.");
        return 0;
    }

    if (startRow == endRow) {
        int minCol = startCol < endCol ? startCol : endCol;
        int maxCol = startCol > endCol ? startCol : endCol;
        for (int col = minCol + 1; col < maxCol; col++) {
            if (board[startRow][col] != '.') {
                printf("Path blocked horizontally.\n");
                return 0;
            }
        }

    }

    else {
        int minRow = startRow < endRow ? startRow : endRow;
        int maxRow = startRow > endRow ? startRow : endRow;
        for (int row = minRow + 1; row < maxRow; row++) {
            if (board[row][startCol] != '.') {
                printf("Path blocked vertically.\n");
                return 0;
            }
        }
    }

    if (currentPlayer == 0 && !(piece >= 'A' && piece <= 'Z')) {
        printf("White's turn: You can't move black piece!\n");
        return 0;
    }

    if (currentPlayer == 1 && !(piece >= 'a' && piece <= 'z')){
        printf("Black's turn: You can't move white piece!\n");
        return 0;
    }

    if ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') || (piece >= 'a' && piece <= 'z') &&  (target >= 'a' && target <= 'z')) {
        printf("You can't capture your own piece.\n");
        return 0;
    }

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = '.';
    return 1;
}


int moveBishop(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer ) {
    char piece = board[startRow][startCol];
    char target = board[endRow][endCol];

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    if (rowDiff != colDiff) {
        printf("Invalid move for bishop. Try again.\n");
        return 0;
    }

    if (currentPlayer == 0 && !(piece >= 'A' && piece <= 'Z')) {
        printf("White's turn! You can't move a black piece.\n");
        return 0;
    }

    if (currentPlayer == 1 && !(piece >= 'a' && piece <= 'z')) {
        printf("Black's turn! You cant move a white piece.\n");
        return 0;
    }

    int stepRow = sign(endRow - startRow);
    int stepCol = sign(endCol - startCol);

    int c = startCol + stepCol;
    int r = startRow + stepRow;

    while (r != endRow && c != endCol  ) {
        if (board[r][c] != '.') {
            printf("Path blocked for bishop.\n");
            return 0;
        }
        r += stepRow;
        c += stepCol;
    }

    if ((currentPlayer == 0 && target >= 'A' && target <= 'Z') || (currentPlayer == 1 && !(target >= 'a' && target <= 'z'))) {
        printf("You can't capture your own piece!\n");
        return 0;
    }

    if ((currentPlayer == 0 && target >= 'A' && target <= 'Z') ||
        (currentPlayer == 1 && target >= 'a' && target <= 'z')) {
        printf("You can't capture your own piece.\n");
        return 0;
        }


    board[endRow][endCol] = piece;
    board[startRow][startCol] = '.';
    return 1;
}

int sign(int x) {
    if (x > 0) return 1;
    return -1;
}

int moveKnight(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer ) {
    char piece = board[startRow][startCol];
    char target = board[endRow][endCol];

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)){
        if ((currentPlayer == 0 && target >= 'A' && target <= 'Z') ||
        (currentPlayer == 1 && target >= 'a' && target <= 'z')) {
            printf("You can't capture your own piece.\n");
            return 0;
        }
        board[endRow][endCol] = piece;
        board[startRow][startCol] = '.';
        return 1;
    }
    else {
        printf("Invalid move for knight. Must move in L shape.\n");
        return 0;
    }
}

int moveQueen(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer ) {
    char piece = board[startRow][startCol];

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    if (rowDiff == 0 || colDiff == 0) {             //checking if its moving like rook//
        if (startRow == endRow) {                  //horizontally path control//
            int minCol = startCol < endCol ? startCol : endCol;
            int maxCol = startCol > endCol ? startCol : endCol;
            for (int col = minCol + 1; col < maxCol; col++) {
                if (board[startRow][col] != '.') {
                    printf("Path blocked horizontally.\n");
                    return 0;
                }
            }

        }

        else {      //vertically path control//
            int minRow = startRow < endRow ? startRow : endRow;
            int maxRow = startRow > endRow ? startRow : endRow;
            for (int row = minRow + 1; row < maxRow; row++) {
                if (board[row][startCol] != '.') {
                    printf("Path blocked vertically.\n");
                    return 0;
                }
            }
        }
    }

    else if (rowDiff == colDiff ) {  //checking if its moving like bishop//
        int stepRow = sign(endRow - startRow);
        int stepCol = sign(endCol - startCol);

        int c = startCol + stepCol;
        int r = startRow + stepRow;

        while (r != endRow ) {
            if (board[r][c] != '.') {
                printf("Path blocked for queen.\n");
                return 0;
            }
            r += stepRow;
            c += stepCol;
        }
    }

    else {
        printf("Invalid move for queen.\n");
        return 0;
    }

    board[endRow][endCol] = piece;
    board[startRow][startCol] = '.';
    return 1;

}

int moveKing(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol, int currentPlayer ) {
    char piece = board[startRow][startCol];
    char target =  board[endRow][endCol];

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    if (rowDiff == 1 || colDiff == 1) {
        if ((currentPlayer == 0 && target >= 'A' && target <= 'Z') ||(currentPlayer == 1 && target >= 'a' && target <= 'z')) {
            printf("You can't capture your own piece.\n");
            return 0;
        }
        board[endRow][endCol] = piece;
        board[startRow][startCol] = '.';
        return 1;
    }
    else {
        printf("Invalid move for king. Kings can only move one square for each direction. \n");
        return 0;
    }
}

int gameNotFinished(char board[ROW][COL], int currentPlayer){
        if (isInCheck(board, currentPlayer)) {
            if (isCheckmate(board, currentPlayer)) {
                if (currentPlayer == 0) {
                    printf("Checkmate! Black wins.\n");
                } else {
                    printf("Checkmate! White wins.\n");
                }
                return 0; // Oyun bitti
            }
        } else {
            if (isStalemate(board, currentPlayer)) {
                printf("Stalemate! Draw.\n");
                return 0; // Oyun bitti
            }
        }
            return 1;  ///  TO BE IMPLEMENTED TO CHECK IF THE GAME IS FINISHED (etc. MATE ,STALE MATE ..
    }


int isCheckmate(char board[ROW][COL], int currentPlayer) {
    if (!isInCheck(board, currentPlayer)) {
        return 0;  // Şah tehdit altında değil mat olamaz
    }

    // Tüm taşları dolaş, legal bir kurtuluş hamlesi var mı bak
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            char piece = board[row][col];

            // Sadece mevcut oyuncunun taşları
            if (currentPlayer == 0 && piece >= 'A' && piece <= 'Z') {
                for (int targetRow = 0; targetRow < ROW; targetRow++) {
                    for (int targetCol = 0; targetCol < COL; targetCol++) {
                        // Kendi konumuna gitme, geç
                        if (row == targetRow && col == targetCol) continue;

                        if (isMoveValid(board, row, col, targetRow, targetCol)) {
                            char backup = board[targetRow][targetCol];
                            board[targetRow][targetCol] = piece;
                            board[row][col] = '.';

                            int stillInCheck = isInCheck(board, currentPlayer);

                            // Hamleyi geri al
                            board[row][col] = piece;
                            board[targetRow][targetCol] = backup;

                            if (!stillInCheck) {
                                return 0; // Kurtulabiliyor mat değil
                            }
                        }
                    }
                }
            }

            if (currentPlayer == 1 && piece >= 'a' && piece <= 'z') {
                for (int targetRow = 0; targetRow < ROW; targetRow++) {
                    for (int targetCol = 0; targetCol < COL; targetCol++) {
                        if (row == targetRow && col == targetCol) continue;

                        if (isMoveValid(board, row, col, targetRow, targetCol)) {
                            char backup = board[targetRow][targetCol];
                            board[targetRow][targetCol] = piece;
                            board[row][col] = '.';

                            int stillInCheck = isInCheck(board, currentPlayer);

                            board[row][col] = piece;
                            board[targetRow][targetCol] = backup;

                            if (!stillInCheck) {
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    return 1;  // Hiçbir kurtuluş hamlesi yok MAT
}



int isInCheck(char board[ROW][COL], int currentPlayer) {
        char king = (currentPlayer == 0) ? 'K' : 'k';  // Beyaz için büyük K, siyah için küçük k

        int kingRow = -1, kingCol = -1;

        // Şahın yerini bul
        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++) {
                if (board[row][col] == king) {
                    kingRow = row;
                    kingCol = col;
                    break;
                }
            }
        }

        if (kingRow == -1) {
            printf("King not found on board!\n");
            return 1;  //  şah yoksa check gibi davran
        }

        // Rakip taşları gez
        for (int row = 0; row < ROW; row++) {
            for (int col = 0; col < COL; col++) {
                char piece = board[row][col];

                // Rakip taş mı?
                if (currentPlayer == 0 && piece >= 'a' && piece <= 'z') {
                    if (isMoveValid(board, row, col, kingRow, kingCol)) {
                        return 1;  // Rakip taş şahı tehdit ediyor
                    }
                }
                if (currentPlayer == 1 && piece >= 'A' && piece <= 'Z') {
                    if (isMoveValid(board, row, col, kingRow, kingCol)) {
                        return 1;
                    }
                }
            }
        }

        return 0;  // Hiçbir taş vuramıyor  şah güvende
    }

int isStalemate(char board[ROW][COL], int currentPlayer) {
    if (isInCheck(board, currentPlayer)) {
        return 0;  // Şah tehdit altında  stalemate değil.
    }

    // Tüm taşları gez
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            char piece = board[row][col];

            if (currentPlayer == 0 && piece >= 'A' && piece <= 'Z') {
                // Beyaz taşlar
                for (int targetRow = 0; targetRow < ROW; targetRow++) {
                    for (int targetCol = 0; targetCol < COL; targetCol++) {
                        if (isMoveValid(board, row, col, targetRow, targetCol)) {
                            return 0;  // Geçerli hamle bulundu  stalemate değil
                        }
                    }
                }
            }

            if (currentPlayer == 1 && piece >= 'a' && piece <= 'z') {
                // Siyah taşlar
                for (int targetRow = 0; targetRow < ROW; targetRow++) {
                    for (int targetCol = 0; targetCol < COL; targetCol++) {
                        if (isMoveValid(board, row, col, targetRow, targetCol)) {
                            return 0;  // Geçerli hamle bulundu stalemate değil
                        }
                    }
                }
            }
        }
    }

    // Şah tehdit altında değil ve hiç geçerli hamle yok
    return 1;
}

int isMoveValid(char board[ROW][COL], int startRow, int startCol, int endRow, int endCol) {
    char piece = board[startRow][startCol];
    char target= board[endRow][endCol];

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    if ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') ||
        (piece >= 'a' && piece <= 'z' && target >= 'a' && target <= 'z')) {
        return 0;
    }

    switch (piece) {
        case 'R':
        case 'r':
            if (startRow == endRow) {
                int min = startCol < endCol ? startCol : endCol;
                int max = startCol > endCol ? startCol : endCol;
                for (int i = min + 1; i < max; i++) {
                    if (board[startRow][i] != '.') return 0;
                }
                return 1;
            }
            if (startCol == endCol) {
                int min = startRow < endRow ? startRow : endRow;
                int max = startRow > endRow ? startRow : endRow;
                for (int i = min + 1; i < max; i++) {
                    if (board[i][startCol] != '.') return 0;
                }
                return 1;
            }
            break;

        case 'B':
        case 'b':
            if (rowDiff == colDiff) {
                int stepRow = (endRow - startRow) > 0 ? 1 : -1;
                int stepCol = (endCol - startCol) > 0 ? 1 : -1;
                int r = startRow + stepRow;
                int c = startCol + stepCol;
                while (r != endRow && c != endCol) {
                    if (board[r][c] != '.') return 0;
                    r += stepRow;
                    c += stepCol;
                }
                return 1;
            }
            break;

        case 'Q':
        case 'q':
            if (rowDiff == colDiff) {
                int stepRow = (endRow - startRow) > 0 ? 1 : -1;
                int stepCol = (endCol - startCol) > 0 ? 1 : -1;
                int r = startRow + stepRow;
                int c = startCol + stepCol;
                while (r != endRow && c != endCol) {
                    if (board[r][c] != '.') return 0;
                    r += stepRow;
                    c += stepCol;
                }
                return 1;
            }
            if (startRow == endRow) {
                int min = startCol < endCol ? startCol : endCol;
                int max = startCol > endCol ? startCol : endCol;
                for (int i = min + 1; i < max; i++) {
                    if (board[startRow][i] != '.') return 0;
                }
                return 1;
            }
            if (startCol == endCol) {
                int min = startRow < endRow ? startRow : endRow;
                int max = startRow > endRow ? startRow : endRow;
                for (int i = min + 1; i < max; i++) {
                    if (board[i][startCol] != '.') return 0;
                }
                return 1;
            }
            break;

        case 'N':
        case 'n':
            if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) return 1;
            break;

        case 'K':
        case 'k':
            if (rowDiff <= 1 && colDiff <= 1) return 1;
            break;

        case 'P':
            if (endRow == startRow - 1 && startCol == endCol && target == '.') return 1; // düz
            if (rowDiff == 1 && colDiff == 1 && target >= 'a' && target <= 'z') return 1; // çapraz
            break;

        case 'p':
            if (endRow == startRow + 1 && startCol == endCol && target == '.') return 1; // düz
            if (rowDiff == 1 && colDiff == 1 && target >= 'A' && target <= 'Z') return 1; // çapraz
            break;

        default:
            return 0; // bilinmeyen taş
    }

    return 0;
}



