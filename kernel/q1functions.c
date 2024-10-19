#include "mbox.h"
#include "framebf.h"
#include "../uart/uart1.h"
#include "../uart/uart0.h"
#include "../gcclib/stddef.h"
#include "gpio.h"

#include "../videoimage/image1.h"
#include "../videoimage/image2.h"
#include "../videoimage/image3.h"
#include "../videoimage/image4.h"
#include "../videoimage/image5.h"
#include "../videoimage/image6.h"
#include "../videoimage/image7.h"
#include "../videoimage/image8.h"
#include "../videoimage/image9.h"
#include "../videoimage/image10.h"
#include "../videoimage/image11.h"
#include "../videoimage/image12.h"
#include "../videoimage/image13.h"
#include "../videoimage/image14.h"
#include "../videoimage/image15.h"
#include "../videoimage/image16.h"
#include "../videoimage/image17.h"
#include "../videoimage/image18.h"
#include "../videoimage/image19.h"
#include "../videoimage/image20.h"
#include "../videoimage/image21.h"
#include "../videoimage/image22.h"
#include "../videoimage/image23.h"
#include "../videoimage/image24.h"
#include "../videoimage/image25.h"
#include "../videoimage/image26.h"
#include "../videoimage/image27.h"
#include "../videoimage/image28.h"
#include "../videoimage/image29.h"
#include "../videoimage/image30.h"
#include "../videoimage/image31.h"
#include "../videoimage/image32.h"
#include "../videoimage/image33.h"
#include "../videoimage/image34.h"
#include "../videoimage/image35.h"
#include "../videoimage/image36.h"
#include "../videoimage/image37.h"
#include "../videoimage/image38.h"
#include "../videoimage/image39.h"
#include "../videoimage/image40.h"
#include "../videoimage/image41.h"
#include "../videoimage/image42.h"
#include "../videoimage/image43.h"
#include "../videoimage/image44.h"
#include "../videoimage/image45.h"
#include "../videoimage/image46.h"
#include "../videoimage/image47.h"
#include "../videoimage/image48.h"
#include "../videoimage/image49.h"
#include "../videoimage/image50.h"


#include "../image/earth.h"
#include "../image/mars.h"
#include "../image/uranus.h"

#include "../image/bigmoon.h"

#define MAX_CMD_SIZE 100

const long unsigned int *epd_bitmap[] = {epd_bitmap_0001, epd_bitmap_0002, epd_bitmap_0003, epd_bitmap_0004, epd_bitmap_0005, epd_bitmap_0006,
                                         epd_bitmap_0007, epd_bitmap_0008, epd_bitmap_0009, epd_bitmap_0010, epd_bitmap_0011, epd_bitmap_0012,
                                         epd_bitmap_0013, epd_bitmap_0014, epd_bitmap_0015, epd_bitmap_0016, epd_bitmap_0017, epd_bitmap_0018,
                                         epd_bitmap_0019, epd_bitmap_0020, epd_bitmap_0021, epd_bitmap_0022, epd_bitmap_0023, epd_bitmap_0024,
                                         epd_bitmap_0025, epd_bitmap_0026, epd_bitmap_0027, epd_bitmap_0028, epd_bitmap_0029, epd_bitmap_0030,
                                         epd_bitmap_0031, epd_bitmap_0032, epd_bitmap_0033, epd_bitmap_0034, epd_bitmap_0035, epd_bitmap_0036,
                                         epd_bitmap_0037, epd_bitmap_0038, epd_bitmap_0039, epd_bitmap_0040, epd_bitmap_0041, epd_bitmap_0042,
                                         epd_bitmap_0043, epd_bitmap_0044, epd_bitmap_0045, epd_bitmap_0046, epd_bitmap_0047, epd_bitmap_0047,
                                         epd_bitmap_0048, epd_bitmap_0049, epd_bitmap_0050};

const long unsigned int *epd_bitmap_slideshow[] = {epd_bitmap_earth, epd_bitmap_mars, epd_bitmap_uranus};

/* Function to wait for some msec: the program will stop there */
void wait_msec(unsigned int n)
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

