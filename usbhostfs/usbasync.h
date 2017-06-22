/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * usbasync.h - PSPLINK USB Asynchronous Data Provider
 *
 * Copyright (c) 2006 James F
 *
 * $HeadURL: svn://svn.ps2dev.org/psp/trunk/psplinkusb/usbhostfs/usbasync.h $
 * $Id: usbasync.h 2177 2007-02-15 17:28:02Z tyranid $
 */
#ifndef __USBASYNC_H__
#define __USBASYNC_H__

#include <stdint.h>

#define MAX_ASYNC_BUFFER   4096

#define ASYNC_USER 4

struct AsyncEndpoint
{
	unsigned char buffer[MAX_ASYNC_BUFFER];
	int read_pos;
	int write_pos;
	int size;
};

#define MAX_ASYNC_CHANNELS 8
#define ASYNC_ALLOC_CHAN ((unsigned int) (-1))

/**
  * Wait for the USB connection to be established
  *
  * @return 0 on connected, < 0 on error
  */
int     usbWaitForConnect(void);

/**
  * Register an asyncronous provider
  * @param chan - The channel number to register (0->3 are reserved for psplink use)
  * If you dont care about what channel number to provide then pass ASYNC_ALLOC_CHAN
  * @param endp - Pointer to an AsyncEndpoint structure
  * 
  * @return channel number on success, < 0 on error
  */
int     usbAsyncRegister(unsigned int chan, struct AsyncEndpoint *endp);

/**
  * Unregister an asyncronous provider
  * 
  * @param chan - The channel to unregister
  *
  * @return 0 on success, < 0 on error
  */
int     usbAsyncUnregister(unsigned int chan);

/**
  * Write data to the specified async channel
  * 
  * @param chan - The channel to write to
  * @param data - The data set to write
  * @param len - The length of the data
  * 
  * @return The number of bytes written, < 0 on error
  */
int     usbAsyncWrite(unsigned int chan, const void *data, int len);

/**
  * Read data from the specified async channel
  * 
  * @param chan - The channel to read from
  * @param data - The data block to read into
  * @param len -  The length of the data to read
  * 
  * @return The number of bytes read, < 0 on error
  */
int     usbAsyncRead(unsigned int chan, unsigned char *data, int len);

/**
  * Read data from the specified async channel with a timeout
  * 
  * @param chan - The channel to read from
  * @param data - The data block to read into
  * @param len -  The length of the data to read
  * @param timeout - The timeout, if < 0 then dont timeout, otherwise number
  * of microseconds
  * 
  * @return The number of bytes read, < 0 on error
  */
int     usbAsyncReadWithTimeout(unsigned int chan, unsigned char *data, int len, int timeout);

/**
  * Flush the read buffer of an async channel
  * 
  * @param chan - The channel to flush
  */
void    usbAsyncFlush(unsigned int chan);

/**
 * Write a large transfer to an async channel
 *
 * @param chan - The channel to write to
 * @param data - Pointer to the data to write (should be 16byte aligned)
 * @param size - Size of data set to write
 *
 * @return the number of bytes written, < 0 on error
 */
int usbWriteBulkData(int chan, const void *data, int len);

/**
 * Lock the USB bus (normally to ensure no threads are using it)
 *
 * @return < 0 on error
 */
int 	usbLockBus(void);

/**
 * Unlock the USB bus 
 *
 * @return < 0 on error
 */
int 	usbUnlockBus(void);

#endif
