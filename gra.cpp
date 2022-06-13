#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

/*Struktura przechowująca wiersz i kolumnę ruchu*/
struct Move {
    int row;
    int col;
};

/*Funkcja wyświetlająca planszę gry dla danego jej rozmiaru*/
void print_board(char** board, int size) {

    switch(size) {

        case 3:
        cout<<" "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<" "<<endl;
        cout<<"-----------"<<endl;
        cout<<" "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<" "<<endl;
        cout<<"-----------"<<endl;
        cout<<" "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<" "<<endl;
        cout<<endl;
        break;

        case 4:
        cout<<" "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<" | "<<board[0][3]<<" "<<endl;
        cout<<"---------------"<<endl;
        cout<<" "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<" | "<<board[1][3]<<" "<<endl;
        cout<<"---------------"<<endl;
        cout<<" "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<" | "<<board[2][3]<<" "<<endl;
        cout<<"---------------"<<endl;
        cout<<" "<<board[3][0]<<" | "<<board[3][1]<<" | "<<board[3][2]<<" | "<<board[3][3]<<" "<<endl;
        cout<<endl;
        break;

        // case 5:
        // cout<<" "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<" | "<<board[0][3]<<" | "<<board[0][4]<<" "<<endl;
        // cout<<"-------------------"<<endl;
        // cout<<" "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<" | "<<board[1][3]<<" | "<<board[1][4]<<" "<<endl;
        // cout<<"-------------------"<<endl;
        // cout<<" "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<" | "<<board[2][3]<<" | "<<board[2][4]<<" "<<endl;
        // cout<<"-------------------"<<endl;
        // cout<<" "<<board[3][0]<<" | "<<board[3][1]<<" | "<<board[3][2]<<" | "<<board[3][3]<<" | "<<board[3][4]<<" "<<endl;
        // cout<<"-------------------"<<endl;
        // cout<<" "<<board[4][0]<<" | "<<board[4][1]<<" | "<<board[4][2]<<" | "<<board[4][3]<<" | "<<board[4][4]<<" "<<endl;
        // cout<<endl;
        // break;

        default:
        break;
    }
}

/*Funkcja odpowiedzialna za wstawianie odpowiedniego symbolu gracza w 
wybrane przez niego miejsce, w zależności od tego czyja kolej ruchu jest obecnie*/
void modify_board(char** board, Move pick, int counter) {

    if (counter%2==0 && board[pick.row][pick.col]=='_') {
        board[pick.row][pick.col]='x';
    }
    else if (counter%2==1 && board[pick.row][pick.col]=='_') {
        board[pick.row][pick.col]='o';
    }
    else {cerr<<"błąd w modify board"<<endl;}
}


/*Funkcja sprawdzająca poprawność, wybranego przez gracza ruchu*/
bool check_if_fine2(char** board, Move pick, int size) {
    if (pick.row<size && pick.row>=0 && pick.col<size && pick.col>=0) {return true;}
    else {return false;}
}


/*Funkcja sprawdzająca czy wybrane przez gracza pole jest puste*/
bool check_if_fine(char** board, Move pick, int size) {

    if(check_if_fine2(board,pick,size)==true) {
        if (board[pick.row][pick.col]=='_') {return true;}
        else {return false;}
    }
    else {return false;}
}


/*Funkcja sprawdzająca czy któryś z graczy wygrał przez zajęcie całego rzędu*/
int check_if_win_row(char** board, int size) {

    int count=0;
    int win=0;
    int tmp=size-1;


   for(int i=0; i<size; ++i) {
       for(int j=1; j<size; ++j) {
           if (board[i][0]==board[i][j]) {++count;}
       }
       if (tmp==count) {
            if (board[i][0]=='x' )
                {win=1;}
            else if (board[i][0]=='o')
                {win=-1; }
            else {;}
        }
       count=0;
   }
   if (win==1) {return 2;}
   else if (win==-1) {return -2;}
   else {return 0;}

}



/*Funkcja sprawdzająca czy któryś z graczy wygrał przez zajęcie całej kolumny*/
int check_if_win_col(char** board, int size) {

    int count=0;
    int win=0;
    int tmp=size-1;


   for(int i=0; i<size; ++i) {
       for(int j=1; j<size; ++j) {
           if (board[0][i]==board[j][i]) {++count;}
       }
       if (tmp==count) {
            if (board[0][i]=='x' )
                {win=1;}
            else if (board[0][i]=='o')
                {win=-1; }
            else {;}
        }
       count=0;
   }
   if (win==1) {return 2;}
   else if (win==-1) {return -2;}
   else {return 0;}

}



