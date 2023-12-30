#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include <MMsystem.h>
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define CRESET "\e[0m"
#define HEART_SYMBOL 0x3
#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define EXIT_BUTTON 27 //ESC
#define PAUSE_BUTTON 112 //P
#define LARGEUR_NIVEAU 30
#define HAUTEUR_NIVEAU 10
int affiche =0;
int mazewall=0;
int heartCode = 0x1FA77;
int fin = 0;
int score = 0;
int count = 0;
int number_heart = 3;
char niveau[HAUTEUR_NIVEAU][LARGEUR_NIVEAU] = {
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "a                        aaaaa",
    "a         aaaaa              a",
    "a             aaaa           a",
    "a                            a",
    "aaaaa         aa         aaaaa",
    "a               aaa          a",
    "a                 a          a",
    "a   aaaaaa                   a",
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  };
void saveScore(int score);
char mainMenu();
void mainMenu1();
void loadGame();
void controls(void);
void updateBallPosition(int * ballX, int * ballY,int * posX, int * posY, int maxX, int maxY, int * ballDirectionX, int * ballDirectionY) ;
void gestionMouvement(char niveau[HAUTEUR_NIVEAU][LARGEUR_NIVEAU], int * posX, int * posY, int * ballX, int * ballY, int commande);
void afficherNiveau(char niveau[HAUTEUR_NIVEAU][LARGEUR_NIVEAU], int posX, int posY, int ballX, int ballY, int * birdX, int * birdY);
void exitYN(void);
void pauseALL(void);
void welcomeToSnoopyGame();
void printONE();
void printTWO();
void printTHREE();
void gameOverScreen();
void youWinScreen(void);
char waitForAnyKey();
void resetColor();
void setColor(int color);
void gotoxy(int x, int y);
void Launch();

int main() {

  // for (int i = 0; i < HAUTEUR_NIVEAU; i++) {
  //   for (int j = 0; j < LARGEUR_NIVEAU; j++) {
  //     if (i == posY && j == posX) {
  //       printf("X");
  //     } else if (i == ballY && j == ballX) {
  //       printf("0");
  //     } else if (i == birdY[0] && j == birdX[0] || i == birdY[1] && j == birdX[1] || i == birdY[2] && j == birdX[2] || i == birdY[3] && j == birdX[3]) {
  //       printf("B"); // Caractère pour représenter les oiseaux
  //     } else {
  //       printf("%c", niveau[i][j]);
  //     }

  //   }
  welcomeAnimation();
  welcomeToSnoopyGame();
  Sleep(2000);
  setColor(10);
  Launch();
  // mise a l'echelle
  return 0;
}

void printTHREE() {
  printf("\n");
  int x = 25, y = 7;
  gotoxy(x, y++);
  printf("  .--,-``-.\n");

  gotoxy(x, y++);
  printf(" /   /     '.\n");

  gotoxy(x, y++);
  printf("/ ../        ;\n");

  gotoxy(x, y++);
  printf("\\ ``\\  .`-    '\n");

  gotoxy(x, y++);
  printf(" \\___\\/   \\   :\n");

  gotoxy(x, y++);
  printf("      \\   :   |\n");

  gotoxy(x, y++);
  printf("      /  /   /\n");

  gotoxy(x, y++);
  printf("      \\  \\   \\\n");

  gotoxy(x, y++);
  printf("  ___ /   :   |\n");

  gotoxy(x, y++);
  printf(" /   /\\   /   :\n");

  gotoxy(x, y++);
  printf("/ ,,/  ',-    .\n");

  gotoxy(x, y++);
  printf("\\ ''\\        ;\n");

  gotoxy(x, y++);
  printf(" \\   \\     .'\n");

  gotoxy(x, y++);
  printf("  `--`-,,-'\n");
}

void printTWO() {
  printf("\n");
  int x = 25, y = 7;
  gotoxy(x, y++);
  printf("      ,----,\n");
  gotoxy(x, y++);
  printf("    .'   .' \\ \n");
  gotoxy(x, y++);
  printf("  ,----,'    |\n");
  gotoxy(x, y++);
  printf("  |    :  .  ;\n");
  gotoxy(x, y++);
  printf("  ;    |.'  /\n");
  gotoxy(x, y++);
  printf("  `----'/  ; \n");
  gotoxy(x, y++);
  printf("    /  ;  /  \n");
  gotoxy(x, y++);
  printf("   ;  /  /-, \n");
  gotoxy(x, y++);
  printf("  /  /  /.`|\n");
  gotoxy(x, y++);
  printf("./__;      :\n");
  gotoxy(x, y++);
  printf("|   :    .'\n");
  gotoxy(x, y++);
  printf(";   | .'\n");
  gotoxy(x, y++);
  printf("`---'\n");

}

