#include "mbox.h"
#include "framebf.h"
#include "../uart/uart1.h"
#include "../uart/uart0.h"
#include "../gcclib/stddef.h"
#include "gpio.h"

// #include "../image/earth.h"
// #include "../image/mars.h"
// #include "../image/uranus.h"

// #include "../image/bigmoon.h"

#define MAX_CMD_SIZE 100

/*
Compare string function to compare the input of the user with
the command to see if they match */
// ref: https://stackoverflow.com/questions/14232990/comparing-two-strings-in-c
int stringcp(char arrayA[], char arrayB[])
{
    int boolean;
    int count = 0;

    while (arrayA[count] == arrayB[count])
    {
        if (arrayA[count] == '\0' || arrayB[count] == '\0')
        {
            break;
        }
        count++;
    }
    if (arrayA[count] == '\0' && arrayB[count] == '\0')
    {
        return boolean = 1;
    }
    else
    {
        return boolean = 0;
    }
}

void cli()
{
    static char cli_buffer[MAX_CMD_SIZE];
    static int index = 0;
    // read and send back each char
    char c = uart_getc();
    uart_sendc(c);

    // For BACKSPACE to delete previous characters
    if (c == '\b')
    {
        if (index > 0)
        {
            index--;
            uart_puts(" \b");
        }

        else
        {
            // Will simply print a whitespace everytime the user press backspace. To avoid deleting the OS
            uart_puts(" ");
        }
    }

    else if (c != '\n')
    {
        cli_buffer[index] = c; // Store into the buffer
        index++;
    }

    else if (c == '\n')
    {
        cli_buffer[index] = '\0';
        uart_puts("\nGot commands: ");
        uart_puts(cli_buffer);
        uart_puts("\n");

        // Show commands
        if (stringcp(cli_buffer, "help") == 1)
        {
            uart_puts("video		Display a short video on virtual machine, press 's' to start or replay video\n");
            uart_puts("slideshow	Display 3 images, press 'd' to view next image and 'a' to view previous one\n");
            uart_puts("view	        Display an image larger than the VM, press 'w' and 's' to view up and down, 'a' and 'd' for left and right\n");
            uart_puts("names           Display the name of team members\n");
            uart_puts("play            To play a game\n");

            uart_puts("clear		Clear screen\n");
        }

        // clear command
        else if (stringcp(cli_buffer, "clear") == 1)
        {
            uart_puts("\e[1;1H\e[2J");
        }

        // Show video
        else if (stringcp(cli_buffer, "video") == 1)
        {
            video();
        }

        // Show slideshow
        else if (stringcp(cli_buffer, "slideshow") == 1)
        {
            slideshow();
        }

        // Show view
        else if (stringcp(cli_buffer, "view") == 1)
        {
            view();
        }

        else if (stringcp(cli_buffer, "names") == 1)
        {
            names();
        }

        else if (stringcp(cli_buffer, "play") == 1)
        {
            // game();
            game2();
        }

        // display error message if there is some typo error
        else if (stringcp(cli_buffer, "") == 1)
        {
            uart_puts("Please type a commmand !\n");
        }
        else
        {
            uart_puts("Did not understand command, please try again.\n");
        }

        // Return to the OS
        uart_puts("\nGroup24OS> ");

        // Return to command line
        index = 0;
    }
}

void main()
{

    // set up serial console
    uart_init();
    // Welcome Message

    uart_puts("\033[36m");

    uart_puts("\n\n");
    uart_puts("######## ######## ######## ########  #######  ##         #######    ##### \n");
    uart_puts("##       ##       ##          ##    ##     ## ##    ##  ##     ##  ##   ## \n");
    uart_puts("##       ##       ##          ##           ## ##    ##  ##     ## ##     ## \n");
    uart_puts("######   ######   ######      ##     #######  ##    ##   ######## ##     ## \n");
    uart_puts("##       ##       ##          ##    ##        #########        ## ##     ##  \n");
    uart_puts("##       ##       ##          ##    ##              ##  ##     ##  ##   ##   \n");
    uart_puts("######## ######## ########    ##    #########       ##   #######    #####   \n");
    uart_puts("\n\n\n");
    uart_puts("########     ###    ########  ########     #######   ######\n");
    uart_puts("##     ##   ## ##   ##     ## ##          ##     ## ##    ##\n");
    uart_puts("##     ##  ##   ##  ##     ## ##          ##     ## ##\n");
    uart_puts("########  ##     ## ########  ######      ##     ##  ######\n");
    uart_puts("##     ## ######### ##   ##   ##          ##     ##       ##\n");
    uart_puts("##     ## ##     ## ##    ##  ##          ##     ## ##    ##\n");
    uart_puts("########  ##     ## ##     ## ########     #######   ######\n\n\n");

    uart_puts("Developed by Bui Dang Dac Duong - S3764487\n");
    uart_puts("Developed by Nguyen Minh Quang - S3878631\n");
    uart_puts("Developed by Nguyen Hoang Phuong - S3924593\n");
    uart_puts("Developed by Tran Xuan Hoang Dat - S3651550\n\n\n");

    uart_puts("Type 'help' into the terminal for commands information\n");

    // Initialize frame buffer
    framebf_init(0, 0);
    uart_puts("\nGroup24OS> ");

    while (1)
    {

        cli();
    }
}