/*Funkcja sprawdzająca czy któryś z graczy wygrał przez zajęcie całego skosu*/
int check_if_win_diag(char** board, int size) {

    int count=0;
    int win=0;
    int tmp=size-1;


    for(int j=1; j<size; ++j) {
        if (board[0][0]==board[j][j]) {++count;}
    }
    if (tmp==count) {
        if (board[0][0]=='x' )
            {win=1;}
        else if (board[0][0]=='o')
            {win=-1; }
        else {;}
    }
    count=0;

    for(int j=1; j<size; ++j) {
        if (board[tmp][0]==board[tmp-j][j]) {++count;}
    }
    if (tmp==count) {
        if (board[tmp][0]=='x' )
            {win=1;}
        else if (board[tmp][0]=='o')
            {win=-1; }
        else {;}
    }
   count=0;


   if (win==1) {return 2;}
   else if (win==-1) {return -2;}
   else {return 0;}

}



/*Funkcja sprawdzająca czy któryś z graczy wygrał w jakikolwiek sposób lub czy starcie
zakończyło się remisem czyli wyczerpały się ruchy*/
int check_for_win(char** board, int size, int counter) {

int tmp=0;

tmp=check_if_win_row(board, size);
if(tmp!=0){return tmp;}

tmp=check_if_win_col(board, size);
if(tmp!=0){return tmp;}

tmp=check_if_win_diag(board, size);
if(tmp!=0){return tmp;}

if(counter>=(size*size)) {return 1;}

else {return tmp;}

}

/*Funkcja realizująca algorytm minimax z cięciami alfa beta*/
int minimax(char** board, int size, int counter, bool xoro, int alpha, int beta) {

    int value = check_for_win(board, size, counter);

    if(value==-2) {return -2;}
    else if(value==1) {return 1;}       //zwrócenie wartości jeśli dotarliśmy do jednego ze
    else if(value==2) {return 2;}       //stanów końcowych

    else if (value==0) {

        if(xoro){               //maksymalizacja dla gracza x
            int best = -9999;
            int end=0;

            for (int i=0; i<size; ++i) {

                for (int j=0; j<size; ++j) {

                    if (board[i][j]=='_') {

                        board[i][j]='x';
                        counter++;
                        best = max( best, minimax(board, size, counter, !xoro, alpha, beta) );
                        alpha = max(alpha, best);
                        board[i][j]='_';
                        counter--;
                    }
                    if (beta <= alpha) {
                        end=1;
                        break;
                    }

                }
                if (end==1) {
                    break;
                }
            }   

            return best; 
        }

        else {              //minimalizacja dla gracza o
            int best = 9999;
            int end=0;

            for (int i=0; i<size; ++i) {

                for (int j=0; j<size; ++j) {

                    if (board[i][j]=='_') {

                        board[i][j]='o';
                        counter++;
                        best = min( best, minimax(board, size, counter, !xoro, alpha, beta) );
                        beta = min(beta, best);
                        board[i][j]='_';
                        counter--;
                    }
                    if (beta <= alpha) {
                        end=1;
                        break;
                    }

                }
                if (end==1) {
                    break;
                }
            }   

            return best; 
        }




    }
    else {cerr<<"Błąd minimax - zła wartość value"<<endl; return -10;}

}


/*Funkcja wykonująca optymalny ruch AI*/
void AImove (char** board, int size, int counter) {

int best = -9999;
int alpha =-9999;
int beta = 2;
int end=0;
Move nextmove;

    for (int i=0; i<size; ++i) {

        for (int j=0; j<size; ++j) {

            if (board[i][j]=='_') {

                board[i][j]='x';
                counter++;
                int maxx =minimax(board, size, counter, false, alpha, beta);
                alpha = max(alpha, best);
                board[i][j]='_';
                counter--;

                if (maxx>best) {
                    nextmove.row=i;
                    nextmove.col=j;
                    best=maxx;
                }

            }
            if (beta <= alpha) {
                end=1;
                break;
            }

        }
        if (end==1) {
            break;
        }
    }   

    board[nextmove.row][nextmove.col]='x'; 

}