void Launch() {
  do {
    int select = mainMenu();

    switch (select) {
    case '1':
      system("cls");
      gotoxy(50, 7);
      Sleep(350);
      printTHREE();
      Sleep(350);
      system("cls");

      printTWO();
      Sleep(350);
      system("cls");

      printONE();
      Sleep(300);
      loadGame();

      break;
      // case 1:
      //     displayHighScores();
      //     break;
    case '3':
      controls();
      break;
    case '4':
      exitYN();
      break;
    }
  } while (1);

}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // 15 is the default color (white on black)
}
char waitForAnyKey() {
  int pressed;

  while (!kbhit());

  pressed = getch();
  //pressed = tolower(pressed);
  return ((char) pressed);
}

void youWinScreen(void) {
  setColor(10);
  int x = 3, y = 13;
  gotoxy(x, y++);
  printf("'##:::'##::'#######::'##::::'##::::'##:::::'##:'####:'##::: ##:'####:");
  gotoxy(x, y++);
  printf(". ##:'##::'##.... ##: ##:::: ##:::: ##:'##: ##:. ##:: ###:: ##: ####:");
  gotoxy(x, y++);
  printf(":. ####::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ####: ##: ####:");
  gotoxy(x, y++);
  printf("::. ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ## ## ##:: ##::");
  gotoxy(x, y++);
  printf("::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ##. ####::..:::");
  gotoxy(x, y++);
  printf("::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ##:. ###:'####:");
  gotoxy(x, y++);
  printf("::: ##::::. #######::. #######:::::. ###. ###::'####: ##::. ##: ####:");
  gotoxy(x, y++);
  printf(":::..::::::.......::::.......:::::::...::...:::....::..::::..::....::");
  gotoxy(x, y++);
  gotoxy(x, y++);
  gotoxy(x, y++);
  gotoxy(x, y++);

  if (fin == 4) {
    printf("Your score is :   %d", score);
    saveScore(score);
    waitForAnyKey();
    int chose=0 ;
    printf("\n\n do u want to continue :  1- YES \n");
    printf("                          2- Noo \n");
    scanf("%d",&chose);
    switch (chose) {
    case 1:
      main();
      break;
      
    case 2:
      exitYN();
      break;
    }
  }

  system("cls"); // Clear the console
  //clear the console
  return;
}

void gameOverScreen() {
  system("cls"); // Clear the console
  int x = 17, y = 3;
  setColor(12);
  //http://www.network-science.de/ascii/ <- Ascii Art Gen

  gotoxy(x, y++);
  printf(":'######::::::'###::::'##::::'##:'########:\n");
  gotoxy(x, y++);
  printf("'##... ##::::'## ##::: ###::'###: ##.....::\n");
  gotoxy(x, y++);
  printf(" ##:::..::::'##:. ##:: ####'####: ##:::::::\n");
  gotoxy(x, y++);
  printf(" ##::'####:'##:::. ##: ## ### ##: ######:::\n");
  gotoxy(x, y++);
  printf(" ##::: ##:: #########: ##. #: ##: ##...::::\n");
  gotoxy(x, y++);
  printf(" ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::\n");
  gotoxy(x, y++);
  printf(". ######::: ##:::: ##: ##:::: ##: ########:\n");
  gotoxy(x, y++);
  printf(":......::::..:::::..::..:::::..::........::\n");
  gotoxy(x, y++);
  printf(":'#######::'##::::'##:'########:'########::'####:\n");
  gotoxy(x, y++);
  printf("'##.... ##: ##:::: ##: ##.....:: ##.... ##: ####:\n");
  gotoxy(x, y++);
  printf(" ##:::: ##: ##:::: ##: ##::::::: ##:::: ##: ####:\n");
  gotoxy(x, y++);
  printf(" ##:::: ##: ##:::: ##: ######::: ########::: ##::\n");
  gotoxy(x, y++);
  printf(" ##:::: ##:. ##:: ##:: ##...:::: ##.. ##::::..:::\n");
  gotoxy(x, y++);
  printf(" ##:::: ##::. ## ##::: ##::::::: ##::. ##::'####:\n");
  gotoxy(x, y++);
  printf(". #######::::. ###:::: ########: ##:::. ##: ####:\n");
  gotoxy(x, y++);
  printf(":.......::::::...:::::........::..:::::..::....::\n");

  waitForAnyKey();
  system("cls"); // Clear the console
  return;
}

