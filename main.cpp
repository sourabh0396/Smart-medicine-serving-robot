#include <reg52.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "delay.h"
unsigned int aa;
sbit mot11 = P2 ^ 0;
sbit mot12 = P2 ^ 1;
sbit mot21 = P2 ^ 2;
sbit mot22 = P2 ^ 3;
sbit mot31 = P2 ^ 4;
sbit mot32 = P2 ^ 5;
sbit buzz = P2 ^ 6;

sbit r1 = P3 ^ 0;
sbit r2 = P3 ^ 1;
sbit r3 = P3 ^ 2;
sbit r4 = P3 ^ 3;
sbit c1 = P3 ^ 4;
sbit c2 = P3 ^ 5;
sbit c3 = P3 ^ 6;

sbit button = P3 ^ 7;
sbit show = P2 ^ 7;
sbit empty = P0 ^ 7;
sbit reset = P0 ^ 6;
int var;
unsigned int f = 0;

int arr[6] = {0};
unsigned int count = 0;

int pill1 = 1, pill2 = 1, pill3 = 1;

// void del(unsigned int i)
//{
//     unsigned int j;
//     for (j = 0; j < i; j++)
//         ;
// }

void Timerdelay()
{
    TMOD = 0x01; // Timer0 mode1
    TH0 = 0xFC;  // initial value for 1ms
    TL0 = 0x66;
    TR0 = 1; // timer start
    while (TF0 == 0)
        ;    // check overflow condition
    TR0 = 0; // Stop Timer
    TF0 = 0; // Clear flag
}

// void md()
//{
//     unsigned int z, x;

//    for (z = 0; z < 62; z++)
//    {
//        for (x = 0; x < 1257; x++)
//            ;
//    }
//}

void delay(unsigned int t)
{

    unsigned int i, j;

    for (j = 0; j <= t; j++)
    {
        for (i = 0; i < 1257; i++)
            ;
    }
}

unsigned char sec, min, hour, day, month, year, h, m, s;
unsigned char char1, char2, char3;
unsigned int a1, a2, b1, b2, c11, c22, d1, d2, d3;

unsigned int total[3] = {0};