int main() {


int size;
int tryb;
int n=0;
int counter=0;
Move pick;

cout<< "=================================="<<endl;      //wybór parametrów rozgrywki
cout<< " WITAJ W GRZE KÓŁKO I KRZYŻYK"<<endl;
cout<< "=================================="<<endl;
cout<< " WYBIERZ TRYB GRY!"<<endl<<endl;
cout<< " 1 VS 1           VS AI "<<endl;
cout<<"░░███╗░░         ██████╗░"<<endl;
cout<<"░████║░░         ╚════██╗"<<endl;
cout<<"██╔██║░░         ░░███╔═╝"<<endl;
cout<<"╚═╝██║░░         ██╔══╝░░"<<endl;
cout<<"███████╗         ███████╗"<<endl;
cout<<"╚══════╝         ╚══════╝"<<endl;
do {
cin>>tryb;
cout<<endl;
if (tryb<1 || tryb>2) {
    cout<<"Niepoprawny wybór trybu gry, spróbuj jeszcze raz"<<endl;
}
} while(tryb<1 || tryb>2);
cout<<endl;
cout<< "PODAJ WIELKOŚĆ PLANSZY"<<endl<<endl;
cout<< " Plansza 3x3          Plansza 4x4 "<<endl;
cout<<"   ██████╗░             ░░██╗██╗"<<endl;
cout<<"   ╚════██╗             ░██╔╝██║"<<endl;
cout<<"   ░█████╔╝             ██╔╝░██║"<<endl;
cout<<"   ░╚═══██╗             ███████║"<<endl;
cout<<"   ██████╔╝             ╚════██║"<<endl;
cout<<"   ╚═════╝░             ░░░░░╚═╝"<<endl;
do {
cin>>size;
cout<<endl;
if (size<3 || size>4) {
    cout<<"Niepoprawny rozmiar planszy spróbuj jeszcze raz"<<endl;
}
} while(size<3 || size>4);
cout<<endl;


char ** board = new char * [size];       //tworzenie planszy

for (int i = 0; i<size; ++i)           
	board[i] = new char [size]; 


for (int j=0; j<size; ++j) {
    for (int k = 0; k<size; ++k){ //wypełnienie podłogami odpowiadającymi polom pustym
        board[j][k]='_';
    }
}

print_board(board, size);

switch(tryb) {

    case 1:                     // wersja dla trybu 1v1

    while(n!=2 && n!=-2 && n!=1) {//&& check_if_win(board, size)!=-1
        do {
            cout<<"Podaj wiersz: ";
            cin>>pick.row; pick.row--;
            cout<<"Podaj kolumnę: ";
            cin>>pick.col; pick.col--;
            cout<<endl;

            if (check_if_fine(board,pick,size)==false) {
                cout<<"To pole jest już zajęte lub źle wpisałeś koordynaty"<<endl;
                cout<<"Podaj inne koordynaty"<<endl;
            }

        } while(check_if_fine(board, pick, size)==false);

    counter++;

    modify_board(board, pick, counter);
    print_board(board, size);
    n=check_for_win(board, size, counter);
    }
    if(n==-2){cout<<"Wygrywa potężne KOŁO!!!!"<<endl;}
    else if(n==2){cout<<"Wygrywa potężny KRZYŻYK!!!!"<<endl;}
    else if(n==1){cout<<"REMIS!!!!"<<endl;}

    break;

    case 2:         //wersja dla trybu vsAI

    while(n!=2 && n!=-2 && n!=1) {

    if((counter%2)==0) {

        do {
            cout<<"Podaj wiersz: ";
            cin>>pick.row; pick.row--;
            cout<<"Podaj kolumnę: ";
            cin>>pick.col; pick.col--;
            cout<<endl;

            if (check_if_fine(board,pick,size)==false) {
                cout<<"To pole jest już zajęte lub źle wpisałeś koordynaty"<<endl;
                cout<<"Podaj inne koordynaty"<<endl;
            }

        } while(check_if_fine(board, pick, size)==false);

        counter++;

        modify_board(board, pick, counter);
        print_board(board, size);
        n=check_for_win(board, size, counter);
        
        if(n==-2){cout<<"Wygrywa potężne KOŁO!!!!"<<endl;}
        else if(n==2){cout<<"Wygrywa potężny KRZYŻYK!!!!"<<endl;}
        else if(n==1){cout<<"REMIS!!!!"<<endl;}

    }
    else {
        AImove(board, size, counter);
        counter++;
        print_board(board, size);
        n=check_for_win(board, size, counter);
        if(n==-2){cout<<"Wygrywa potężne KOŁO!!!!"<<endl;}
        else if(n==2){cout<<"Wygrywa potężny KRZYŻYK!!!!"<<endl;}
        else if(n==1){cout<<"REMIS!!!!"<<endl;}
    }
    }
    break;



    default:
    cerr<<"Zmienna tryb przybrała wartość różną od 1 lub 2"<<endl;
    break;




}


for (int i = 0; i<size; i++)                                 //uwolnienie pamięci
	delete [] board[i];

delete [] board;


    return 0;

}