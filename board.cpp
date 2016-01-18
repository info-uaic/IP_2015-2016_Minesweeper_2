#include "board.h"

Board::Board(unsigned int columns, unsigned int rows, unsigned int bombs){
    existence=1;
    number_of_columns=columns,
    number_of_rows=rows,
    number_of_bombs=bombs,
    board=new square[rows*columns];
    cx=0, cy=0, mark_button=2, square_counter=0, flagged_counter=0;
    ///Initialize board
    for(unsigned int i=0; i<rows*columns; ++i)
        board[i].type=empty,
        board[i].state=hidden;
    ///Set random bombs
    int i=GetNumberOfBombs();
    while(GetNumberOfBombs()<number_of_bombs){
        i=GetNumberOfBombs();
        srand ( time(NULL));
        unsigned int random=rand()%(7967);
        unsigned int n=(random%(7*(i+1)))%columns;
        unsigned int m=(random%((i+1)))%rows;
        if(board[n*columns+m].type!=(squaretype)1) board[n*columns+m].type=bomb;
    }
    ///Set numbers
    for(unsigned int i=0; i<number_of_rows; ++i)
        for(unsigned int j=0; j<number_of_columns; ++j){
            if(board[i*number_of_rows+j].type!=bomb){

                unsigned int counter=0;
                for(int k=-1; k<2; ++k)
                    for(int l=-1; l<2 ; ++l)
                        if(board[(i+k)*number_of_rows+(j+l)].type==bomb
                           && (i+k)>=0 && (i+k)<number_of_rows
                           && (j+l)>=0 && (j+l)<number_of_columns)
                            counter++;
                board[i*number_of_rows+j].type=(board[i*number_of_rows+j].type!=bomb)?(squaretype)counter:bomb;
            }
        }
}

Board::~Board(){
    delete[] board;
}

void Board::SetMarkButton(const unsigned x){
    mark_button=x;
}

unsigned int Board::GetNumberOfBombs(){
    int nr=0;
     for(unsigned int i=0; i<number_of_rows; ++i)
        for(unsigned int j=0; j<number_of_columns; ++j)
            if(board[i*number_of_rows+j].type==9) nr++;
    return nr;
}

unsigned int Board::GetCX(){
return cx;
}

unsigned int Board::GetCY(){
return cy;
}

void Board::UpdateCursor(const char a){
    if((a=='A' || a=='a' ) && cy) cy--;
    if((a=='D' || a=='d' )) cy++;
    if((a=='W' || a=='w' ) && cx) cx--;
    if((a=='S' || a=='s' )) cx++;
    ///check limits
    if(cy>=number_of_columns) cy=number_of_columns-1;
    if(cx>=number_of_rows) cx=number_of_rows-1;
}

void Board::PrintNumbersBoard(){
   //for(int i=0;i<255;++i) cout<<i<<' '<<(char)(i)<<"  ";
    cout<<"    ";
    for(unsigned int i=0; i<number_of_columns; ++i){
        if(i<10) cout<<0;
        cout<<i<<"  ";
    }
    for(unsigned int i=0; i<number_of_rows; ++i){
        cout<<'\n';
        cout<<'\n';
        if(i<10) cout<<0;
        cout<<i<<"   ";
        for(unsigned int j=0; j<number_of_columns; ++j){
            //if(j==5) cout<<"\b"<<(char)(187);
            if(board[i*number_of_rows+j].type==empty)
                cout<<(char)(176)<<"   ";
            else if(board[i*number_of_rows+j].type==9)
                cout<<"*   ";
            else cout<<(int)board[i*number_of_rows+j].type<<"   ";
        }

    }
}

