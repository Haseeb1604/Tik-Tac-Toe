# include <iostream>
# include <conio.h> // for getch() function
# include <windows.h>

using namespace std;

void color(int val){ 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), val); 
}

// Used to increase whole console size not individual font size
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
    private:
	  bool draw,undo,redo,Quit;
      char turn;
	  char No[9],selection[20],achar[20];
      int turnchoice,choice,PlayAgain_choice;
	  int row,column,Exit,temp,k;
	  int a[20];
	  string Player1,Player2;
	  
	public:
		 int win1,win2,loss1,loss2,sdraw;
		 char board[3][3]; //= {{'1','2','3'},{'4','5','6'},{'7','8','9'} }; //board declearation and initialization
		// constructor		 
		 Tic_Tac_Toe(){
			for(int i=0 ; i<20 ; i++) 
				selection[i]='F';
			
			win1=0,win2=0,loss1=0,loss2=0,sdraw=0;
			k=0,temp=0;
			turn='X';
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
    color(11);
	cout<<"\n\t\t\t    "<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178);
	cout<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<endl;
	cout<<"\t\t\t    "<<char(178); color(911); cout<<"  Tic Tac Toe Game  "; color(14); cout<<char(178);
	cout<<"\n\t\t\t    "<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178);
	cout<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<char(178)<<endl<<endl;
	color(15);
}

//////////////////////////////////////////////////////////////////////////////////////
//                              Exit Option                                         //
//////////////////////////////////////////////////////////////////////////////////////
bool Tic_Tac_Toe::ExitOption(){
	char ExitChoice;
	cout<<"Are You Sure You Want to Exit"
		  "\n    ( Yes(Y) or No(N) )\n";
	ExitChoice=getch();
	
	if( ExitChoice=='Y' || ExitChoice=='y' ) 
		return false;
	else if( ExitChoice=='N' || ExitChoice=='n' ) 
		return true;
	else 
		ExitOption(); // if user Enters wrong option then the same menu will appears again
}

//////////////////////////////////////////////////////////////////////////////////////
//                                  Menu                                            //
//////////////////////////////////////////////////////////////////////////////////////
int Tic_Tac_Toe::Menu(){ // main menu
    system("cls");
    TitleDisplay();
    
	color(12); cout<<">>Menu\n"; color(15);
    cout<<" 1) Start Game\n"
		  " 2) Game Info\n"
		  " 3) How to Win\n"
		  " 4) Score\n"
		  " 0) Exit\n"; 
	color(13);
    cout<<"    Choice : ";
	
	choice=getch();	
	
	color(15);
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
	Players_Names(); // sets players Names
	
	do { // Outer Do While Starting To Chech Either user want to Play Again or Not
		
		InitializeBoard(); //Board initializing to initial stage
		
		do{ ////Game Body/////
			Display(); // the main display board of game
			Move(); // all logics when user select any value 
    	}while(win_check()); // win_check() returns boolean value so if someone wins the do while loop ends
		
		system("pause");  // pause the console until user press any key
		system("cls"); // clear the previous screen
		
		Result(); // shows result who wins
	    
		line: 
		cout<<"\n\nSelect AnyOne\n\n" //menu for user to select whether he wants to play again or goto main menu
			  "1) Play Again\n"
			  "2) Main Menu\n"
			  "3) Exit"
			  "\n Choice : ";
        PlayAgain_choice=_getch();
        
	    switch(PlayAgain_choice){
		   case '1': Quit = false;  continue; // outer do while loops starts again resulting starting the game again
		   case '2': Exit = false;  break; // loops breaks
		   case '3': 
		   			cout<<"\n\n"; 
					backtoexit=ExitOption(); // Exit Option function for confirmation for exit
                     if(backtoexit==true){ 
					 	system("cls");	
						goto line; // return back to menu starting from line:
					} 
					break;
		   default:  
		   			system("cls");	
					TitleDisplay();
			        cout<<"Invalid Choice\n"
						  "Please Select Valid one\n"; 
					goto line; // return back to menu starting from line:
		}
    }while(Exit && backtoexit); // backtoexit will ends loops and continue the window to main menu while exit will close all the game
}