void printONE() {
  printf("\n");
  gotoxy(25, 7);
  printf("     ,---, \n");
  gotoxy(25, 8);
  printf("  ,`--.' | \n");
  gotoxy(25, 9);
  printf(" /    /  : \n");
  gotoxy(25, 10);
  printf(":    |.' ' \n");
  gotoxy(25, 11);
  printf("`----':  | \n");
  gotoxy(25, 12);
  printf("   '   ' ; \n");
  gotoxy(25, 13);
  printf("   |   | | \n");
  gotoxy(25, 14);
  printf("   '   : ; \n");
  gotoxy(25, 15);
  printf("   |   | ' \n");
  gotoxy(25, 16);
  printf("   '   : | \n");
  gotoxy(25, 17);
  printf("   ;   |.' \n");
  gotoxy(25, 18);
  printf("   '---'   \n");
  gotoxy(25, 19);
  printf("\n");
}

void welcomeToSnoopyGame() {
  system("cls"); // Clear the console
  setColor(14);
  int x = 14, y = 2;
  printf("\n");
  Sleep(50);
  gotoxy(x, y++);

  printf("  _________                                  \n");
  gotoxy(x, y++);
  Sleep(50);
  printf(" /   _____/ ____   ____   ____ ______ ___.__.\n");
  gotoxy(x, y++);
  Sleep(50);
  printf(" \\_____  \\ /    \\ /  _ \\ /  _ \\____ <   |  |\n");
  gotoxy(x, y++);
  Sleep(50);
  printf(" /        \\   |  (  <_> |  <_> )  |_> >___  |\n");
  gotoxy(x, y++);
  Sleep(50);
  printf("/_______  /___|  /\\____/ \\____/|   __// ____|\n");
  gotoxy(x, y++);
  Sleep(50);
  printf("        \\/     \\/              |__|   \\/     \n");
  gotoxy(x, y++);
  Sleep(50);
  printf("\n");
  gotoxy(x, y++);
  Sleep(50);
  printf("  Welcome to the Snoopy Adventure!\n");
  gotoxy(x, y++);
  Sleep(50);
  printf("  Press any key to start the journey...\n");
  gotoxy(x, y++);
  Sleep(50);

  // Wait for user input
  waitForAnyKey();

  return;
}

