#include "board.h"
#include "Drawings.h"
using namespace std;

int main(){
    int ok=1;
    int bx,by,bn;
    Welcome();
    char any=_getch();
    if(any){
        system("cls");
        Instructions();
        cin>>by>>bx>>bn;

        system("cls");
        Loading();
        Board x(bx, by, bn);
        int val=0;
        char c='\0';
        while(ok){
            system("cls");
            x.PrintBoard();
            c=_getch();
            x.UpdateCursor(c);
            ok=(c)?1:0;
            if(c==' '){
                    //unsigned int cx,cy; cin>>cx>>cy;
                x.SetFlag(x.GetCX(),x.GetCY());
            }
            if(c==(char)(13)){
                //unsigned int cx,cy; cin>>cx>>cy;
                x.DiscoverSquare(x.GetCX(),x.GetCY());
            }
            if(c=='M' || c=='m'){
                //unsigned int cx,cy; cin>>cx>>cy;
                x.SetMark(x.GetCX(),x.GetCY());
            }
            if(x.CheckForWin()){
                YouWin();
                ok=0;
            }
            if(!x.IsNotOver()){
                YouLose();
                ok=0;
                x.PrintNumbersBoard();
            }
        }
    }
    cout<<'\n';
    system("pause");
    return 0;
}
