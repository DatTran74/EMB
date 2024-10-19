#include "framebf.h"
#include "mbox.h"
#include "../uart/uart1.h"
#include "../uart/uart0.h"
#include "../gcclib/stddef.h"
#include "gpio.h"

// Functions that given by teacher
///////////

unsigned int uart_isReadByteReady()
{
    return (AUX_MU_LSR & 0x01);
}

unsigned char getUart()
{
    unsigned char ch = 0;

    if (uart_isReadByteReady())
        ch = uart_getc();
    return ch;
}
void wait_ms(unsigned int n)
{
    register unsigned long f, t, r, expiredTime;

    // Get the current counter frequency (Hz)
    asm volatile("mrs %0, cntfrq_el0"
                 : "=r"(f));

    // Read the current counter value
    asm volatile("mrs %0, cntpct_el0"
                 : "=r"(t));

    // Calculate expire value for counter
    expiredTime = t + ((f / 1000) * n) / 1000;
    do
    {
        asm volatile("mrs %0, cntpct_el0"
                     : "=r"(r));
    } while (r < expiredTime);
}

///////////

struct Walls
{
    int x1, y1, x2, y2, w, h;
} wall1, wall2, wall3, wall4, wall5, wall6, wall7, wall8, wall9, wall10, wall11, wall12, wall13, wall14, wall15, wall16, wall17, wall18, wall19, wall20;

struct Monsters
{
    int x1, y1, x2, y2, w, h, velocity;
} monster1, monster2, monster3;

struct Player
{
    int x1, y1, x2, y2, w, h, velocityUP, velocityDOWN, velocityLEFT, velocityRIGHT, lives;
} player;

enum stateOfGame
{
    welcomeScreen,
    play,
    win,
    lose,
    quit
};

void initGame();
void resetGame();
void drawElements(int *textScale);
void detectWallCollision();
void winCon(enum stateOfGame *state);
void loseCon(enum stateOfGame *state);