////////////////////////////////////////////////////////////////////////////////////
//                             Player Names                                       //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Players_Names(){
	system("cls");
	TitleDisplay();
	color(14); cout<<"\n>>Players Names\n"; color(7);
	cout<<"\n  Enter Player 1 Name : "; color(15);   
	cin>>Player1; color(7);
	cout<<"\n  Enter Player 2 Name : "; color(15);   
	cin>>Player2;
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
	if(turn == 'X')
		cout<<"\n "<<Player1<<" [X] Turns :- ";
	else if(turn == 'O') 
		cout<<"\n "<<Player2<<" [O] Turns :- ";
	turnchoice=_getch();  // User Will Select Any Number on The Board
	
	switch(turnchoice){//      Setting Row and Column According to User Choice To Replace with 'X' or 'O'
		// K checks the position while a array keeps value of its position
		// No array stores the ascii code of value at that position	
		// selection array checks whether the position has assigned some value before undo it.
		// achar stores the turns at specific position
		case '1':  	row=0;  column=0; No[0]=49; a[k]=0; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=0 */ k++; break;
		case '2':  	row=0;  column=1; No[1]=50; a[k]=1; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=1 */ k++; break;
		case '3':	row=0;  column=2; No[2]=51; a[k]=2; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=2 */ k++; break;
		case '4':	row=1;  column=0; No[3]=52; a[k]=3; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=3 */ k++; break;
		case '5':	row=1;  column=1; No[4]=53; a[k]=4; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=4 */ k++; break;
		case '6':	row=1;  column=2; No[5]=54; a[k]=5; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=5 */ k++; break;
		case '7':	row=2;  column=0; No[6]=55; a[k]=6; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=6 */ k++; break;
		case '8':	row=2;  column=1; No[7]=56; a[k]=7; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=7 */ k++; break;
		case '9':	row=2;  column=2; No[8]=57; a[k]=8; if(turn=='O'){achar[k]='O';}else{achar[k]='X';} selection[k]='T'; /* k=8 */ k++; break;
		case 'z':   undo=true; break;
		case 'y':   redo=true; break;
		case '0':   Quit=true; break;
		default :   
			cout<<"Invalid Choice\n"
				  "Please select Valid One "; 
			Move();
	}
    
	if(Quit == true) 
	goto line; // game will be intrupted
    
	if ( redo==false && undo==false && turn == 'X' &&  board[row][column] != 'X'  &&  board[row][column] != 'O' ){
	  board[row][column] = 'X' ;    // Converting User Selected Number With X
	  turn = 'O' ;                  // Converting Turn to O
	}else
	if ( redo==false && undo==false &&  turn == 'O' &&  board[row][column] != 'X'  &&  board[row][column] != 'O' ){
	  board[row][column] = 'O';   	// Converting User Selected Number With O
	  turn = 'X';                   // Converting Turn to O
	}else
	if(undo==true && redo==false) 
		Undo();
	else 
	if(redo==true && undo==false) 
		Redo();
	
	line: Display();
}


////////////////////////////////////////////////////////////////////////////////////
//                                  Undo                                          //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Undo(){
    // k checks the turns count since array index start with zero so here we decreament k to match exact array value and also reduce the turn counts
	k--;
    temp=a[k]; // here the board index value is stored in a[k]  at which position user want to undo
    switch(temp){ // this switch set row and column value to undo the value at specific position
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
	if(board[row][column]!='O' && board[row][column]!='X') 
	goto line; // If board has no move yet then undo will be false and the game will be back to its position again	
	
	board[row][column] = No[temp]; // initialize that position with value as its initial stage
	
	// changes turn	
	if(turn == 'X')
		turn = 'O';
	else if(turn == 'O') 
		turn = 'X';
		
    line: 
	undo=false;
}

////////////////////////////////////////////////////////////////////////////////////
//                                  Redo                                          //
////////////////////////////////////////////////////////////////////////////////////
void Tic_Tac_Toe::Redo(){
	// if there is no selection at specific value before undo then there is no need to perfom Redo operation on that position 
	if(selection[k]=='F')
	goto line;
	
    char t; 
    temp=a[k]; // stores position value
	t=achar[k]; // t stores turn at specific position
	
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
     
	if(turn == 'X' && selection[k]=='T'){
    	board[row][column]=t; // turns value at position of row and column at board to value
        turn = 'O'; // turn changes 
        selection[k]=='F'; // selection turns off
    }
	else if(turn == 'O' && selection[k]=='T'){
	    board[row][column]=t;
	    turn = 'X';
	    selection[k]=='F';
    }
    k++;
    
    line:
	redo=false;
}