/* main program */
void main()
{
    buzz = 0;
    button = 1;
    show = 1;
    empty = 0;
    reset = 1;

    /* Initilize the lcd */
    lcd_Init();
    delay_us(20);
    /* Initilize the RTC(ds1307)*/
    ds1307_Init();
    delay_us(20);
    /*set the time and DATE only once */
    ds1307_SetTime(0x17, 0x59, 0x30); //
    ds1307_SetDate(0x11, 0x01, 0x23); //
    delay_us(20);
    /* Display "time" on first line*/
    lcd_DisplayString("TIME: ");

    /* Display "date" on Second line*/
    lcd_GoToLineTwo();
    delay_us(20);
    lcd_DisplayString("DATE: ");

    /* Display the time and date continously */
    while (1)
    {

        /* Display "time" on first line*/

        /* Read the TIME from RTC(ds1307) */
        ds1307_GetTime(&hour, &min, &sec);
        h = hour;
        s = sec;
        m = min;
        lcd_GoToXY(0, 6);
        lcd_DisplayRtcTime(hour, min, sec);
        /* Display the time on firstline 7th position*/
        delay_us(20);
        lcd_GoToXY(0, 6);
        lcd_DisplayRtcTime(hour, min, sec);
        delay_us(20);
        if ((h == char1) && (m == 0x00) && (sec == 0x00))
        {
            lcd_Init();
            delay_us(20);
            lcd_DisplayString("!TAKE MEDICINE!");
            delay_us(40);
					
            buzz = 1;
                for (var = 0; var < 5000; var++)
                {
                    Timerdelay();
                }
                // delay(103);
                buzz = 0;
								
            delay_us(20);
            lcd_Init();

            delay_us(20);
            lcd_DisplayString("TIME: ");
            lcd_GoToLineTwo();
            delay_us(20);
            lcd_DisplayString("DATE: ");
            delay_us(20);
            //            mot11 = 1;
            //            mot12 = 0;
            //            md();
            //            mot11 = 0;
            //            mot12 = 0;

            mot11 = 1;
            mot12 = 0;

            for (var = 0; var < 400; var++)
            {
                Timerdelay();
            }
            mot11 = 0;
            mot12 = 0;

            pill1--;
        }

        else if ((h == char2) && (m == 0x01) && (sec == 0x00))
        {
            lcd_Init();
            delay_us(20);
            lcd_DisplayString("!TAKE MEDICINE!");
            delay_us(40);
					
                buzz = 1;
                for (var = 0; var < 5000; var++)
                {
                    Timerdelay();
                }
                // delay(103);
                buzz = 0;
                
                // delay(103)
            
            delay_us(20);
            lcd_Init();
            delay_us(20);
            lcd_DisplayString("TIME: ");
            lcd_GoToLineTwo();
            delay_us(20);
            lcd_DisplayString("DATE: ");
            delay_us(20);

            //            mot21 = 1;
            //            mot22 = 0;
            //            md();
            //            mot21 = 0;
            //            mot22 = 0;

            mot21 = 1;
            mot22 = 0;

            for (var = 0; var < 400; var++)
            {
                Timerdelay();
            }
            mot21 = 0;
            mot22 = 0;
            pill2--;
        }

        else if ((h == char3) && (m == 0x02) && (sec == 0x00))
        {
            lcd_Init();
            delay_us(40);
            lcd_DisplayString("!TAKE MEDICINE!");
            delay_us(40);
					
            buzz = 1;
                for (var = 0; var < 5000; var++)
                {
                    Timerdelay();
                }
                // delay(103);
                buzz = 0;
								
            delay_us(20);
            lcd_Init();
            delay_us(40);
            lcd_DisplayString("TIME: ");
            lcd_GoToLineTwo();
            delay_us(40);
            lcd_DisplayString("DATE: ");
            delay_us(20);

            mot31 = 1;
            mot32 = 0;

            for (var = 0; var < 400; var++)
            {
                Timerdelay();
            }
            mot31 = 0;
            mot32 = 0;
            pill3--;
        }

        /* Read the DATE from RTC(ds1307) */
        ds1307_GetDate(&day, &month, &year);

        /* Display the DATE on secondline 7th position*/
        lcd_GoToXY(1, 6);
        lcd_DisplayRtcDate(day, month, year);

        if (show == 0)
        {

            lcd_Init();
            delay_us(50);
            lcd_WriteCmd(0x01);
            delay_us(50);
            lcd_WriteCmd(0x80);
            delay_us(50);
            lcd_DisplayString("PILLS LEFT:");
            delay_us(50);
            lcd_WriteCmd(0xc0);
            delay_us(50);
            lcd_DisplayString("P1:");
            delay_us(50);
            lcd_WriteCmd(0xc3);
            delay_us(50);
            lcd_Writedata((pill1 + 0x30));
					
					  
					 delay_us(50);
            lcd_WriteCmd(0xc5);
            delay_us(50);
            lcd_DisplayString("P2:");
            delay_us(50);
            lcd_WriteCmd(0xc8);
            delay_us(50);
            lcd_Writedata((pill2 + 0x30));					
					
						delay_us(50);
            lcd_WriteCmd(0xca);
            delay_us(50);
            lcd_DisplayString("P3:");
            delay_us(50);
            lcd_WriteCmd(0xcd);
            delay_us(50);
            lcd_Writedata((pill3 + 0x30));					
					
						
					
            for (var = 0; var < 5000; var++)
            {
                Timerdelay();
            }

            lcd_Init();
            delay_us(20);
            lcd_DisplayString("TIME: ");
            delay_us(20);
            /* Display "date" on Second line*/
            lcd_GoToLineTwo();
            delay_us(20);
            lcd_DisplayString("DATE: ");
            delay_us(20);
        }

        if (pill1 <= 0 && pill2 <= 0 && pill3 <= 0)
        {
            empty = 1;
        }

        if (reset == 0)
        {

            pill1 = 1;
						pill2 = 1;
						pill3 = 1;
            empty = 0;
        }

        if (button == 0)
        {
            f = 0;
            count = 0;
            lcd_Init();
            delay_us(50);
            lcd_WriteCmd(0x01);
            delay_us(50);
            lcd_WriteCmd(0x80);
            delay_us(50);
            lcd_DisplayString("SetTime:HH:HH:HH");
            delay_us(50);
            lcd_WriteCmd(0xc0);
            delay_us(50);
            f = 0;
            delay_us(50);
            while (f < 6)
            {
                delay(30);

                c1 = c2 = c3 = 1;
                r1 = r2 = r3 = r4 = 0;

                if (c1 == 0) // c1 is pressed
                {
                    // f++;
                    delay_us(20);
                    r1 = r2 = r3 = r4 = 1;
                    c1 = c2 = c3 = 0;
                    if (r1 == 0) // r1 is pressed
                    {
                        while (r1 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('1');
                        delay_us(20);
                        arr[count] = 1;
                        count++;
                        f++;
                    }
                    if (r2 == 0) // r2 is pressed
                    {
                        while (r2 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('4');
                        delay_us(20);
                        arr[count] = 4;
                        count++;
                        f++;
                    }
                    if (r3 == 0) // r1 is pressed
                    {
                        while (r3 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('7');
                        delay_us(20);
                        arr[count] = 7;
                        count++;
                        f++;
                    }

                    if (r4 == 0) // r1 is pressed
                    {
                        while (r4 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('*');
                        delay_us(20);
                        arr[count] = 25;
                        count++;
                        f++;
                    }
                }
                else if (c2 == 0) // c1 is pressed
                {
                    // f++;

                    r1 = r2 = r3 = r4 = 1;
                    c1 = c2 = c3 = 0;
                    if (r1 == 0) // r1 is pressed
                    {
                        while (r1 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('2');
                        delay_us(20);
                        arr[count] = 2;
                        count++;
                        f++;
                    }
                    if (r2 == 0) // r2 is pressed
                    {
                        while (r2 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('5');
                        delay_us(20);
                        arr[count] = 5;
                        count++;
                        f++;
                    }
                    if (r3 == 0) // r1 is pressed
                    {
                        while (r3 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('8');
                        delay_us(20);
                        arr[count] = 8;
                        count++;
                        f++;
                    }
                    if (r4 == 0) // r2 is pressed
                    {
                        while (r4 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('0');
                        delay_us(20);
                        arr[count] = 0;
                        count++;
                        f++;
                    }
                }

                else if (c3 == 0) // c1 is pressed
                {
                    // f++;
                    r1 = r2 = r3 = r4 = 1;
                    c1 = c2 = c3 = 0;
                    if (r1 == 0) // r1 is pressed
                    {
                        while (r1 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('3');
                        delay_us(20);
                        arr[count] = 3;
                        count++;
                        f++;
                    }
                    if (r2 == 0) // r2 is pressed
                    {
                        while (r2 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('6');
                        delay_us(20);
                        arr[count] = 6;
                        count++;
                        f++;
                    }
                    if (r3 == 0) // r1 is pressed
                    {
                        while (r3 == 0)
                            ;
                        delay_us(20);
                        lcd_Writedata('9');
                        delay_us(20);
                        arr[count] = 9;
                        count++;
                        f++;
                    }
                }
            }
            f = 0;
            count = 0;
            a1 = arr[0];

            a1 = a1 * 10;
            a2 = arr[1];

            a2 = a1 + a2;
            delay_us(20);
            b1 = arr[2];

            b1 = b1 * 10;
            b2 = arr[3];

            b2 = b1 + b2;
            delay_us(20);
            c11 = arr[4];

            c11 = c11 * 10;
            c22 = arr[5];

            c22 = c11 + c22;
            delay_us(20);

            switch (a2)
            {
            case 0:
                char1 = 0x00;
                break;
            case 1:
                char1 = 0x01;
                break;
            case 2:
                char1 = 0x02;
                break;
            case 3:
                char1 = 0x03;
                break;
            case 4:
                char1 = 0x04;
                break;
            case 5:
                char1 = 0x05;
                break;
            case 6:
                char1 = 0x06;
                break;
            case 7:
                char1 = 0x07;
                break;
            case 8:
                char1 = 0x08;
                break;
            case 9:
                char1 = 0x09;
                break;

            case 10:
                char1 = 0x10;
                break;
            case 11:
                char1 = 0x11;
                break;
            case 12:
                char1 = 0x12;
                break;
            case 13:
                char1 = 0x13;
                break;
            case 14:
                char1 = 0x14;
                break;
            case 15:
                char1 = 0x15;
                break;
            case 16:
                char1 = 0x16;
                break;
            case 17:
                char1 = 0x17;
                break;
            case 18:
                char1 = 0x18;
                break;
            case 19:
                char1 = 0x19;
                break;
            case 20:
                char1 = 0x20;
                break;
            case 21:
                char1 = 0x21;
                break;
            case 22:
                char1 = 0x22;
                break;
            case 23:
                char1 = 0x23;
                break;
            case 275:
                char1 = 0x25;
                break;
            default:
                char1 = 0x200;
            };

            switch (b2)
            {
            case 0:
                char2 = 0x00;
                break;
            case 1:
                char2 = 0x01;
                break;
            case 2:
                char2 = 0x02;
                break;
            case 3:
                char2 = 0x03;
                break;
            case 4:
                char2 = 0x04;
                break;
            case 5:
                char2 = 0x05;
                break;
            case 6:
                char2 = 0x06;
                break;
            case 7:
                char2 = 0x07;
                break;
            case 8:
                char2 = 0x08;
                break;
            case 9:
                char2 = 0x09;
                break;

            case 10:
                char2 = 0x10;
                break;
            case 11:
                char2 = 0x11;
                break;
            case 12:
                char2 = 0x12;
                break;
            case 13:
                char2 = 0x13;
                break;
            case 14:
                char2 = 0x14;
                break;
            case 15:
                char2 = 0x15;
                break;
            case 16:
                char2 = 0x16;
                break;
            case 17:
                char1 = 0x17;
                break;
            case 18:
                char2 = 0x18;
                break;
            case 19:
                char2 = 0x19;
                break;
            case 20:
                char2 = 0x20;
                break;
            case 21:
                char2 = 0x21;
                break;
            case 22:
                char2 = 0x22;
                break;
            case 23:
                char2 = 0x23;
                break;
            case 275:
                char2 = 0x25;
                break;
            default:
                char2 = 0x200;
            };

            switch (c22)
            {
            case 0:
                char3 = 0x00;
                break;
            case 1:
                char3 = 0x01;
                break;
            case 2:
                char3 = 0x02;
                break;
            case 3:
                char3 = 0x03;
                break;
            case 4:
                char3 = 0x04;
                break;
            case 5:
                char3 = 0x05;
                break;
            case 6:
                char3 = 0x06;
                break;
            case 7:
                char3 = 0x07;
                break;
            case 8:
                char3 = 0x08;
                break;
            case 9:
                char3 = 0x09;
                break;

            case 10:
                char3 = 0x10;
                break;
            case 11:
                char3 = 0x11;
                break;
            case 12:
                char3 = 0x12;
                break;
            case 13:
                char3 = 0x13;
                break;
            case 14:
                char3 = 0x14;
                break;
            case 15:
                char3 = 0x15;
                break;
            case 16:
                char3 = 0x16;
                break;
            case 17:
                char3 = 0x17;
                break;
            case 18:
                char3 = 0x18;
                break;
            case 19:
                char3 = 0x19;
                break;
            case 20:
                char3 = 0x20;
                break;
            case 21:
                char3 = 0x21;
                break;
            case 22:
                char3 = 0x22;
                break;
            case 23:
                char3 = 0x23;
                break;
            case 275:
                char3 = 0x25;
                break;
            default:
                char3 = 0x200;
            };

            f = 0;
            count = 0;
            lcd_Init();
            delay_us(20);
            lcd_DisplayString("TIME: ");
            delay_us(20);
            /* Display "date" on Second line*/
            lcd_GoToLineTwo();
            delay_us(20);
            lcd_DisplayString("DATE: ");
            delay_us(20);
        }
    }
} 
