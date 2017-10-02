/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * usbhostfs.h - PSPLINK USB HostFS command header
 *
 * Copyright (c) 2006 James F
 *
 * $HeadURL: svn://svn.ps2dev.org/psp/trunk/psplinkusb/usbhostfs/usbhostfs.h $
 * $Id: usbhostfs.h 2263 2007-06-28 20:00:22Z tyranid $
 */
#ifndef __USBHOSTFS_H__
#define __USBHOSTFS_H__

#define MODULE_NAME "USBHostFS"
#define HOSTFSDRIVER_NAME "USBHostFSDriver"
#define HOSTFSDRIVER_PID  (0x1C9)
#define SONY_VID (0x54C)

#define HOSTFS_MAGIC 0x782F0812
#define ASYNC_MAGIC  0x782F0813
#define BULK_MAGIC   0x782F0814

#define HOSTFS_PATHMAX (4096)

#define HOSTFS_MAX_BLOCK (32*1024)

#define HOSTFS_RENAME_BUFSIZE (1024)

#define HOSTFS_BULK_MAXWRITE  (1024*1024)

#define DEVCTL_GET_INFO       0x3001

/*
struct DevctlGetInfo {
    // Total number of blocks
    unsigned int btotal;
    // Total number of free blocks
    unsigned int bfree;
    // Unknown
    unsigned int unk;
    // Sector size
    unsigned int ssize;
    // Number of sectors per block
    unsigned int sects;
};

typedef struct {
    uint64_t max_size;
    uint64_t free_size;
    uint32_t cluster_size;
    void *unk;
} SceIoDevInfo;
*/

enum USB_ASYNC_CHANNELS {
    ASYNC_SHELL = 0,
    ASYNC_GDB = 1,
    ASYNC_STDOUT = 2,
    ASYNC_STDERR = 3,
};

#define MAX_ASYNC_CHANNELS 8

enum HostFsCommands {
    HOSTFS_CMD_HELLO = 0x8FFC0000,
    HOSTFS_CMD_BYE = 0x8FFC0001,
    HOSTFS_CMD_OPEN = 0x8FFC0002,
    HOSTFS_CMD_CLOSE = 0x8FFC0003,
    HOSTFS_CMD_READ = 0x8FFC0004,
    HOSTFS_CMD_WRITE = 0x8FFC0005,
    HOSTFS_CMD_LSEEK = 0x8FFC0006,
    HOSTFS_CMD_REMOVE = 0x8FFC0007,
    HOSTFS_CMD_MKDIR = 0x8FFC0008,
    HOSTFS_CMD_RMDIR = 0x8FFC0009,
    HOSTFS_CMD_DOPEN = 0x8FFC000A,
    HOSTFS_CMD_DREAD = 0x8FFC000B,
    HOSTFS_CMD_DCLOSE = 0x8FFC000C,
    HOSTFS_CMD_GETSTAT = 0x8FFC000D,
    HOSTFS_CMD_GETSTATBYFD = 0x8FFC000E,
    HOSTFS_CMD_CHSTAT = 0x8FFC000F,
    HOSTFS_CMD_RENAME = 0x8FFC0010,
    HOSTFS_CMD_CHDIR = 0x8FFC0011,
    HOSTFS_CMD_IOCTL = 0x8FFC0012,
    HOSTFS_CMD_DEVCTL = 0x8FFC0013
};

struct HostFsTimeStamp {
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
} __attribute__((packed));

struct HostFsCmd {
    uint32_t magic;
    uint32_t command;
    uint32_t extralen;
} __attribute__((packed));

struct HostFsHelloCmd {
    struct HostFsCmd cmd;
} __attribute__((packed));

struct HostFsHelloResp {
    struct HostFsCmd cmd;
} __attribute__((packed));

struct HostFsByeCmd {
    struct HostFsCmd cmd;
} __attribute__((packed));

struct HostFsByeResp {
    struct HostFsCmd cmd;
} __attribute__((packed));