////////////////////////////////////////////////////////////////////////////////////
//                              Win Check                                         //
///////////////////////////////////////////////////////////////////////////////////
bool Tic_Tac_Toe::win_check(){
	if( Quit==true ) 
		return false; // if game was intrupted then return false with Quit == true
		
  	if (( board [1][0] == board [1][1] && board [1][0] == board [1][2]) || ( board [0][0] == board [0][1] && board [0][1] == board [0][2] ) || 
	   	( board [2][0] == board [2][1] && board [2][0] == board [2][2]) || ( board [0][0] == board [1][1] && board [1][1] == board [2][2] ) || 
		( board [2][0] == board [1][1] && board [1][1] == board [0][2]) || ( board [0][0] == board [1][0] && board [1][0] == board [2][0] ) || 
		( board [0][1] == board [1][1] && board [1][1] == board [2][1]) || ( board [0][2] == board [1][2] && board [1][2] == board [2][2] ))
  	 return false; //  check for 3 consective similar boxes in rows, columns, and diagnols
  	 
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
	if(Quit==true)  // when game has been intrupted
		cout<<"\n\t\t<<<<Game Interepted>>>>";
	else if(draw== true){  
		cout<<"\n\t\t<<<<<<Game Draw>>>>>>"; 
		sdraw++; // draw score increases
	}
	else if(turn == 'O'){ 
		cout<<"\n\t\t>>>>>>Congratulations<<<<<<\n\t\t\t"<<Player1<<" wins"; 
		win1++; // player 1 win score incrases
		loss2++; // player 2 loss numbers increases
	}
	else if(turn == 'X'){ 
		cout<<"\n\t\t>>>>>>Congratulations<<<<<<\n\t\t\t"<<Player2<<" wins"; 
		win2++; // player 2 win score incrases
		loss1++; // player 1 loss numbers increases
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//                                  Score                                          //
/////////////////////////////////////////////////////////////////////////////////////
bool Tic_Tac_Toe::Score(){
	line: 
	system("cls");
	TitleDisplay();
	
	int choice;
	bool Choice;
 	
	cout<<">>>Scores\n\n"
		  "  >>Player 1 \n"
		  "\n      >>wins :- "<<win1<<"\n"
    	  "\n      >>Loses :- "<<loss1<<"\n"
		  "\n  >>Player 2 \n"
		  "\n     >>wins :- "<<win2<<"\n"
 		  "\n     >>loses :- "<<loss2<<"\n"
 		  "\n  >>Games Draw \n"
		  "\n     >>Draws :- "<<sdraw<<"\n\n";
	
	cout<<"\n1) Main Menu"
		  "\n2) Reset Scores"
		  "\n3) Exit"
		  "\n    Choice : ";
	choice=getch();
	switch(choice){
		case '1': return true;
		case '2': 
			loss1=0,loss2=0,sdraw=0,win1=0,win2=0; 
			goto line;	
		case '3':
		    char ExitChoice;
	    	cout<<"Are You Sure You Want to Exit\n"
				  "    ( Yes(Y) or No(N) )\n";
	        ExitChoice = getch();
	        if( ExitChoice=='Y' || ExitChoice=='y' ) 
				return false;
	        else if( ExitChoice=='N' || ExitChoice=='n' ) 
				goto line;
		default: Score();
    }
}

////////////////////////////////////////////////////////////////////////////////////
//                                Gameinfo                                        //
////////////////////////////////////////////////////////////////////////////////////
class Gameinfo{
	private:
		char choice;
		bool Choice;
	
	public:
		bool gameinfo(){
			system("cls");
			Tic_Tac_Toe Title;
		    Title.TitleDisplay();
			
			cout<<"\n\t\tRULES OF TIC-TAC-TOE\n\n"
				  " 1. The game is played on a grid that's 3 squares by 3 squares.\n\n"
			      " 2. You are X, your friend is O. Players take turns putting their\n"
				  "    marks in any number squares.\n\n"
		    	  " 3. The player who get 3 of her marks in a row\n"
				  "    (up, down, across, or diagonally) is the winner.\n\n"
		   		  " 4. When all 9 squares are full, the game is over.\n"
				  "    If no player has 3 marks in a row, the game ends in a tie.\n\n\n"
				  "\n1) Main Menu"
				  "\n2) Exit"
				  "\n    Choice : ";
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
	private:
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
	        "  1) Main Menu\n"
			"  0) Exit\n"
			"    Choice : ";
       choice=getch();
       
	   switch(choice){
			case '1': return true;
			case '2': 
					Choice=Title.ExitOption();
					if(Choice == false) return false;
					else how_to_win();
		}
	}
};

//////////////////////////////////////////////////////////////////////////////////
//                             About Info                                       //
//////////////////////////////////////////////////////////////////////////////////
void info(){
	color(8);cout<<"\t\t\t <<<<<<"; color(15); cout<<" Major Project "; color(8); cout<<">>>>>>\n\n";color(7);
	cout<<"Developed By"
		  "\n   Muhammad Haseeb"
		  "\n   ID : 10619"
		  "\n   Object Oriented Programming"
		  "\n   BS Software Engineering\n\n";
	system("pause");
}

//////////////////////////////////////////////////////////////////////////////////
//                                 Main                                         //
//////////////////////////////////////////////////////////////////////////////////
main(){
	bool exit=true;
	Tic_Tac_Toe game; // Game Object
	
	fontsize(10,20);
	
	game.TitleDisplay(); // main title
	info(); // About Info
	
	do{
		switch(game.Menu()){ // Menu returns numeric char value
			case '1': game.startgame(); break;
			case '2': Gameinfo g;   exit=g.gameinfo();   break;
			case '3': How_to_win h; exit=h.how_to_win(); break;
			case '4': exit=game.Score(); break;
			case '0': exit=game.ExitOption(); break;
			default : 
				cout<<"Invalid Choice\n"
					  "Please Select Valid One\n"; 
				system("pause");
				game.Menu(); 
				break;
		}
    }while(exit && game.backtoexit);
    
    // End Note
    system("cls"); 
	cout<<"\n\n\n\n\n\n\n\n\t";
	cout<<char(247)<<char(247)<<char(173)<<char(173)<<char(173);
	cout<<"    Hope You Enjoy The Game ";	
	cout<<char(173)<<char(173)<<char(173)<<char(247)<<char(247);
	cout<<"\n\n\n\n\n\n\n\n\n\n";
}
