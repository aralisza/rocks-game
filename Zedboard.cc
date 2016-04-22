#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include "Level.h"

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;
// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;
const int gpio_led1_offset = 0x12C; // Offset for LED1
const int gpio_led2_offset = 0x130; // Offset for LED2
const int gpio_led3_offset = 0x134; // Offset for LED3
const int gpio_led4_offset = 0x138; // Offset for LED4
const int gpio_led5_offset = 0x13C; // Offset for LED5
const int gpio_led6_offset = 0x140; // Offset for LED6
const int gpio_led7_offset = 0x144; // Offset for LED7
const int gpio_led8_offset = 0x148; // Offset for LED8
const int gpio_sw1_offset = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset = 0x150; // Offset for Switch 2
const int gpio_sw3_offset = 0x154; // Offset for Switch 3
const int gpio_sw4_offset = 0x158; // Offset for Switch 4
const int gpio_sw5_offset = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset = 0x160; // Offset for Switch 6
const int gpio_sw7_offset = 0x164; // Offset for Switch 7
const int gpio_sw8_offset = 0x168; // Offset for Switch 8
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button

class ZedBoard
{
	char *ptr;
	int fd;
  	Game* g;

public:

	ZedBoard()
	{
		fd = open( "/dev/mem", O_RDWR);
		g = new Game;

		ptr = (char *) mmap(
			NULL,
			gpio_size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fd,
			gpio_address);

		// Check error
		if (ptr == MAP_FAILED)
		{
			perror("Mapping I/O memory failed - Did you run with 'sudo'?\n");
		}
	}

	~ZedBoard()
	{
	   munmap(ptr, gpio_size);
	   close(fd);
	}

	void RegisterWrite(int offset, int value)
	{
		* (int *) (ptr + offset) = value;
	}

	int RegisterRead(int offset)
	{
		return * (int *) (ptr + offset);
	}

	/**
	 * Show lower 8 bits of integer value on LEDs
	 *
	 * @param ptr Base address of I/O
	 * @param value Value to show on LEDs
	 */
	void SetLedNumber(int value)
	{
		RegisterWrite(gpio_led1_offset, reduceTo1(value + 1) );
		RegisterWrite(gpio_led2_offset, reduceTo1((value + 1)/2));
		RegisterWrite(gpio_led3_offset, reduceTo1((value + 1)/3));
		RegisterWrite(gpio_led4_offset, reduceTo1((value + 1)/4));
		RegisterWrite(gpio_led5_offset, 0);
		RegisterWrite(gpio_led6_offset, 0);
		RegisterWrite(gpio_led7_offset, 0);
		RegisterWrite(gpio_led8_offset, 0);
	}

    int PushButtonGet()
    {
        if ((RegisterRead(gpio_pbtnl_offset) == 1))
        {
            g->onKey('a');
            usleep(200000);
            return 1;
        }
        else if ((RegisterRead(gpio_pbtnr_offset) == 1))
        {
            g->onKey('d');
            usleep(200000);
            return 2;
        }
        else if ((RegisterRead(gpio_pbtnu_offset) == 1))
        {
            g->onKey('w');
            usleep(200000);
            return 3;
        }
        else if ((RegisterRead(gpio_pbtnd_offset) == 1))
        {
            g->onKey('s');
            usleep(200000);
            return 4;
        }
        else if ((RegisterRead(gpio_pbtnc_offset) == 1))
        {
            g->onKey('r');
            usleep(200000);
            return 5;
        }
        else
        {
            return 0;
        }
    }

int ReadSwitches() {
	int i = -1;
	if (RegisterRead(gpio_sw4_offset) == 1)
		i = 3;

	else if (RegisterRead(gpio_sw3_offset) == 1)
		i = 2;

	else if (RegisterRead(gpio_sw2_offset) == 1)
		i = 1;
	else if (RegisterRead(gpio_sw1_offset) == 1)
		i = 0;

	return i;
}

	void levelControl() {
		int i = ReadSwitches();

		if (i != g->curLev && i >= 0 && i < g->levels.size()) {
			g->curLev = i;
			g->print();
		}
		SetLedNumber(i);
	}

	int reduceTo1(int val) {
		if (val > 0) {
			return 1;
		}
		else return 0;
	}

	bool end() {
		return g->winAll();
	}

};

int main() {
    ZedBoard* zedboard = new ZedBoard;

    printf("======================================================\n\n        ######\n        #     #   ####    ####   #    #   ####\n        #     #  #    #  #    #  #   #   #\n        ######   #    #  #       ####     ####\n        #   #    #    #  #       #  #         #\n        #    #   #    #  #    #  #   #   #    #\n        #     #   ####    ####   #    #   ####\n\n======================================================\n\n~~~~~~~~~~~~~~~~~~~  How to Play  ~~~~~~~~~~~~~~~~~~~~\n\nYou are represented with the letter 'p'\n\nPush the rocks so that you clear a path to the exit.\nRocks are represented with the letter 'O'\n\nYou can only move rocks if there is a free space to\npush them to.\n\nExits are marked with the letter 'e'\n\nWalls are represented with the letter 'X'.\nWalls are immovable.\n\nYou beat the level when you move your player to the\nexit.\n\nControls:\nUp Button - up\nLeft Button - left\nDown Button - down\nRight Button - right\nCenter Button - reset\nUse the switches to change the current level.\n\nPress the center button to begin! Have fun!\n\n");

    while(!zedboard->end()) {
        zedboard->PushButtonGet();
        zedboard->levelControl();
    }
    printf("You Win!\n");
}
