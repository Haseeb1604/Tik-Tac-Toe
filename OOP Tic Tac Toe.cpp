# include <iostream>
# include <conio.h> // for getch() function
# include <windows.h>
using namespace std;
void color(int val){ SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), val); }
void fontsize(int a, int b){  
   PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();  
   lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
   GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);  
   lpConsoleCurrentFontEx->dwFontSize.X = a;  
   lpConsoleCurrentFontEx->dwFontSize.Y = b;  
   SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);  
}
////////////////////////////////////////////////////////////////////////////////////
//                                 Classes                                        //
////////////////////////////////////////////////////////////////////////////////////
class Tic_Tac_Toe{
      bool draw,undo,redo,Quit;
      char turn,No[9],selection[20],achar[20];
      int turnchoice,choice,PlayAgain_choice,row,column,Exit,temp,k,a[20];
	  string Player1,Player2;
	public:
		 int win1,win2,loss1,loss2,sdraw;
		 char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
		 Tic_Tac_Toe(){
			for(int i=0 ; i<20 ; i++) selection[i]='F';
			win1=0,win2=0,loss1=0,loss2=0,sdraw=0,k=0,temp=0,turn='X';
			draw= false;undo=false;redo=false,Quit=false,backtoexit=true,Exit=true;
		};
		void Undo();
		void Redo();
		bool backtoexit;
		void TitleDisplay();
		int Menu();
		void startgame();
		void Players_Names();
		void Display();
		void Move();
		bool win_check();
		void Result();
		bool Score();
		void InitializeBoard();
		bool ExitOption();
};
//////////////////////////////////////////////////////////////////////////////////////
//                            Title Display                                         //
//////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::TitleDisplay(){
    color(11);cout<<"\n\t\t\t    "<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178);
	cout<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<endl;
	cout<<"\t\t\t    "<<char(178); color(911); cout<<"  Tic Tac Toe Game  "; color(14); cout<<char(178);
	cout<<"\n\t\t\t    "<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178);
	cout<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<endl<<endl;color(15);
}
//////////////////////////////////////////////////////////////////////////////////////
//                              Exit Option                                         //
//////////////////////////////////////////////////////////////////////////////////////
bool Tic_Tac_Toe::ExitOption(){
	char ExitChoice;
	cout<<"Are You Sure You Want to Exit\n    ( Yes(Y) or No(N) )\n";
	ExitChoice=getch();
	if( ExitChoice=='Y' || ExitChoice=='y' ) return false;
	else if( ExitChoice=='N' || ExitChoice=='n' ) return true;
	else ExitOption();
}
//////////////////////////////////////////////////////////////////////////////////////
//                                  Menu                                            //
//////////////////////////////////////////////////////////////////////////////////////
int Tic_Tac_Toe::Menu(){
    system("cls");
    TitleDisplay();
    color(12); cout<<">>Menu\n"; color(15);
    cout<<" 1) Start Game\n 2) Game Info\n 3) How to Win\n 4) Score\n 0) Exit\n"; color(13);
    cout<<"    Choice : ";
	choice=getch();	color(15);
	return choice;
}
//////////////////////////////////////////////////////////////////////////////////////
//                          Initialize Board                                        //
//////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::InitializeBoard(){
	int n=49;    //   49 is the ASCII code of 1 and Onward Numbers 50-57 are ASCII Code of 2-9 Respectively
	for( int i=0 ; i<3 ; i++ )
	for( int j=0 ; j<3 ; j++ ){
		board[i][j]=n; // Setting Board To its Initial Position
		n++;
	}
}
//////////////////////////////////////////////////////////////////////////////////////
//                              Start Game                                          //
//////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::startgame(){
	Players_Names();
	do { // Outer Do While Starting To Chech Either user want to Play Again or Not
		InitializeBoard();
		do{ ////Game Body/////
			Display(); Move();
    	}while(win_check()); 
	    system("pause"); system("cls");
	    Result();
	    line: cout<<"\n\nSelect AnyOne\n\n1) Play Again\n2) Main Menu\n3) Exit\n Choice : ";
        PlayAgain_choice=_getch();
	    switch(PlayAgain_choice){
		   case '1': Quit = false;  continue;
		   case '2': Exit = false;  break;
		   case '3': cout<<"\n\n"; backtoexit=ExitOption();
                     if(backtoexit==true){ system("cls");	goto line; } break;
		   default:  system("cls");	TitleDisplay();
			         cout<<"Invalid Choice\nPlease Select Valid one\n"; goto line;
		}
    }while(Exit && backtoexit);
}
////////////////////////////////////////////////////////////////////////////////////
//                             Player Names                                       //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Players_Names(){
	system("cls");
	TitleDisplay();
	color(14); cout<<"\n>>Players Names\n"; color(7);
	cout<<"\n  Enter Player 1 Name : "; color(15);   cin>>Player1; color(7);
	cout<<"\n  Enter Player 2 Name : "; color(15);   cin>>Player2;
}
////////////////////////////////////////////////////////////////////////////////////
//                           Dispaly Board                                        //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Display(){
	system("cls");
	TitleDisplay(); color(15);
	cout<<"\n Player 1 :"; color(9); cout<<" X\t\t\t\t\t\t "; color(15);  cout<<" Press z to Undo\n";color(15);
	cout<<" Player 2 :"; color(9); cout<<" O\t\t\t\t\t\t "; color(15);  cout<<" Press y to Redo\n";
	cout<<"\t\t\t           "; color(11); cout<<char(219); color(11);cout<<"     "; color(11); cout<<char(219)<<"     \n"; color(15);
	cout<<"\t\t\t        "<<board[0][0]<<"  "; color(11); cout<<char(219)<<"  "; color(15);cout<<board[0][1]<<"  "; color(11);
	cout<<char(219)<<"  "; color(15);cout<<board[0][2]<<"  \n";; color(11);
	cout<<"\t\t\t      _____"<<char(219)<<"_____"<<char(219)<<"_____\n";
	cout<<"\t\t\t           "<<char(219)<<"     "<<char(219)<<"     \n";
    cout<<"\t\t\t        "; color(15);cout<<board[1][0]<<"  ";  color(11);
    cout<<char(219)<<"  "; color(15);cout<<board[1][1]<<"  ";   color(11);
    cout<<char(219)<<"  "; color(15);cout<<board[1][2]<<"  \n"; color(11);
    cout<<"\t\t\t      _____"<<char(219)<<"_____"<<char(219)<<"_____\n";
	cout<<"\t\t\t           "<<char(219)<<"     "<<char(219)<<"     \n";
	cout<<"\t\t\t        "; color(15);cout<<board[2][0]<<"  "; color(11); cout<<char(219)<<"  "; color(15);
	cout<<board[2][1]<<"  "; color(11); cout<<char(219)<<"  "; color(15);cout<<board[2][2]<<"  \n"; color(11);
    cout<<"\t\t\t           "<<char(219)<<"     "<<char(219)<<"     \n\n"; color(12);
    cout<<" Press 0 To Quit\n"; color(15);
}
////////////////////////////////////////////////////////////////////////////////////
//                                  Move                                          //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Move()
{
	if(turn == 'X')      cout<<"\n "<<Player1<<" [X] Turns :- ";
	else if(turn == 'O') cout<<"\n "<<Player2<<" [O] Turns :- ";
	turnchoice=_getch();  // User Will Select Any Number on The Board
	switch(turnchoice){//      Setting Row and Column According to User Choice To Replace with 'X' or 'O'
		case '1':  	row=0;  column=0; No[0]=49; a[k]=0; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=0 */ break;
		case '2':  	row=0;  column=1; No[1]=50; a[k]=1; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=1 */ break;
		case '3':	row=0;  column=2; No[2]=51; a[k]=2; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=2 */ break;
		case '4':	row=1;  column=0; No[3]=52; a[k]=3; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=3 */ break;
		case '5':	row=1;  column=1; No[4]=53; a[k]=4; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=4 */ break;
		case '6':	row=1;  column=2; No[5]=54; a[k]=5; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=5 */ break;
		case '7':	row=2;  column=0; No[6]=55; a[k]=6; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=6 */ break;
		case '8':	row=2;  column=1; No[7]=56; a[k]=7; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=7 */ break;
		case '9':	row=2;  column=2; No[8]=57; a[k]=8; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; k++; /* k=8 */ break;
		case 'z':   undo=true; break;
		case 'y':   redo=true; break;
		case '0':   Quit=true; break;
		default :   cout<<"Invalid Choice\nPlease select Valid One "; Move();
	}
    if(Quit == true) goto line;
    if ( redo==false && undo==false && turn == 'X' &&  board[row][column] != 'X'  &&  board[row][column] != 'O' ){
	  board[row][column] = 'X' ;    // Converting User Selected Number With X
	  turn = 'O' ;                  // Converting Turn to O
	}else
	if ( redo==false && undo==false &&  turn == 'O' &&  board[row][column] != 'X'  &&  board[row][column] != 'O' ){
	  board[row][column] = 'O';   	// Converting User Selected Number With O
	  turn = 'X';                   // Converting Turn to O
	}else
	if(undo==true && redo==false) Undo();
	else if(redo==true && undo==false) Redo();
	line: Display();
}
////////////////////////////////////////////////////////////////////////////////////
//                                  Redo                                          //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Redo(){
    char t;
    temp=a[k];t=achar[k];
    switch(temp){
        case 0:  row=0;  column=0; break;
        case 1:  row=0;  column=1; break;
        case 2:  row=0;  column=2; break;
        case 3:  row=1;  column=0; break;
        case 4:  row=1;  column=1; break;
        case 5:  row=1;  column=2; break;
        case 6:  row=2;  column=0; break;
        case 7:  row=2;  column=1; break;
        case 8:  row=2;  column=2; break;
    }
    if(selection[k]=='F') goto line;
    else if(turn == 'X' && selection[k-1]=='T'){
    	board[row][column]=t;
        turn = 'O';
        selection[k]=='F';
    }
	else if(turn == 'O' && selection[k]=='T'){
	    board[row][column]=t;
	    turn = 'X';
	    selection[k]=='F';
    }
    k++;
    line: redo=false;
}
////////////////////////////////////////////////////////////////////////////////////
//                                  Undo                                          //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Undo(){
    k--;
    temp=a[k];
    switch(temp){
        case 0:  row=0;  column=0; break;
        case 1:  row=0;  column=1; break;
        case 2:  row=0;  column=2; break;
        case 3:  row=1;  column=0; break;
        case 4:  row=1;  column=1; break;
        case 5:  row=1;  column=2; break;
        case 6:  row=2;  column=0; break;
        case 7:  row=2;  column=1; break;
        case 8:  row=2;  column=2; break;
    }
	if(board[row][column]!='O' && board[row][column]!='X') goto line;
	board[row][column] = No[temp];
	if(turn == 'X')      turn = 'O';
	else if(turn == 'O') turn = 'X';
    line: undo=false;
}
////////////////////////////////////////////////////////////////////////////////////
//                              Win Check                                         //
///////////////////////////////////////////////////////////////////////////////////
bool Tic_Tac_Toe::win_check(){
	if( Quit==true ) return false;
  	 if (( board [1][0] == board [1][1] && board [1][0] == board [1][2]) || ( board [0][0] == board [0][1] && board [0][1] == board [0][2] ) || 
	   	 ( board [2][0] == board [2][1] && board [2][0] == board [2][2]) || ( board [0][0] == board [1][1] && board [1][1] == board [2][2] ) || 
		 ( board [2][0] == board [1][1] && board [1][1] == board [0][2]) || ( board [0][0] == board [1][0] && board [1][0] == board [2][0] ) || 
		 ( board [0][1] == board [1][1] && board [1][1] == board [2][1]) || ( board [0][2] == board [1][2] && board [1][2] == board [2][2] ))
  	 return false;
     /////////////////////////////////// unfilled Box Check //////////////////////////////////////
     for ( int i=0 ; i<3 ; i++ )
     for ( int j=0 ; j<3 ; j++ )
     if ( board [i][j] != 'X' && board [i][j] != 'O' )
     return true;   // If There Is Any Box Unfilled Tic_Tac_Toe will Continue 
     //////////////////////////// When all Boxes Filled and No one wins //////////////////////////
     draw = true;  // If There is No winner And All the Box Are Filled Then Match Draw will Be Draw  
     return false;
}
//////////////////////////////////////////////////////////////////////////////////
//                                 Result                                       //
//////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Result(){
	TitleDisplay();
	cout<<"Result :\n";
	if(Quit==true) cout<<"\n\t\t<<<<Game Interepted>>>>";
	else if(draw== true){  cout<<"\n\t\t<<<<<<Game Draw>>>>>>"; sdraw++;}
	else if(turn == 'O'){ cout<<"\n\t\t>>>>>>Congratulations<<<<<<\n\t\t\t"<<Player1<<" wins"; win1++; loss2++;}
	else if(turn == 'X'){ cout<<"\n\t\t>>>>>>Congratulations<<<<<<\n\t\t\t"<<Player2<<" wins"; win2++; loss1++; }
}
/////////////////////////////////////////////////////////////////////////////////////
//                                  Score                                          //
/////////////////////////////////////////////////////////////////////////////////////
bool Tic_Tac_Toe::Score(){
	line: system("cls");
	TitleDisplay();
 	cout<<">>>Scores\n\n"
		  "  >>Player 1 \n";
	cout<<"\n      >>wins :- "<<win1<<endl;
    cout<<"\n      >>Loses :- "<<loss1<<endl;
	cout<<"\n  >>Player 2 \n\n      >>wins :- "<<win2;
 	cout<<"\n\n      >>loses :- "<<loss2<<endl;
	int choice;
	bool Choice;
	cout<<"\n  >>Games Draw \n\n      >>Draws :- "<<sdraw<<endl<<endl;
	cout<<"\n1) Main Menu\n2) Reset Scores\n3) Exit\n    Choice : ";
	choice=getch();
	switch(choice){
		case '1': return true;
		case '2': loss1=0,loss2=0,sdraw=0,win1=0,win2=0; goto line;	
		case '3':
		    char ExitChoice;
	    	cout<<"Are You Sure You Want to Exit\n    ( Yes(Y) or No(N) )\n";
	        ExitChoice = getch();
	        if( ExitChoice=='Y' || ExitChoice=='y' ) return false;
	        else if( ExitChoice=='N' || ExitChoice=='n' ) goto line;
		default: Score();
    }
}
////////////////////////////////////////////////////////////////////////////////////
//                                Gameinfo                                        //
////////////////////////////////////////////////////////////////////////////////////
class Gameinfo{
	char choice;
	bool Choice;
	public:
		bool gameinfo(){
			system("cls");
			Tic_Tac_Toe Title;
		    Title.TitleDisplay();
			cout<<"\n\t\tRULES OF TIC-TAC-TOE\n\n"
				  " 1. The game is played on a grid that's 3 squares by 3 squares.\n\n"
			      " 2. You are X, your friend is O. Players take turns putting their\n    marks in any number squares.\n\n"
		    	  " 3. The player who get 3 of her marks in a row\n    (up, down, across, or diagonally) is the winner.\n\n"
		   		  " 4. When all 9 squares are full, the game is over.\n    If no player has 3 marks in a row, the game ends in a tie.\n\n\n"
				  "\n1) Main Menu\n2) Exit\n    Choice : ";
			choice=getch();
			switch(choice){
				case '1': return true;
				case '2':
					Choice=Title.ExitOption();
					if(Choice == false) return false;
					else gameinfo();
			}
		}
};
////////////////////////////////////////////////////////////////////////////////////
//                              How to win                                        //
////////////////////////////////////////////////////////////////////////////////////
class How_to_win{
	char choice;
	bool Choice;
    public:
      bool how_to_win(){
	   system("cls");
	   Tic_Tac_Toe Title;
	   Title.TitleDisplay();
       cout<<"\t\t\t |-------------------------|\n"
             "\t\t\t | How To Play Tic Tac Toe |\n"
             "\t\t\t |-------------------------|\n\n"
            "  To beat the Opponent, you need to make use of a little bit of strategy. Strategy means\n"
            "  figuring out what you need to do to win.Part of your strategy is trying to figure out\n"
	        "  how to get three Xs or Os in a row,column or Diagonal.The other part is trying to figure\n"
	        "  out how to stop the Opponent from getting three Os or Xs in a row,column or Diagonal.\n"
            "  After you put an X or O in a square, you start looking ahead. Where's the best place for\n"
	        "  your next X or O? You look at the empty squares and decide which ones are good choices-\n"
	        "  which ones might let you make three Xs or Os in a row,column or Diagonal. You also have\n"
	        "  to watch where the Opponent puts its O or X.That could change what you do next.If the\n"
	        "  Opponent gets two Os or Xs in a row, you have to put your next X or O in the last empty\n"
	        "  square in that row,column or Diagonal otherwise the Opponent will win.You are forced to\n"
	        "  play in a particular square or lose the game.If you always pay attention and look ahead,\n"
	        "  you'll never lose a game of Tic-Tac-Toe.you may not win, but at least you'll tie.\n\n"
	        "  1) Main Menu\n  0) Exit\n    Choice : ";
       choice=getch();
       switch(choice){
			case '1': return true;
			case '2': Choice=Title.ExitOption();
					  if(Choice == false) return false;
					  else how_to_win();
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////
//                                 Main                                         //
//////////////////////////////////////////////////////////////////////////////////
main(){
	bool exit=true;
	Tic_Tac_Toe game;
	fontsize(10,20);
	game.TitleDisplay();
	color(8);cout<<"\t\t\t <<<<<<"; color(15); cout<<" Major Project "; color(8); cout<<">>>>>>\n\n";color(7);
	cout<<"Created By\n   Muhammad Haseeb\n   ID : 10619\n   Object Oriented Programming\n   BS Software Engineering\n\n";
	system("pause");
	do{
		switch(game.Menu()){
			case '1': game.startgame(); break;
			case '2': Gameinfo g;   exit=g.gameinfo();   break;
			case '3': How_to_win h; exit=h.how_to_win(); break;
			case '4': exit=game.Score(); break;
			case '0': exit=game.ExitOption(); break;
			default : cout<<"Invalid Choice\nPlease Select Valid One\n"; system("pause");
				game.Menu(); break;
		}
    }while(exit && game.backtoexit);
    system("cls"); 
	cout<<"\n\n\n\n\n\n\n\n\t"<<char(247)<<char(247)<<char(173)<<char(173)<<char(173);
	cout<<"    Hope You Enjoy The Game ";	
	cout<<char(173)<<char(173)<<char(173)<<char(247)<<char(247)<<"\n\n\n\n\n\n\n\n\n\n";
}
