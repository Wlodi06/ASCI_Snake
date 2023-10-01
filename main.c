#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <pthread.h> // Dla w¹tków
#include <time.h>

#define AREA_SIZE_X 40
#define AREA_SIZE_Y 20
//snake by Miko³aj w³odarzcyk 3tee
//github project

//            x             y
char area[AREA_SIZE_X][AREA_SIZE_Y];
int score = 0;
int snake_x_poz[AREA_SIZE_X*AREA_SIZE_Y] = {(AREA_SIZE_X-1)/2};
int snake_y_poz[AREA_SIZE_X*AREA_SIZE_Y] = {(AREA_SIZE_Y-1)/2};
char actual_dir;
int bscore = 0;


void area_outline()
{
  printf("Punkty: %i\n",score);
  //print x outline
  for(int i=0 ; i<AREA_SIZE_X-1 ; i++)
  {
      area[i][0] = '_';
      area[i][AREA_SIZE_Y-1] = '-';

  }
  //print y outline
  for(int i=1 ; i<AREA_SIZE_Y ; i++)
  {
      area[0][i] = '|';
      area[AREA_SIZE_X-1][i] = '|';
  }

}

void game_over()
{
        system("cls");
        printf("Gra skonczona zdobyles %i punktow\n",score);
        printf("nacisnij r aby zaczac grac od nowa");
        //wpisanie najlepszego wyniku
        if(score>bscore)bscore=score;
        Sleep(500);
        actual_dir = NULL;
        while(actual_dir != 'r' && actual_dir != 'R'){}
        score=0;

        for (int i = 0; i < (AREA_SIZE_X*AREA_SIZE_Y)-1; i++) {
        snake_x_poz[i] = 0;
        snake_y_poz[i] = 0;
        }
        snake_x_poz[0] = (AREA_SIZE_X-1)/2;
        snake_y_poz[0] = (AREA_SIZE_Y-1)/2;
        main();
}

//enter space in char
void area_space_DM()
{
    //y choose
  for(int y=0 ; y<AREA_SIZE_Y ; y++)
  {
  //x choose
    for(int x=0 ; x<AREA_SIZE_X ; x++)
    {
       area[x][y]=' ';
    }
  }
}

void DSP_cord_drw()
{
  //y choose
  for(int y=0 ; y<AREA_SIZE_Y ; y++)
  {
  //x choose
    for(int x=0 ; x<AREA_SIZE_X ; x++)
    {
       fprintf(stderr, "%c", area[x][y]);
    }
    //new line in y
    printf("\n");
  }
}

void display_refresh()
{
  //przesuniêcie na pozycje 0,0 w konsoli
  printf("\033[0;0H");
  area_outline();
  DSP_cord_drw();
  Sleep(100);

}
int x_oba=1,y_oba=1 ;
void obstacle(){

   if(snake_x_poz[0]==x_oba && snake_y_poz[0]==y_oba)score++;
   // Generowanie losowej liczby ca³kowitej w zakresie od 0 do RAND_MAX
   if(area[x_oba][y_oba] != 'o') x_oba = rand()% AREA_SIZE_X - 1;
   if(area[x_oba][y_oba] != 'o') y_oba = rand()% AREA_SIZE_Y - 1;
    area[x_oba][y_oba] = 'o';
   //wpisanie wartoœci do czêœci wê¿a
}
void collision()
{
   if((snake_x_poz[0]>=AREA_SIZE_X-1 || snake_x_poz[0]<= 0) || (snake_y_poz[0]>=AREA_SIZE_Y-1 || snake_y_poz[0]<= 0)) {
       game_over();
   }
}

void snake_move()
{

   switch (actual_dir) {
                case 'w':
                case 'W':
                         snake_y_poz[0]--;
                         area[snake_x_poz[0]][snake_y_poz[0]] = '*';
                    break;
                case 'a':
                case 'A':
                         snake_x_poz[0]--;
                         area[snake_x_poz[0]][snake_y_poz[0]] = '*';

                    break;
                case 's':
                case 'S':
                         snake_y_poz[0]++;
                         area[snake_x_poz[0]][snake_y_poz[0]] = '*';
                    break;
                case 'd':
                case 'D':
                         snake_x_poz[0]++;
                         area[snake_x_poz[0]][snake_y_poz[0]] = '*';
                    break;
            }

    //spawdzanie czy w¹¿ dotchn¹³ samgo soebie
    for (int i = score+3; i > 1; i--)
    {
       if(snake_x_poz[i]==snake_x_poz[0] && snake_y_poz[i]==snake_y_poz[0])
       {
           game_over();
       }
    }

     ///usuwanie * za wezem
       for (int i = score+3; i > 0; i--) {
        snake_x_poz[i]=snake_x_poz[i-1];
         snake_y_poz[i]=snake_y_poz[i-1];
    }
     area[snake_x_poz[score+3]][snake_y_poz[score+3]] = ' ';
}

  char actual_dir;
// Funkcja do wykonywania w¹tku odpowiedzialnego za sprawdzanie klawiszy
void* snake_control(void* arg) {

    while (1) {
        if (_kbhit()) {
            actual_dir = _getch();
        }
        Sleep(50); // OpóŸnienie sprawdzania klawiszy w tle
    }
    return NULL;
}


void game_loop()
{
   bool game_over = true;

   while(game_over)
   {

     snake_move();
     obstacle();
     collision();

    display_refresh();
   //pobierz kierunek
   }

}
void start()
{
  printf("ASCI Snake project\n");
printf("By Mikolaj Wlodarczyk\n");
printf("----------------------\n");
printf("najlepszy wynik : %i\n",bscore);
printf("----------------------\n");
printf("nacisnij w aby zaczac grac...\n");
printf("\n");
  while(actual_dir != 'w' && actual_dir != 'W'){}
  system("cls");
  system("color 70");
}

int main()
{

    system("cls");
    srand(time(NULL)); //inicjalizacja losowych liczb
           pthread_t thread; // Identyfikator w¹tku
//snake cord

    // Tworzenie w¹tku do wykonywania funkcji w czasie opóŸnienia
    if (pthread_create(&thread, NULL, snake_control, NULL) != 0) {
        perror("B³¹d podczas tworzenia w¹tku.");
        return 1;
    }

    //zmiania koloru
    system("color 07");

    //wpisanie spacji do char
    area_space_DM();
    //wpisanie kontur
    area_outline();
    //narysowanie kontur
    DSP_cord_drw();
    //pêtla gry
    start();
    //pêtla gry
    game_loop();

    return 0;
}
