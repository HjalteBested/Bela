/*
MIT License

Copyright (c) 2020 Jeremiah Rose

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <stddef.h>

class SPI {
#include <linux/spi/spidev.h>
public:
	/* Generic Definitions */
	static const int SS_HIGH = 1;
	static const int SS_LOW = 0;

	/* Enum SPI Modes*/
	typedef enum{
		MODE0 = SPI_MODE_0,
		MODE1 = SPI_MODE_1,
		MODE2 = SPI_MODE_2,
		MODE3 = SPI_MODE_3
	} Mode;

	SPI();
	~SPI();
	/**
	* Initialize the device
	*
	* @param device path to the device file (e.g.: `/dev/spidev2.1`)
	* @param speed clock rate in Hz
	* @param delay delay after the last bit transfer before deselecting the device
	* @param speed SPI clock rate in Hz
	* @param numBits No. of bits per transaction
	* @param mode SPI mode for RD and WR operations
	* @return 0 on success, an error code otherwise.
	*/
	int setup(const char* device = "/dev/spidev2.1",
		unsigned long speed = 500000,
		unsigned short delay = 0,
		unsigned char numBits = 8,
		unsigned int mode = MODE3); // this is not a Mode because the user can specify a custom mode by OR'ing flags together
	/**
	* Perform one SPI transaction.
	*
	* @send: Points to the buffer containing the data to be sent
	* @receive: Points to the buffer into which the received
	* bytes will be stored
	* @numBytes: length of buffers in bytes.
	*
	* @return 0 on success, -1 on failure
	*/
	int transfer(unsigned char *send, unsigned char *receive,
		 size_t numBytes);
	/**
	* Close the device.
	*/
	void cleanup();
private:
	const char* device;
	unsigned long speed;
	unsigned short delay;
	unsigned char numBits;
	unsigned char mode;
	int fd;
	struct spi_ioc_transfer transaction;
	int openDevice(const char* device);
	int setMode(unsigned char mode);
	int setNumBits(unsigned char numBits);
	int setSpeed(unsigned long speed);
};