void game2()
{
    // int textScale1 = 1;
    int textScale2 = 2;
    // int textScale3 = 3;
    int textScale4 = 4;

    framebf_init(0, 0);
    drawRectARGB32(0, 0, 2000, 2000, 0x00070200, 1); // CLEAR SCREEN
    uart_puts("\nPlease look at the virtual machine and open the terminal side by side for control\n");

    enum stateOfGame stateOfGame;
    stateOfGame = welcomeScreen;

    char move = getUart();

    while (1)
    {
        if (stateOfGame == welcomeScreen)
        {
            drawString(SCR_WIDTH / 2 - 200, 262, "Pax Man Adventure", 0xe, textScale4);
            drawString(SCR_WIDTH / 2 - 240, 300, "Press ENTER to play", 0xf, textScale4);

            drawString(SCR_WIDTH / 2 - 200, 350, "Authors", 0x0a, textScale2);
            drawString(SCR_WIDTH / 2 - 200, 400, "Bui Dang Dac Duong - S3764487", 0x0a, textScale2);
            drawString(SCR_WIDTH / 2 - 200, 450, "Nguyen Minh Quang - S3878631", 0x0b, textScale2);
            drawString(SCR_WIDTH / 2 - 200, 500, "Nguyen Hoang Phuong - S3924593", 0x0c, textScale2);
            drawString(SCR_WIDTH / 2 - 200, 550, "Tran Xuan Hoang Dat - S3651550", 0x0d, textScale2);
            char move = getUart();

            if (move == '\n')
            {
                stateOfGame = play;
                initGame();
            }
        }
        while (stateOfGame == play)
        {

            // player movement
            move = getUart();
            if (move == 'w')
            {
                if (player.y1 > 0)
                {
                    player.y1 -= player.velocityUP;
                    uart_puts("player x1: ");
                    uart_dec(player.x1);
                    uart_puts(" \n");
                    uart_puts("player y1: ");
                    uart_dec(player.y1);
                    uart_puts(" \n");
                    uart_puts("player x2: ");
                    uart_dec(player.x2);
                    uart_puts(" \n");
                    uart_puts("player y2: ");
                    uart_dec(player.y2);
                    uart_puts(" \n");
                    uart_puts(" \n");
                }
            }

            else if (move == 'd')
            {
                if (player.x2 < 1024 - 20)
                {
                    player.x1 += player.velocityRIGHT;
                    uart_puts("player x1: ");
                    uart_dec(player.x1);
                    uart_puts(" \n");
                    uart_puts("player y1: ");
                    uart_dec(player.y1);
                    uart_puts(" \n");
                    uart_puts("player x2: ");
                    uart_dec(player.x2);
                    uart_puts(" \n");
                    uart_puts("player y2: ");
                    uart_dec(player.y2);
                    uart_puts(" \n");
                    uart_puts(" \n");
                }
            }
            else if (move == 's')
            {
                if (player.y2 < 768 - 20)
                {
                    player.y1 += player.velocityDOWN;
                    uart_puts("player x1: ");
                    uart_dec(player.x1);
                    uart_puts(" \n");
                    uart_puts("player y1: ");
                    uart_dec(player.y1);
                    uart_puts(" \n");
                    uart_puts("player x2: ");
                    uart_dec(player.x2);
                    uart_puts(" \n");
                    uart_puts("player y2: ");
                    uart_dec(player.y2);
                    uart_puts(" \n");
                    uart_puts(" \n");
                }
            }
            else if (move == 'a')
            {
                if (player.x1 > 0)
                {
                    player.x1 -= player.velocityLEFT;
                    uart_puts("player x1: ");
                    uart_dec(player.x1);
                    uart_puts(" \n");
                    uart_puts("player y1: ");
                    uart_dec(player.y1);
                    uart_puts(" \n");
                    uart_puts("player x2: ");
                    uart_dec(player.x2);
                    uart_puts(" \n");
                    uart_puts("player y2: ");
                    uart_dec(player.y2);
                    uart_puts(" \n");
                    uart_puts(" \n");
                }
            }
            else if (move == '\n')
            {
                stateOfGame = quit;
            }

            else if (move == 'r')
            {
                stateOfGame = win;
            }

            // revert direction if monsters touch top or bottom edge
            if (monster1.y2 > wall19.y1 - 30 || monster1.y1 < 0)
                monster1.velocity = -monster1.velocity;
            if (monster2.y2 > SCR_HEIGHT || monster2.y1 < wall4.y1 + 30)
                monster2.velocity = -monster2.velocity;
            if (monster3.y2 > wall16.y1 || monster3.y1 < wall7.y1 + 30)
                monster3.velocity = -monster3.velocity;

            // update the other edge of the player and the boxes
            player.x2 = player.x1 + player.w;
            player.y2 = player.y1 + player.h;

            monster1.y1 += monster1.velocity;
            monster1.y2 = monster1.y1 + monster1.h;

            monster2.y1 += monster2.velocity;
            monster2.y2 = monster2.y1 + monster2.h;

            monster3.y1 += monster3.velocity;
            monster3.y2 = monster3.y1 + monster3.h;

            // wall collision detection
            detectWallCollision();

            winCon(&stateOfGame);

            loseCon(&stateOfGame);

            drawElements(&textScale2);

            wait_ms(50000); // The more we delay, the less the flickering, however, there will be more bugs :(

            // drawRect(0, 0, 1024, 768, 0x00070200, 1);
            drawRectARGB32(0, 0, 1024, 768, 0x00070200, 1); // flickering the screen to improve stability of the game
        }
        while (stateOfGame == win)
        {
            char ch1 = getUart();

            // uart_puts("YOU WIN!!");
            drawString(SCR_WIDTH / 2 - 150, 200, "YOU WIN!!", 0xA, textScale4);

            drawString(SCR_WIDTH / 2 - 200, 300, "Press SPACEBAR to try again", 0x2, textScale2);

            drawString(SCR_WIDTH / 2 - 200, 400, "Press 'q' to quit the game", 0xB, textScale2);

            if (ch1 == ' ')
            {
                player.lives = 3;
                resetGame();
                stateOfGame = play; // come back to the play state
            }
            else if (ch1 == 'q')
            {
                stateOfGame = quit;
            }
        }

        while (stateOfGame == lose)
        {
            char ch = getUart();

            // uart_puts("YOU LOSE!!");
            drawString(SCR_WIDTH / 2 - 150, 300, "YOU LOSE!!", 0xC, textScale4);
            drawString(SCR_WIDTH / 2 - 200, 350, "Press SPACEBAR to try again", 0x2, textScale2);
            drawString(SCR_WIDTH / 2 - 200, 400, "Press 'q' to quit the game", 0xB, textScale2);

            if (ch == ' ')
            {
                player.lives = 3;
                resetGame();
                stateOfGame = play; // come back to the play state
            }
            else if (ch == 'q')
            {
                stateOfGame = quit;
            }
        }

        if (stateOfGame == quit)
        {
            drawRectARGB32(0, 0, 2000, 2000, 0x00070200, 1); // CLEAR SCREEN
            uart_puts("GAME QUIT");
            drawString(SCR_WIDTH / 2 - 150, 400, "YOU QUIT!!", 0xe, textScale4);
            break;
        }
    }
}