void view()
{
    int i1 = 0;
    int i2 = 0;
    uart_puts("\nPlease look at the virtual machine and open the terminal side by side for control\n");
    uart_puts("Press 'w' to move the image UP\n");
    uart_puts("Press 's' to move the image DOWN\n");
    uart_puts("Press 'd' to move the image RIGHT\n");
    uart_puts("Press 'a' to move the image LEFT\n");
    uart_puts("Press ENTER to exit slideshow\n\n");
    framebf_init(i1, i2);

    while (1)
    {

        draw_background(epd_bitmap_moon1500, 1500, 1500);

        char ch = uart_getc();
        uart_sendc(ch);
        // framebf_init(0, i2);

        if (ch == 'w')
        {
            i2 -= 500;
            if (i2 < 0)
            {
                i2 = 0;
                uart_puts("\rView Limit Reached !!\n");
            }
            else
            {

                uart_puts("\rup\n");
                uart_puts("\nPress ENTER to exit view\n\n");
            }

            framebf_init(i1, i2);
        }
        else if (ch == 's')
        {
            i2 += 500;
            if (i2 > 1200)
            {
                i2 = 1200;
                uart_puts("\rView Limit Reached !!\n");
            }

            else
            {
                uart_puts("\rdown\n");
                uart_puts("\nPress ENTER to exit view\n\n");
            }

            framebf_init(i1, i2);
        }

        else if (ch == 'a')
        {
            i1 -= 500;
            if (i1 < 0)
            {
                i1 = 0;
                uart_puts("\rView Limit Reached !!\n");
            }
            else
            {
                uart_puts("\rleft\n");
                uart_puts("\nPress ENTER to exit view\n\n");
            }

            framebf_init(i1, i2);
        }

        else if (ch == 'd')
        {
            i1 += 500;
            if (i1 > 1900)
            {
                i1 = 1900;
                uart_puts("\rView Limit Reached !!\n");
            }
            else
            {
                uart_puts("\rright\n");
                uart_puts("\nPress ENTER to exit view\n\n");
            }

            framebf_init(i1, i2);
        }

        else if (ch == '\n')
        {
            drawRectARGB32(0, 0, 2000, 2000, 0x00070200, 1); // CLEAR SCREEN
            uart_puts("\nView exited\n");

            break;
        }
    }
}

void slideshow()
{

    framebf_init(0, 0);

    static int i = 0;

    draw_background(epd_bitmap_slideshow[i], 1280, 720);
    uart_puts("Please look at the virtual machine\n");
    uart_puts("Press 'd' to view next image\n");
    uart_puts("Press 'a' to view previous image\n");
    uart_puts("Press ENTER to exit slideshow\n\n");

    while (1)
    {
        char ch = uart_getc();
        uart_sendc(ch);
        if (ch == 'd')
        {

            i++;
            if (i > 2)
            {
                i = 0;
            }
            uart_puts("\rnext\n");
            uart_puts("\nPress ENTER to exit slideshow\n\n");

            draw_background(epd_bitmap_slideshow[i], 1280, 720);
        }
        else if (ch == 'a')
        {

            i--;
            if (i < 0)
            {
                i = 2;
            }
            uart_puts("\rprevious\n");
            uart_puts("\nPress ENTER to exit slideshow\n\n");

            draw_background(epd_bitmap_slideshow[i], 1280, 720);
        }
        else if (ch == '\n')
        {
            drawRectARGB32(0, 0, 2000, 2000, 0x00070200, 1); // CLEAR SCREEN
            i = 0;
            uart_puts("\nSlideshow exited\n");

            break;
        }
    }
}

void video()
{
    framebf_init(0, 0);
    uart_puts("Please look at the virtual machine\n");
    uart_puts("Press r key to replay video\n");
    uart_puts("Press ENTER to exit video\n");
    int i;
    for (i = 0; i < 50; i++)
    {
        draw_background(epd_bitmap[i], 1280, 720);
        wait_msec(30000);
    }
    while (1)
    {
        char ch = uart_getc();
        uart_sendc(ch);
        if (ch == 'r')
        {

            for (i = 0; i < 50; i++)
            {

                draw_background(epd_bitmap[i], 1280, 720);
                wait_msec(30000);
                uart_puts(" \r\r"); // delete 'r' character when press
            }
        }

        else if (ch == '\n')
        {
            drawRectARGB32(0, 0, 2000, 2000, 0x00070200, 1); // CLEAR SCREEN
            i = 0;
            uart_puts("\nVideo exited\n");

            break;
        }
    }
}

void names()
{
    framebf_init(0, 0);

    uart_puts("\nPlease look at the virtual machine and open the terminal side by side for control\n");

    // drawRectARGB32(0, 0, 2000, 2000, 0x00FFFFFF, 1); // white background
    drawString(250, 300, "Bui Dang Dac Duong - S3764487", 0x0a, 2);
    drawString(300, 350, "Nguyen Minh Quang - S3878631", 0x0b, 2);
    drawString(350, 400, "Nguyen Hoang Phuong - S3924593", 0x0c, 2);
    drawString(400, 450, "Tran Xuan Hoang Dat - S3651550", 0x0d, 2);

    drawString(250, 500, "Press ENTER to exit the name display", 0x0e, 2);

    while (1)
    {
        char ch = uart_getc();
        uart_sendc(ch);

        if (ch == '\n')
        {
            drawRectARGB32(0, 0, 2000, 2000, 0x00070200, 1); // CLEAR SCREEN
            uart_puts("\nNames display exited\n");

            break;
        }
    }
}