struct HostFsOpenCmd {
    struct HostFsCmd cmd;
    uint32_t mode;
    uint32_t mask;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsOpenResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsCloseCmd {
    struct HostFsCmd cmd;
    int32_t fid;
} __attribute__((packed));

struct HostFsCloseResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsReadCmd {
    struct HostFsCmd cmd;
    int32_t fid;
    int32_t len;
} __attribute__((packed));

struct HostFsReadResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsWriteCmd {
    struct HostFsCmd cmd;
    int32_t fid;
} __attribute__((packed));

struct HostFsWriteResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsLseekCmd {
    struct HostFsCmd cmd;
    int32_t fid;
    int64_t ofs;
    int32_t whence;
} __attribute__((packed));

struct HostFsLseekResp {
    struct HostFsCmd cmd;
    int32_t res;
    int64_t ofs;
} __attribute__((packed));

struct HostFsIoctlCmd {
    struct HostFsCmd cmd;
    int32_t fid;
    uint32_t cmdno;
    int32_t outlen;
} __attribute__((packed));

struct HostFsIoctlResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsDevctlCmd {
    struct HostFsCmd cmd;
    uint32_t cmdno;
    uint32_t fsnum;
    int32_t outlen;
} __attribute__((packed));

struct HostFsDevctlResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsRemoveCmd {
    struct HostFsCmd cmd;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsRemoveResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsDopenCmd {
    struct HostFsCmd cmd;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsDopenResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsDreadCmd {
    struct HostFsCmd cmd;
    int32_t did;
} __attribute__((packed));

struct HostFsDreadResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsDcloseCmd {
    struct HostFsCmd cmd;
    int32_t did;
} __attribute__((packed));

struct HostFsDcloseResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsMkdirCmd {
    struct HostFsCmd cmd;
    unsigned int mode;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsMkdirResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsRmdirCmd {
    struct HostFsCmd cmd;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsRmdirResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsGetstatCmd {
    struct HostFsCmd cmd;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsGetstatResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsGetstatByFdCmd {
    struct HostFsCmd cmd;
    int32_t fid;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsGetstatByFdResp {
    struct HostFsCmd cmd;
    SceMode mode;
    unsigned int attr;
    SceOff size;
    SceDateTime ctime;
    SceDateTime atime;
    SceDateTime mtime;
    int32_t res;
} __attribute__((packed));

struct HostFsChstatCmd {
    struct HostFsCmd cmd;
    int32_t bits;
    uint32_t mode;
    int64_t size;
    /** Access time. */
    struct HostFsTimeStamp atime;
    /** Modification time. */
    struct HostFsTimeStamp mtime;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsChstatResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsRenameCmd {
    struct HostFsCmd cmd;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsRenameResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct HostFsChdirCmd {
    struct HostFsCmd cmd;
    uint32_t fsnum;
} __attribute__((packed));

struct HostFsChdirResp {
    struct HostFsCmd cmd;
    int32_t res;
} __attribute__((packed));

struct AsyncCommand {
    uint32_t magic;
    uint32_t channel;
} __attribute__((packed));

struct BulkCommand {
    uint32_t magic;
    uint32_t channel;
    uint32_t size;
} __attribute__((packed));

#ifndef PC_SIDE
// use psp2shell to print
#ifdef DEBUG

void p2s_debug(const char *fmt, ...);

#define printf p2s_debug
#define DEBUG_PRINTF p2s_debug
#define MODPRINTF p2s_debug
#else
#define DEBUG_PRINTF(fmt, ...)
#define MODPRINTF DEBUG_PRINTF
#endif

int usbhostfs_connected(void);

int command_xchg(void *outcmd, int outcmdlen, void *incmd, int incmdlen, const void *outdata,
                 int outlen, void *indata, int inlen);

int usbhostfs_start(void);

int usbhostfs_stop(void);

#endif // PC_SIDE

#endif // __USBHOSTFS_H__