void initGame()
{
    // wall 1
    wall1.x1 = 0;
    wall1.y1 = 200;
    wall1.w = 120;
    wall1.h = 5;

    wall1.x2 = wall1.x1 + wall1.w;
    wall1.y2 = wall1.y1 + wall1.h;

    // wall 2
    wall2.x1 = 120;
    wall2.y1 = 0;
    wall2.w = 5;
    wall2.h = 200;

    wall2.x2 = wall2.x1 + wall2.w;
    wall2.y2 = wall2.y1 + wall2.h;

    // wall 3
    wall3.x1 = 240;
    wall3.y1 = 0;
    wall3.w = 5;
    wall3.h = 260;

    wall3.x2 = wall3.x1 + wall3.w;
    wall3.y2 = wall3.y1 + wall3.h;

    // wall 4
    wall4.x1 = 240;
    wall4.y1 = 260;
    wall4.w = 220;
    wall4.h = 5;

    wall4.x2 = wall4.x1 + wall4.w;
    wall4.y2 = wall4.y1 + wall4.h;

    // wall 5
    wall5.x1 = wall4.x1 + wall4.w; //= 480
    wall5.y1 = 0;
    wall5.w = 5;
    wall5.h = 260;

    wall5.x2 = wall5.x1 + wall5.w;
    wall5.y2 = wall5.y1 + wall5.h;

    // wall 6
    wall6.x1 = wall5.x1 + 160;
    wall6.y1 = 0;
    wall6.w = 5;
    wall6.h = 100;

    wall6.x2 = wall6.x1 + wall6.w;
    wall6.y2 = wall6.y1 + wall6.h;

    // wall 7
    wall7.x1 = wall6.x1;
    wall7.y1 = wall6.h;
    wall7.w = 240;
    wall7.h = 5;

    wall7.x2 = wall7.x1 + wall7.w;
    wall7.y2 = wall7.y1 + wall7.h;

    // wall 8
    wall8.x1 = wall7.x1 + wall7.w;
    wall8.y1 = 0;
    wall8.w = 5;
    wall8.h = 100;

    wall8.x2 = wall8.x1 + wall8.w;
    wall8.y2 = wall8.y1 + wall8.h;

    // wall 9
    wall9.x1 = wall8.x1 - 40;
    wall9.y1 = wall8.h + 80;
    wall9.w = 220;
    wall9.h = 5;

    wall9.x2 = wall9.x1 + wall9.w;
    wall9.y2 = wall9.y1 + wall9.h;

    // wall 10
    wall10.x1 = wall9.x1;
    wall10.y1 = wall9.y1;
    wall10.w = 5;
    wall10.h = 180;

    wall10.x2 = wall10.x1 + wall10.w;
    wall10.y2 = wall10.y1 + wall10.h;

    // wall 11
    wall11.x1 = wall10.x1;
    wall11.y1 = wall10.h * 2;
    wall11.w = 220;
    wall11.h = 5;

    wall11.x2 = wall11.x1 + wall11.w;
    wall11.y2 = wall11.y1 + wall11.h;

    // wall 12
    wall12.x1 = wall10.x1 - 240;
    wall12.y1 = wall10.h + 40;
    wall12.w = 5;
    wall12.h = 180;

    wall12.x2 = wall12.x1 + wall12.w;
    wall12.y2 = wall12.y1 + wall12.h;

    // wall 13
    wall13.x1 = wall12.x1;
    wall13.y1 = wall12.y1;
    wall13.w = 140;
    wall13.h = 5;

    wall13.x2 = wall13.x1 + wall13.w;
    wall13.y2 = wall13.y1 + wall13.h;

    // wall 14
    wall14.x1 = wall13.x1 + wall13.w;
    wall14.y1 = wall13.y1;
    wall14.w = 5;
    wall14.h = 180;

    wall14.x2 = wall14.x1 + wall14.w;
    wall14.y2 = wall14.y1 + wall14.h;

    // wall 15
    wall15.x1 = wall12.x1;
    wall15.y1 = wall12.y1 + wall12.h;
    wall15.w = 140;
    wall15.h = 5;

    wall15.x2 = wall15.x1 + wall15.w;
    wall15.y2 = wall15.y1 + wall15.h;

    // wall 16
    wall16.x1 = wall15.x1 + 60;
    wall16.y1 = wall15.y1 + 100;
    wall16.w = 5;
    wall16.h = 260;

    wall16.x2 = wall16.x1 + wall16.w;
    wall16.y2 = wall16.y1 + wall16.h;

    // wall 17
    wall17.x1 = wall16.x1;
    wall17.y1 = wall16.y1;
    wall17.w = 240;
    wall17.h = 5;

    wall17.x2 = wall17.x1 + wall17.w;
    wall17.y2 = wall17.y1 + wall17.h;

    // wall 18
    wall18.x1 = wall17.x1 + wall17.w;
    wall18.y1 = wall17.y1;
    wall18.w = 5;
    wall18.h = 260;

    wall18.x2 = wall18.x1 + wall18.w;
    wall18.y2 = wall18.y1 + wall18.h;

    // wall 19
    wall19.x1 = 0;
    wall19.y1 = wall18.y1 - 40;
    wall19.w = 340;
    wall19.h = 5;

    wall19.x2 = wall19.x1 + wall19.w;
    wall19.y2 = wall19.y1 + wall19.h;

    // wall 20
    wall20.x1 = wall19.w;
    wall20.y1 = wall19.y1;
    wall20.w = 5;
    wall20.h = 300;

    wall20.x2 = wall20.x1 + wall20.w;
    wall20.y2 = wall20.y1 + wall20.h;

    // player
    player.x1 = 40;
    player.y1 = 360; // SCR_HEIGHT = 768, player.y1 = 314
    player.w = 20;
    player.h = 20;
    player.x2 = player.x1 + player.w;
    player.y2 = player.y1 + player.h;
    player.lives = 3;
    player.velocityUP = 20;
    player.velocityDOWN = 20;
    player.velocityLEFT = 20;
    player.velocityRIGHT = 20;

    // monster 1
    monster1.x1 = 150;
    monster1.y1 = 100;
    monster1.w = 60;
    monster1.h = 80;

    monster1.x2 = monster1.x1 + monster1.w;
    monster1.y2 = monster1.y1 + monster1.h;
    monster1.velocity = 25;

    // monster 2
    monster2.x1 = 400;
    monster2.y1 = 500;
    monster2.w = 40;
    monster2.h = 180;

    monster2.x2 = monster2.x1 + monster2.w;
    monster2.y2 = monster2.y1 + monster2.h;
    monster2.velocity = -30;

    // monster 3
    monster3.x1 = 740;
    monster3.y1 = 500;
    monster3.w = 60;
    monster3.h = 80;

    monster3.x2 = monster3.x1 + monster3.w;
    monster3.y2 = monster3.y1 + monster3.h;
    monster3.velocity = 80;
}