void Board::PrintBoard(){
    //int cx=1, cy=5;
    cout<<"\n Bombs Remaining: "<<(number_of_bombs-flagged_counter)<<"    Special Functions: "<<mark_button;
    cout<<"\n\n    ";
    for(unsigned int i=0; i<number_of_columns; ++i){
        if(i<10) cout<<0;
        cout<<i<<"  ";
    }
    for(unsigned int i=0; i<number_of_rows; ++i){
        cout<<'\n';
        cout<<"   ";
        ///CURSOR PRINTING
        for(int iy=0; iy< cy*4 ;++iy) cout<<' ';
        if(i==cx) cout<<(char)(201)<<"   "<<(char)(187);
        if(i==cx+1) cout<<(char)(200)<<"   "<<(char)(188);
        cout<<'\n';
        if(i<10) cout<<0;
        cout<<i<<"   ";
        for(unsigned int j=0; j<number_of_columns; ++j){
            //if(j==5) cout<<"\b"<<(char)(187);
            if(board[i*number_of_rows+j].state==hidden)
                cout<<(char)(219)<<"   ";
            else if(board[i*number_of_rows+j].state==flagged)
                cout<<(char)(1)<<"   ";
            else if(board[i*number_of_rows+j].state==marked)
                cout<<'M'<<"   ";
            else if(board[i*number_of_rows+j].type==empty)
                cout<<(char)(176)<<"   ";
            else if(board[i*number_of_rows+j].type==9)
                cout<<"*   ";
            else cout<<(int)board[i*number_of_rows+j].type<<"   ";
        }
    }
    if(cx+1==number_of_rows){
        cout<<"\n   ";
        for(int iy=0; iy< cy*4 ;++iy) cout<<' ';
        cout<<(char)(200)<<"   "<<(char)(188);

    }
    ///for(int i=0;i<255;++i) cout<<i<<' '<<(char)(i)<<"  ";
    ///cout<<(char)(201)<<"  "<<(char)(187)<<'\n'<<'\n';
   /// cout<<(char)(200)<<"  "<<(char)(188)<<'\n';
}

void Board::DiscoverSquare(const unsigned int x, const unsigned int y){
    square_counter++;
    if(square_counter==20) square_counter=0, mark_button++;
    if(board[x*number_of_rows+y].state!=flagged){
       if(board[x*number_of_rows+y].type==bomb) existence=0;
        else if(board[x*number_of_rows+y].type==empty) {
            board[x*number_of_rows+y].state=unhidden;
            ///Recursive fill discovery
            for(int k=-1; k<2; ++k)
                for(int l=-1; l<2; ++l)
                    if(board[(x+k)*number_of_rows+(y+l)].type!=bomb
                       && (x+k)>=0 && (x+k)<number_of_rows
                       && (y+l)>=0 && (y+l)<number_of_columns
                       && board[(x+k)*number_of_rows+(y+l)].state==hidden)
                        DiscoverSquare(x+k, y+l);
        }
        else board[x*number_of_rows+y].state=unhidden;
    }
}

void Board::SetFlag(const unsigned int x, const unsigned int y){
    if(board[x*number_of_rows+y].state!=unhidden)
        if((board[x*number_of_rows+y].state==flagged))
            board[x*number_of_rows+y].state=hidden,
            flagged_counter--;
        else
            board[x*number_of_rows+y].state=flagged,
            flagged_counter++;
}

void Board::SetMark(const unsigned int x, const unsigned int y){
    if(board[x*number_of_rows+y].state!=unhidden)
        if(board[x*number_of_rows+y].state==marked){
            board[x*number_of_rows+y].state=board[x*number_of_rows+y].oldstate;
            HideBomb(x-1, y); HideBomb(x, y+1);
            HideBomb(x+1, y); HideBomb(x-1, y-1);
            HideBomb(x, y-1); HideBomb(x+1, y-1);
            HideBomb(x+1, y+1); HideBomb(x-1, y+1);
        }
        else  if(mark_button){

            board[x*number_of_rows+y].oldstate=board[x*number_of_rows+y].state;
            board[x*number_of_rows+y].state=marked;
            mark_button--;
            ShowBomb(x-1, y); ShowBomb(x, y+1);
            ShowBomb(x+1, y); ShowBomb(x-1, y-1);
            ShowBomb(x, y-1); ShowBomb(x+1, y-1);
            ShowBomb(x+1, y+1); ShowBomb(x-1, y+1);
        }
}

void Board::ShowBomb(const unsigned int x, const unsigned int y){
    if(x>=0 && x<number_of_rows && y>=0 && y<number_of_columns)
        board[x*number_of_rows+y].oldstate=board[x*number_of_rows+y].state,
        board[x*number_of_rows+y].state=unhidden;
}

void Board::HideBomb(const unsigned int x, const unsigned int y){
    if(x>=0 && x<number_of_rows && y>=0 && y<number_of_columns)
        board[x*number_of_rows+y].state=board[x*number_of_rows+y].oldstate;
}

bool Board::IsNotOver(){
    return existence;
}

bool Board::CheckForWin()
{
    for(unsigned int i=0; i<number_of_rows*number_of_columns; ++i)
        if(board[i].state==hidden && board[i].type!=bomb) return 0;
    return 1;
}
