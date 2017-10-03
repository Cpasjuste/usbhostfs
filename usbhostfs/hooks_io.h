//
// Created by cpasjuste on 10/07/17.
//

#ifndef _HOOKS_IO_H_
#define _HOOKS_IO_H_

#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/io/dirent.h>
#include <psp2kern/io/stat.h>
#include <libk/stdlib.h>
#include <libk/string.h>
#include <libk/stdio.h>
#include <taihen.h>

#define MAX_HOST_FD 128

typedef struct _fopen_fd {
    uint32_t sce_reserved[2];
    int fd;
    SceUID uid;
} fopen_fd;

typedef struct Hook {
    SceUID uid;
    tai_hook_ref_t ref;
    const char name[32];
    uint32_t lib;
    uint32_t nid;
    const void *func;
} Hook;

// kernel hooks
enum {
    HOOK_IO_KOPEN = 0,
    HOOK_IO_KOPEN2,
    HOOK_IO_KCLOSE,
    HOOK_IO_KREAD,
    HOOK_IO_KWRITE,
    HOOK_IO_KLSEEK,
    HOOK_IO_KREMOVE,
    HOOK_IO_KRENAME,
    HOOK_IO_KDOPEN,
    HOOK_IO_KDREAD,
    HOOK_IO_KDCLOSE,
    HOOK_IO_KMKDIR,
    HOOK_IO_KRMDIR,
    HOOK_IO_KGETSTAT,
    HOOK_IO_KGETSTATBYFD,
    HOOK_IO_KCHSTAT,
    HOOK_IO_KDEVCTL,
    HOOK_END
};

// psp2/io/fcntl.h
SceUID _ksceIoOpen(const char *path, int flags, SceMode mode);

SceUID _ksceIoOpen2(SceUID pid, const char *path, int flags, SceMode mode);

int _ksceIoClose(SceUID fd);

int _ksceIoRead(SceUID fd, void *data, SceSize size);

int _ksceIoWrite(SceUID fd, const void *data, SceSize size);

SceOff _ksceIoLseek(SceUID fd, SceOff offset, int whence);

int _ksceIoRemove(const char *file);

int _ksceIoRename(const char *oldname, const char *newname);
// psp2/io/fcntl.h

// psp2/io/dirent.h
SceUID _ksceIoDopen(const char *dirname);

int _ksceIoDread(SceUID fd, SceIoDirent *dir);

int _ksceIoDclose(SceUID fd);
// psp2/io/dirent.h

// io/stat.h
int _ksceIoMkdir(const char *dir, SceMode mode);

int _ksceIoRmdir(const char *path);

int _ksceIoGetstat(const char *file, SceIoStat *stat);

int _ksceIoGetstatByFd(SceUID fd, SceIoStat *stat);

int _ksceIoChstat(const char *file, SceIoStat *stat, int bits);
// io/stat.h

// io/devctl.h
int _ksceIoDevctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
// io/devctl.h

void set_hooks_io();

void delete_hooks_io();

#ifdef DEBUG
void p2s_debug(const char *fmt, ...);
#define printf p2s_debug
#endif

#endif //_HOOKS_IO_H_