void resetGame()
{
    // RESET EVERYTHING

    // player
    player.x1 = 40;
    player.y1 = 360; // SCR_HEIGHT = 768
    player.x2 = player.x1 + player.w;
    player.y2 = player.y1 + player.h;

    // monster 1
    monster1.x1 = 150;
    monster1.y1 = 100;
    monster1.x2 = monster1.x1 + monster1.w;
    monster1.y2 = monster1.y1 + monster1.h;

    // monster 2
    monster2.x1 = 400;
    monster2.y1 = 500;
    monster2.x2 = monster2.x1 + monster2.w;
    monster2.y2 = monster2.y1 + monster2.h;

    // HAVE TO COMMENT OUT THIS SECTION DUE TO POTENTIAL BUG PROBLEM
    //  monster 3
    // monster3.x1 = 760;
    // monster3.y1 = 500;
    // monster3.x2 = monster3.x1 + monster3.w;
    // monster3.y2 = monster3.y1 + monster3.h;
}

void drawElements(int *textScale)
{
    // Draw things and stuffs, SCR_HEIGHT = 768
    // TREASURE
    drawCircle(960, 600, 20, 0x33, 1);
    // PAX MAN (PLAYER)
    drawRect(player.x1, player.y1, player.x2, player.y2, 0x9, 1);

    // MONSTERS
    drawRect(monster1.x1, monster1.y1, monster1.x2, monster1.y2, 0xA, 1);
    drawRect(monster2.x1, monster2.y1, monster2.x2, monster2.y2, 0xE, 1);
    drawRect(monster3.x1, monster3.y1, monster3.x2, monster3.y2, 0xC, 1);

    // WALLS
    drawRect(wall1.x1, wall1.y1, wall1.x2, wall1.y2, 0xB, 1);     // wall 1
    drawRect(wall2.x1, wall2.y1, wall2.x2, wall2.y2, 0xB, 1);     // wall 2
    drawRect(wall3.x1, wall3.y1, wall3.x2, wall3.y2, 0xB, 1);     // wall 3
    drawRect(wall4.x1, wall4.y1, wall4.x2, wall4.y2, 0xB, 1);     // wall 4
    drawRect(wall5.x1, wall5.y1, wall5.x2, wall5.y2, 0xB, 1);     // wall 5
    drawRect(wall6.x1, wall6.y1, wall6.x2, wall6.y2, 0xB, 1);     // wall 6
    drawRect(wall7.x1, wall7.y1, wall7.x2, wall7.y2, 0xB, 1);     // wall 7
    drawRect(wall8.x1, wall8.y1, wall8.x2, wall8.y2, 0xB, 1);     // wall 8
    drawRect(wall9.x1, wall9.y1, wall9.x2, wall9.y2, 0xB, 1);     // wall 9
    drawRect(wall10.x1, wall10.y1, wall10.x2, wall10.y2, 0xB, 1); // wall 10
    drawRect(wall11.x1, wall11.y1, wall11.x2, wall11.y2, 0xB, 1); // wall 11
    drawRect(wall12.x1, wall12.y1, wall12.x2, wall12.y2, 0xB, 1); // wall 12
    drawRect(wall13.x1, wall13.y1, wall13.x2, wall13.y2, 0xB, 1); // wall 13
    drawRect(wall14.x1, wall14.y1, wall14.x2, wall14.y2, 0xB, 1); // wall 14
    drawRect(wall15.x1, wall15.y1, wall15.x2, wall15.y2, 0xB, 1); // wall 15
    drawRect(wall16.x1, wall16.y1, wall16.x2, wall16.y2, 0xB, 1); // wall 16
    drawRect(wall17.x1, wall17.y1, wall17.x2, wall17.y2, 0xB, 1); // wall 17
    drawRect(wall18.x1, wall18.y1, wall18.x2, wall18.y2, 0xB, 1); // wall 18
    drawRect(wall19.x1, wall19.y1, wall19.x2, wall19.y2, 0xB, 1); // wall 19
    drawRect(wall20.x1, wall20.y1, wall20.x2, wall20.y2, 0xB, 1); // wall 20

    // LIVES
    // drawRect(20, 600, 60, 640, 0x00070200, 1);
    drawString(20, 520, "Lives Remaining: ", 0xC, *textScale);
    switch (player.lives)
    {
    case 3:
        drawString(20, 560, "3", 0xC, *textScale);
        break;
    case 2:
        drawString(20, 560, "2", 0xC, *textScale);
        break;
    case 1:
        drawString(20, 560, "1", 0xC, *textScale);
        break;
    default:
        break;
    }
    drawString(20, 640, "Press 'r' for magic ", 0xF, *textScale);
}

