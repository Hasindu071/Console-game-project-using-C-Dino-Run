#include <iostream>  // Include the C++ standard input-output library
#include <conio.h>    // Include the console input/output library.
#include <time.h>  // Include the time library for time-related functions.
#include <windows.h> // Include the Windows library for Windows-specific functions.
#define dinoPos 2   // Define a constant called dinoPos with a value of 2
#define hurdlePos 74  // Define a constant called hurdlePos with a value of 74.

using namespace std;

// Define a handle and coordinates for console manipulation
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;  // Create a coordinate structure to store the cursor position.

int dinoY;   // Declare an integer variable to represent the dinosaur's vertical position.
int speed = 40;  // Set the initial speed of the game to 40 (controls the game's speed).
int gameover = 0;  // Initialize a game over flag to 0.

// Function to set the cursor position in the console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to set the cursor's visibility and size
void setcursor(bool visible, DWORD size){
    if (size == 0) {
        size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, & lpCursor);
}
 
 // Initialize the game
void init() {
    system("cls"); // Clear the console screen.
    gameover = 0;   // Reset the game over flag.
    gotoxy(3, 2); cout<<"SCORE : ";    // Display the initial score.
    
     // Draw borders at the top and bottom of the game screen.
    for (int i = 0; i < 79; i++){
    	gotoxy(1+i, 1); cout<<"ß";
    	gotoxy(1+i, 25); cout<<"ß";
	} 
}

// Move the dinosaur character on the screen
void moveDino(int jump = 0) {
    static int foot = 0;

    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else dinoY++;

// Draw the dinosaur character at different positions
    gotoxy(dinoPos, 15 - dinoY);cout<<"                 ";
    gotoxy(dinoPos, 16 - dinoY);cout<<"         ÜÛßÛÛÛÛÜ";
    gotoxy(dinoPos, 17 - dinoY);cout<<"         ÛÛÛÛÛÛÛÛ";
    gotoxy(dinoPos, 18 - dinoY);cout<<"         ÛÛÛÛÛßßß";
    gotoxy(dinoPos, 19 - dinoY);cout<<" Û      ÜÛÛÛÛßßß ";
    gotoxy(dinoPos, 20 - dinoY);cout<<" ÛÛÜ  ÜÛÛÛÛÛÛÜÜÜ ";
    gotoxy(dinoPos, 21 - dinoY);cout<<" ßÛÛÛÛÛÛÛÛÛÛÛ  ß ";
    gotoxy(dinoPos, 22 - dinoY);cout<<"   ßÛÛÛÛÛÛÛß     ";
    gotoxy(dinoPos, 23 - dinoY);

    if (jump == 1 || jump == 2) {
        cout<<"    ÛÛß ßÛ       ";
        gotoxy(2, 24 - dinoY);
        cout<<"    ÛÜ   ÛÜ      ";
    } 
	else if (foot == 0) {
        cout<<"    ßÛÛß  ßßß    ";
        gotoxy(2, 24 - dinoY);
        cout<<"      ÛÜ         ";
        foot = !foot;
    } 
	else if (foot == 1) {
        cout<<"     ßÛÜ ßÛ      ";
        gotoxy(2, 24 - dinoY);
        cout<<"          ÛÜ     ";
        foot = !foot;
    }
    
    gotoxy(2, 25 - dinoY);
    if (jump == 0) {
        cout<<"ßßßßßßßßßßßßßßßßß";
    } else {
        cout<<"                ";
    } 
    Sleep(speed);
}

// Draw the hurdles for the game
void drawHurdle() {
    static int plantX = 0;
	static int score = 0;
	
	// Check if the player has collided with a hurdle.
    if (plantX == 56 && dinoY < 4) {
        score = 0;
        speed = 40;
        gotoxy(36, 8);cout<<"Game Over";  // Display "Game Over" message.
        getch();
        gameover = 1; // Set the game over flag.
    }
    
    gotoxy(hurdlePos - plantX, 20);
	cout<<"| | ";
    gotoxy(hurdlePos - plantX, 21);
	cout<<"| | ";
    gotoxy(hurdlePos - plantX, 22);
	cout<<"|_| ";
    gotoxy(hurdlePos - plantX, 23);
	cout<<" |  ";
    gotoxy(hurdlePos - plantX, 24);
	cout<<" |  ";
     
    plantX++;
    
    // Update the player's score and increase the game speed
    if (plantX == 73) {
        plantX = 0;
        score++;
        gotoxy(11, 2);cout<<"     ";
        gotoxy(11, 2);cout<<score;
        
        // (Display and update the score on the screen.)
        if (speed > 20)
            speed--;
    }
}

// Play the game
void play(){ 
	system("cls");   // Clear the console screen.
    char ch;
    int i;
	init();
	 // Main game loop.
    while (true) {
        while (!kbhit()) {
            if( gameover==1 ){
            	return;   // Exit the game loop when the game is over.
			}
			moveDino();
            drawHurdle();
        }
        ch = getch();  // Get a key press from the player.
          // Handle player input:
        if (ch == 32) {   // If the spacebar is pressed, initiate a jump.
        	i = 0;
            while( i < 12) {
                moveDino(1);  // Move the dinosaur character upward.
                drawHurdle();
                i++;
            }
            while(i > 0) {
                moveDino(2);  // Move the dinosaur character downward.
                drawHurdle();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch(); // Pause the game when 'p' is pressed
		else if (ch == 27)
           break;  // Exit the game when the Escape key is pressed
    }
}

// Display game instructions
void instructions() {
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n1. Avoid hurdles by jumping";
	cout<<"\n2. Press 'Spacebar' to jump ";
	cout<<"\n3. Press 'p' to pause game ";
	cout<<"\n4. Press 'Escape' to exit from game";
	cout<<"\n\nPress any key to go back to menu";
	getch();  // Wait for a key press to return to the main menu.

}

// The main function where the program starts execution.
int main() {

    setcursor(0, 0);
     // Main menu loop.
    do{
		system("cls");  // Clear the console screen
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        DINO RUN        | ";  
		gotoxy(10,7); cout<<" -------------------------- ";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		// Process the user's choice
		if( op=='1') play();   // Start the game
		else if( op=='2') instructions();  // Display game instructions
		else if( op=='3') exit(0);  // Exit the program
		
	}while(1);   // Continue showing the main menu until explicitly exited
    
	return 0;  // Return 0 to indicate successful program execution
}
