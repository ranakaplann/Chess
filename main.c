#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 8
#define ROW 16
#define COL 16

typedef unsigned long long U64;

enum Pieces { EMPTY, P, N, B, R, Q, K, p, n, b, r, q, k};   // buyuk  harfler beyaz, kucukler siyah  //
enum Player { WHITE, BLACK, BOTH };
enum File {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_H, FILE_NULL};
enum Rank {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NULL};
enum {TRUE, FALSE};

typedef enum {
    A1= 0, B1, C1, D1, E1, F1, G1, H1,
    A2= 8, B2, C2, D2, E2, F2, G2, H2,
    A3= 16, B3, C3, D3, E3, F3, G3, H3,
    A4= 24, B4, C4, D4, E4, F4, G4, H4,
    A5= 32, B5, C5, D5, E5, F5, G5, H5,
    A6= 40, B6, C6, D6, E6, F6, G6, H6,
    A7= 48, B7, C7, D7, E7, F7, G7, H7,
    A8= 56, B8, C8, D8, E8, F8, G8, H8, NO_PIECE
} MOVES;

const char *moves[] = {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
    "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
    "A3", "B3", "C3", "D3", "E3", "F3" ,"G3", "H3",
    "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
    "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
    "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
    "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
    "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"};

typedef struct {
    int pieces [57];
    U64 pawns [3];  // white black and both //

    int KingSquare[2];

    int enPassant;
    int fiftyMove;

    int ply;   // half move number//
    int totalPly; // total half moves //

    int pieceNum[13];
    int bigPieces[3];     // anything that's not a pawn. //
    int majorPieces[3];    // rooks and queens (white black and both) //
    int minorPieces[3];    // knights and bishops //


} Board;


void createBoard(char board[ROW][COL]);
void printBoard(char board[ROW][COL]);
MOVES stringToEnum(const char* string);
void movePawn();

void userMove(char(* strs)[16]);

int main(void) {
    printf("Welcome to the Chess Game! \n\n");

    int pawn_row=6 , pawn_col=4 ;
    char board[ROW][COL];

    createBoard(board);
    printBoard(board);
    userMove(board);


    printBoard(board);
    return 0;
}

void createBoard(char board[ROW][COL]){
  const char *initialRow1 = " r n b q k b n r";
  const char *initialRow2 = " p p p p p p p p";
  const char *initialRow7 = " P P P P P P P P";
  const char *initialRow8 = " R N B Q K B N R";


  for(int i =0 ; i < ROW ; i++){
      for(int j =0 ; j < COL ; j++){
       board[i][j]='.';
      }
  }

    for(int i =0 ; i < ROW ; i++) {
        board[7][i]= initialRow8[i]; // black pieces //
        board[6][i]= initialRow7[i]; // black pawns //
        board[1][i]= initialRow2[i]; // white pawns //
        board[0][i]= initialRow1[i]; // white pieces //
    }
}

void printBoard(char board[ROW][COL]){
    printf("  a b c d e f g h \n");
    for(int i =0 ; i < SIZE ; i++) {
        printf("%d", SIZE-i); // row numbers //
        for(int j =0 ; j < COL ; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}


MOVES stringToEnum(const char * string) {
   for (int i =0 ; i < SIZE*SIZE ; i++) {
       if (strcmp(string, moves[i]) == 0)
           return (MOVES)i;
   }
    return NO_PIECE;
}


void userMove(char board[ROW][COL]) {
    char move[3];
    char piece;
    printf("Enter a move (e.g. A4, G2..) :    \n");
    scanf("%2s",move);
    getchar();

    MOVES yourMove  =stringToEnum(move);
    if(yourMove != NO_PIECE) {
        printf("Choose your piece (P, N, B, R, Q, K, p, n, b, r, q, k) :   \n");
        scanf("%c",&piece);
        printf("Your selected move :%s with piece %c \n", move,piece);

    }
    else {
        printf("Invalid move, please try again!\n");
        userMove(board);
    }

}

void movePawn() {







}