void detectWallCollision()
{
    // wall 1
    if ((player.y1 >= wall1.y1 - 20 && player.y2 <= wall1.y2 + 20) && (player.x1 >= wall1.x1 - 10 && player.x2 <= wall1.x2 + 10))
        player.velocityUP = 0;

    // wall 2
    else if ((player.y1 >= wall2.y1 - 10 && player.y2 <= wall2.y2 + 10) && (player.x1 >= wall2.x1 - 20 && player.x2 <= wall2.x2 + 20))
        player.velocityLEFT = 0;

    // wall 3
    else if ((player.y1 >= wall3.y1 - 10 && player.y2 <= wall3.y2 + 10) && (player.x1 >= wall3.x1 - 20 && player.x2 <= wall3.x2 + 20))
        player.velocityRIGHT = 0;

    // wall 4
    else if ((player.y1 >= wall4.y1 - 20 && player.y2 <= wall4.y2 + 20) && (player.x1 >= wall4.x1 - 10 && player.x2 <= wall4.x2 + 10))
        player.velocityUP = 0;
    // wall 5
    else if ((player.y1 >= wall5.y1 - 10 && player.y2 <= wall5.y2 + 10) && (player.x1 >= wall5.x1 - 20 && player.x2 <= wall5.x2 + 20))
        player.velocityLEFT = 0;

    // wall 6
    else if ((player.y1 >= wall6.y1 - 10 && player.y2 <= wall6.y2 + 10) && (player.x1 >= wall6.x1 - 20 && player.x2 <= wall6.x2 + 20))
        player.velocityRIGHT = 0;

    // wall 7
    else if ((player.y1 >= wall7.y1 - 20 && player.y2 <= wall7.y2 + 20) && (player.x1 >= wall7.x1 - 10 && player.x2 <= wall7.x2 + 10))
        player.velocityUP = 0;

    // wall 8
    else if ((player.y1 >= wall8.y1 - 10 && player.y2 <= wall8.y2 + 10) && (player.x1 >= wall8.x1 - 20 && player.x2 <= wall8.x2 + 20))
        player.velocityLEFT = 0;

    // wall 9
    else if ((player.y1 >= wall9.y1 - 20 && player.y2 <= wall9.y2 + 20) && (player.x1 >= wall9.x1 - 10 && player.x2 <= wall9.x2 + 10))
        player.velocityDOWN = 0;

    // wall 10
    else if ((player.y1 >= wall10.y1 - 10 && player.y2 <= wall10.y2 + 10) && (player.x1 >= wall10.x1 - 20 && player.x2 <= wall10.x2 + 20))
        player.velocityRIGHT = 0;

    // wall 11
    else if ((player.y1 >= wall11.y1 - 20 && player.y2 <= wall11.y2 + 20) && (player.x1 >= wall11.x1 - 10 && player.x2 <= wall11.x2 + 10))
        player.velocityUP = 0;

    // wall 12
    else if ((player.y1 >= wall12.y1 - 10 && player.y2 <= wall12.y2 + 10) && (player.x1 >= wall12.x1 - 20 && player.x2 <= wall12.x2 + 20))
        player.velocityRIGHT = 0;

    // wall 13
    else if ((player.y1 >= wall13.y1 - 20 && player.y2 <= wall13.y2 + 20) && (player.x1 >= wall13.x1 - 10 && player.x2 <= wall13.x2 + 10))
        player.velocityDOWN = 0;

    // wall 14
    else if ((player.y1 >= wall14.y1 - 10 && player.y2 <= wall14.y2 + 10) && (player.x1 >= wall14.x1 - 20 && player.x2 <= wall14.x2 + 20))
        player.velocityLEFT = 0;

    // wall 15
    else if ((player.y1 >= wall15.y1 - 20 && player.y2 <= wall15.y2 + 20) && (player.x1 >= wall15.x1 - 10 && player.x2 <= wall15.x2 + 10))
        player.velocityUP = 0;

    // wall 16
    else if ((player.y1 >= wall16.y1 - 10 && player.y2 <= wall16.y2 + 10) && (player.x1 >= wall16.x1 - 20 && player.x2 <= wall16.x2 + 20))
        player.velocityRIGHT = 0;

    // wall 17
    else if ((player.y1 >= wall17.y1 - 20 && player.y2 <= wall17.y2 + 20) && (player.x1 >= wall17.x1 - 10 && player.x2 <= wall17.x2 + 10))
        player.velocityDOWN = 0;

    // wall 18
    else if ((player.y1 >= wall18.y1 - 10 && player.y2 <= wall18.y2 + 10) && (player.x1 >= wall18.x1 - 20 && player.x2 <= wall18.x2 + 20))
        player.velocityLEFT = 0;

    // wall 19
    else if ((player.y1 >= wall19.y1 - 20 && player.y2 <= wall19.y2 + 20) && (player.x1 >= wall19.x1 - 10 && player.x2 <= wall19.x2 + 10))
        player.velocityDOWN = 0;

    // wall 20
    else if ((player.y1 >= wall20.y1 - 10 && player.y2 <= wall20.y2 + 10) && (player.x1 >= wall20.x1 - 20 && player.x2 <= wall20.x2 + 20))
        player.velocityLEFT = 0;

    else
    {
        player.velocityUP = 20;
        player.velocityDOWN = 20;

        player.velocityLEFT = 20;
        player.velocityRIGHT = 20;
    }
}

void winCon(enum stateOfGame *state)
{

    // detect collision with FOOD
    if ((player.x1 >= 960 - 20 && player.x2 <= 960 + 20) && (player.y1 >= 600 - 20 && player.y2 <= 600 + 20))
    {
        *state = win;
    }
}

void loseCon(enum stateOfGame *state)
{
    // detect collision with monster1
    if ((player.y1 >= monster1.y1 - 20 && player.y2 <= monster1.y2 + 20) && (player.x1 >= monster1.x1 - 20 && player.x2 <= monster1.x2 + 20))
    {
        player.lives--;
        resetGame();
    }

    // detect collision with monster2
    if ((player.y1 > monster2.y1 - 20 && player.y2 < monster2.y2 + 20) && (player.x1 > monster2.x1 - 20 && player.x2 < monster2.x2 + 20))
    {
        player.lives--;
        resetGame();
    }

    // detect collision with monster3
    if ((player.y1 > monster3.y1 - 20 && player.y2 < monster3.y2 + 20) && (player.x1 > monster3.x1 - 20 && player.x2 < monster3.x2 + 20))
    {
        player.lives--;
        resetGame();
    }

    if (player.lives < 1)
    {
        *state = lose;
    }
}