void pauseALL(void) {
  int i;

  gotoxy(28, 10);
  printf("**GAME     Paused**");

  waitForAnyKey();
  gotoxy(28, 23);
  printf("            ");

  return;
}
void exitYN(void) {
  char pressed;
  system("cls");
  gotoxy(9, 13);
  printf("Are you sure you want to exit(Y/N)\n");
  do {
    pressed = waitForAnyKey();
    pressed = tolower(pressed);
  } while (!(pressed == 'y' || pressed == 'n'));

  if (pressed == 'y') {
    system("cls"); //clear the console
    exit(1);
  }
  return;
}
void saveScore(int score) {
  FILE * file = fopen("score.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

void afficherNiveau(char niveau[HAUTEUR_NIVEAU][LARGEUR_NIVEAU], int posX, int posY, int ballX, int ballY, int * birdX, int * birdY) {
  
    gotoxy(posX,posY);
      printf("X");
      gotoxy(ballX,ballY);
      printf("O");
      for(int i=0;i<4;i++){
     gotoxy(birdX[i],birdY[i]);
     printf("B");
     }
     gotoxy(0,0);
     mazewall = 219; 
            // gotoxy(i,j);
     printf("%c", mazewall);
  
  gotoxy(1, 13);
  printf("score : %d", score);
  gotoxy(7, 14);
  printf("You have : ");
  for (int i=0; i < number_heart; i++) {
     printf(RED " %c " CRESET, HEART_SYMBOL);
  }

}

void gestionMouvement(char niveau[HAUTEUR_NIVEAU][LARGEUR_NIVEAU], int * posX, int * posY, int * ballX, int * ballY, int commande) {
  gotoxy(posX,posY);
      printf(" ");
  switch (commande) {

  case UP_ARROW:
    if ( * posY > 0 && niveau[ * posY - 1][ * posX] != 'a') {
      ( * posY) --;
    }
    break;
  case DOWN_ARROW:
    if ( * posY < HAUTEUR_NIVEAU - 1 && niveau[ * posY + 1][ * posX] != 'a') {
      ( * posY) ++;
    }
    break;
  case LEFT_ARROW:

    if ( * posX > 0 && niveau[ * posY][ * posX - 1] != 'a') {
      ( * posX) --;
    }
    break;
  case RIGHT_ARROW:
    if ( * posX < LARGEUR_NIVEAU - 1 && niveau[ * posY][ * posX + 1] != 'a') {
      ( * posX) ++;
    }
    break;
  case EXIT_BUTTON:
    exitYN();

    break;
  case PAUSE_BUTTON:
    pauseALL();
    break;
  }

  if ( *posX == *ballX && *posY == *ballY) {
    // Game over!
    number_heart--;
    
    if (number_heart == 0) {
      system("cls");
      gameOverScreen();
      Sleep(350);

      exit(1);
    } // Clear the consolesc
    // Exit the loop to end the game
  }
}

void updateBallPosition(int * ballX, int * ballY,int * posX, int * posY, int maxX, int maxY, int * ballDirectionX, int * ballDirectionY) {
   mazewall=219;
   if(niveau[*ballX][*ballY] != mazewall){
      gotoxy(*ballX,*ballY);
      printf(" ");}else{
        mazewall=219;
        printf("%c",mazewall);
      }
  // mise a jour ball pos
  ( * ballX) += ( * ballDirectionX);
  ( * ballY) += ( * ballDirectionY);

  // rencontre de  la balle avec borders
  if ( * ballX <= 1 || * ballX >= maxX - 2) {
    // Change direction hori
    ( * ballDirectionX) = -( * ballDirectionX);
  }

  if ( * ballY <= 1 || * ballY >= maxY - 2) {

    // Change direction verti
    ( * ballDirectionY) = -( * ballDirectionY);
  }
  
  if ( *posX == *ballX && *posY == *ballY) {
    // Game over!
    number_heart--;
    
    if (number_heart == 0) {
      system("cls");
      gameOverScreen();
      Sleep(350);

      exit(1);
    } // Clear the consolesc
    // Exit the loop to end the game
  }
}
void welcomeAnimation() {
  setColor(14);
  char t4[] = "\n\n\n\t\t>Appuyez sur {ENTRER} pour continuer<";
  for (int p = 0; p <= 100; p++) {
    system("cls");
    printf("\n\n\n\t\tChargement Du Jeu , Veuillez Patienter:\n\n\t\t\t\t %d%%\n\n", p);
    fflush(stdout);
    usleep(10000);
  }

  printf("\n\t\t\tLe Chargement est COMPLET !\n");

  for (int x = 0; t4[x] != '\0'; x++) {
    printf("%c", t4[x]);
    for (int y = 0; y <= 10000000; y++) {}
  }
  getch();
  system("cls");
  int i, l;
  char welcomeMessage[] = "\n\n\n\n\t\t Welcome to Snoopy!";

  for (i = 0; i < strlen(welcomeMessage); i++) {
    printf("%c", welcomeMessage[i]);
    Sleep(50);
  }
  puts("\n\n\n\t Press a key to continue");
  getch();
  system("cls");
}
void controls(void) {
  int x = 10, y = 5;
  system("cls");
  printf("Controls\n");
  gotoxy(x++, y++);
  printf("Use the following arrow keys to direct the Snoopy to the bird: ");
  gotoxy(x, y++);
  printf("Right Arrow");
  gotoxy(x, y++);
  printf("Left Arrow");
  gotoxy(x, y++);
  printf("Top Arrow");
  gotoxy(x, y++);
  printf("Bottom Arrow");
  gotoxy(x, y++);
  gotoxy(x, y++);
  printf("P & Esc pauses and escape the game.");
  gotoxy(x, y++);
  printf("Press any key to continue...");
  waitForAnyKey();
  return;
}

void loadGame() {

  

  int posX = 1;
  int posY = 1;
  int ballX = 5;
  int ballY = 5;
  int ballDirectionX = 1;

  int ballDirectionY = 1;
  int birdX[4];
  int birdY[4];
  for (int x = 0; x < 4; x++) {
    birdX[x] = rand() % LARGEUR_NIVEAU-1 ;
  }

  for (int x = 0; x < 4; x++) {
    birdY[x] = rand() % HAUTEUR_NIVEAU-1 ;
  }
  int commande;
  clock_t startTime;
  startTime = clock();
  int tim_hna = 0;
  int tim_hna_lib9a = 100;
  int tim_fin;
  
   system("cls");
      for (int i = 0; i < HAUTEUR_NIVEAU; i++) {
        for (int j = 0; j < LARGEUR_NIVEAU; j++) {
          if (i == posY && j == posX) {
            printf("X");
          } else if (i == ballY && j == ballX) {
            printf("0");
          } else if (i == birdY[0] && j == birdX[0] || i == birdY[1] && j == birdX[1] || i == birdY[2] && j == birdX[2] || i == birdY[3] && j == birdX[3]) {
            printf("B"); // Caractère pour représenter les oiseaux
          } else if (niveau[i][j] == 'a'){
            mazewall = 219; 
            // gotoxy(i,j);
            printf("%c", mazewall);// ASCII code for block character
          } else{
              mazewall = 32;
            //    gotoxy(i,j);
             printf("%c", mazewall); // ASCII code for space character
            }
                

            

        }
        printf("\n");

      }
  
  while (1) {

    tim_fin = tim_hna_lib9a - tim_hna;
    if (tim_fin < 0) {
      system("cls");
      gameOverScreen();
      exit(1);
    }
    gotoxy(posX,posY);
    printf(" ");
    afficherNiveau(niveau, posX, posY, ballX, ballY, birdX, birdY);
    
    //  gotoxy(12,13);
    //  char a="1F554";
    //  printf("%c",a);
    gotoxy(15, 13);
    printf("YOU HAVE : %d Sec", tim_fin);
    if (_kbhit()) {
      commande = getch();
      gotoxy(posX,posY);
      printf(" ");
      gestionMouvement(niveau, & posX, & posY, & ballX, & ballY, commande);
    }
    for (int i = 0; i < 4; i++) {
      if (posX == birdX[i] && posY == birdY[i]) {
        gotoxy(i, i);
        printf(" ");
        birdY[i] = 0;
        birdX[i] = 0;

        fin++;
        if (fin == 4) {
          system("cls");
          score = tim_fin * 100;
          youWinScreen();
          exit(1);
        }
        count = 1;
        // Augmenter le score lorsque Snoopy mange un oiseau
      }
    }
    if(niveau[ballX][ballY] != '219'){
      gotoxy(ballX,ballY);
      printf(" ");
      }else{
        mazewall=219;
        printf("%c",mazewall);
      }
    updateBallPosition( & ballX, & ballY, & posX, & posY, LARGEUR_NIVEAU, HAUTEUR_NIVEAU, & ballDirectionX, & ballDirectionY);
    // if ( posX == ballX && posY == ballY) {
    // // Game over!
    // number_heart--;
    // if (number_heart == 0) {
    //   system("cls");
    //   gameOverScreen();
    //   Sleep(350);

    //   exit(1);
    // } 
    // }
    tim_hna = (clock() - startTime) / CLOCKS_PER_SEC;
    Sleep(120);
    
      // gotoxy(posX,posY);
      // printf(" ");
  }
}

void mainMenu1() {

  printf(" ___  ___  ___  _____ _   _   ___  ___ _____ _   _ _   _ \n");
  Sleep(50);
  printf(" |  \\/  | / _ \\|_   _| \\ | |  |  \\/  ||  ___| \\ | | | | |\n");
  Sleep(50);
  printf(" | .  . |/ /_\\ \\ | | |  \\| |  | .  . || |__ |  \\| | | | |\n");
  Sleep(50);
  printf(" | |\\/| ||  _  | | | | . ` |  | |\\/| ||  __|| . ` | | | |\n");
  Sleep(50);
  printf(" | |  | || | | |_| |_| |\\  |  | |  | || |___| |\\  | |_| |\n");
  Sleep(50);
  printf(" \\_|  |_/\\_| |_/\\___/\\_| \\_/  \\_|  |_/\\____/\\_| \\_/\\___/ \n");
  Sleep(50);

}

char mainMenu() {
  char t1[] = "1-New Game\n";
  char t2[] = "2-High Scores\n";
  char t3[] = "3-Controls\n";
  char t4[] = "4-Exit\n";
  printf("here");
  int selected;

  system("cls"); //clear the console
  //Might be better with arrays of strings???
  mainMenu1();
  printf("\n\n\n\n\n");
  Sleep(50);
  int x, y;
  int a = 23, b = 16;
  gotoxy(a, b++);
  for (x = 0; t1[x] != '\0'; x++) {
    printf("%c", t1[x]);
    // for (y = 0; y <= 10000000; y++)
    Sleep(50);
  }
  gotoxy(a, b++);
  for (x = 0; t2[x] != '\0'; x++) {
    printf("%c", t2[x]);
    // for (y = 0; y <= 10000000; y++)
    Sleep(50);
  }

  gotoxy(a, b++);
  for (x = 0; t3[x] != '\0'; x++) {
    printf("%c", t3[x]);
    Sleep(50);
  }

  gotoxy(a, b++);
  for (x = 0; t4[x] != '\0'; x++) {
    printf("%c", t4[x]);
    Sleep(50);
  }
  // printf("                    2-High Scores\n");Sleep(50);
  // printf("                    3-Controls\n");Sleep(50);
  // printf("                    4-Exit\n");Sleep(50);

  selected = getch();
  return (selected);
}