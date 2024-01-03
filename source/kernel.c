#include "../include/module.h"
#include "../include/syscall.h"
#include "../include/kernel.h"

int libKernelHandle;

int **__stack_chk_guard;
void (*__stack_chk_fail)(void);
int *(*__error)();

int (*sceKernelError)(int);

int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

int (*sceKernelAllocateDirectMemory)(off_t searchStart, off_t searchEnd, size_t length, size_t alignment, int type, off_t *physicalAddressDestination);
int (*sceKernelMapDirectMemory)(void **addr, size_t length, int protection, int flags, off_t start, size_t alignment);
size_t(*sceKernelGetDirectMemorySize)();

int (*sceKernelStat)(const char *path, void *buf);
int (*sceKernelOpen)(const char *path, int flags, int mode);
int (*sceKernelRead)(int fd, void *buf, size_t nbyte);
int (*sceKernelLseek)(int fd, off_t offset, int whence);
int (*sceKernelClose)(int fd);

unsigned int (*sceKernelSleep)(unsigned int seconds);
int (*sceKernelUsleep)(unsigned int microseconds);
int (*sceKernelGettimeofday)(SceKernelTimeval *tp);
uint64_t(*sceKernelGetProcessTime)(void);
int (*sceKernelGetCurrentCpu)(void);

int (*sysctl)(int *name, unsigned int namelen, char *oldval, size_t *oldlen, char *newval, size_t newlen);
int (*sysctlbyname)(char *name, char *oldval, size_t *oldlen, char *newval, size_t newlen);
int (*sysarch)(int type, void *arg);
int (*execve)(char *path, char *argv[], char *envp[]);

void *(*pthread_self)();
int (*pthread_setaffinity_np)(void *one, long unsigned int two, void *three);

int (*sceKernelCreateEqueue)(SceKernelEqueue *eq, const char *name);
int (*sceKernelDeleteEqueue)(SceKernelEqueue eq);
int (*sceKernelAddUserEvent)(SceKernelEqueue eq, int id);
int (*sceKernelAddReadEvent)(SceKernelEqueue eq, int fd, size_t size, void *udata);

int (*getuid)();
int (*getgid)();
int (*getpid)();

int (*setuid)(int uid);
int (*setgid)(int gid);
int (*setreuid)(int ruid, int euid);
int (*setregid)(int rgid, int egid);

int (*sceKernelSendNotificationRequest)(int device, SceNotificationRequest *req, size_t size, int blocking);
const char *(*sceKernelGetFsSandboxRandomWord)();
int (*sceKernelGetSystemSwVersion)(SceFwInfo *fw_info);

uint32_t(*sceKernelGetCpuTemperature)(uint32_t *);

SYSCALL(kill, 37);
SYSCALL(ioctl, 54);
SYSCALL(kexec, 11);

void initKernel(void) {
  if (libKernelHandle) return;
  
  __error = NULL;

  if (loadModule("libkernel.sprx", &libKernelHandle)) {
    if (loadModule("libkernel_web.sprx", &libKernelHandle)) {
      loadModule("libkernel_sys.sprx", &libKernelHandle);
    }
  }

  HOOKFUNCTION(libKernelHandle, __stack_chk_guard);
  HOOKFUNCTION(libKernelHandle, __stack_chk_fail);
  HOOKFUNCTION(libKernelHandle, __error);

  HOOKFUNCTION(libKernelHandle, sceKernelError);

  HOOKFUNCTION(libKernelHandle, sceKernelLoadStartModule);

  HOOKFUNCTION(libKernelHandle, sceKernelAllocateDirectMemory);
  HOOKFUNCTION(libKernelHandle, sceKernelMapDirectMemory);
  HOOKFUNCTION(libKernelHandle, sceKernelGetDirectMemorySize);

  HOOKFUNCTION(libKernelHandle, sceKernelStat);
  HOOKFUNCTION(libKernelHandle, sceKernelOpen);
  HOOKFUNCTION(libKernelHandle, sceKernelRead);
  HOOKFUNCTION(libKernelHandle, sceKernelLseek);
  HOOKFUNCTION(libKernelHandle, sceKernelClose);

  HOOKFUNCTION(libKernelHandle, sceKernelSleep);
  HOOKFUNCTION(libKernelHandle, sceKernelUsleep);
  HOOKFUNCTION(libKernelHandle, sceKernelGettimeofday);
  HOOKFUNCTION(libKernelHandle, sceKernelGetProcessTime);
  HOOKFUNCTION(libKernelHandle, sceKernelGetCurrentCpu);

  HOOKFUNCTION(libKernelHandle, sysctl);
  HOOKFUNCTION(libKernelHandle, sysctlbyname);
  HOOKFUNCTION(libKernelHandle, sysarch);
  HOOKFUNCTION(libKernelHandle, execve);

  HOOKFUNCTION(libKernelHandle, pthread_self);
  HOOKFUNCTION(libKernelHandle, pthread_setaffinity_np);

  HOOKFUNCTION(libKernelHandle, sceKernelCreateEqueue);
  HOOKFUNCTION(libKernelHandle, sceKernelDeleteEqueue);
  HOOKFUNCTION(libKernelHandle, sceKernelAddUserEvent);
  HOOKFUNCTION(libKernelHandle, sceKernelAddReadEvent);

  HOOKFUNCTION(libKernelHandle, getuid);
  HOOKFUNCTION(libKernelHandle, getgid);
  HOOKFUNCTION(libKernelHandle, getpid);

  HOOKFUNCTION(libKernelHandle, setuid);
  HOOKFUNCTION(libKernelHandle, setgid);
  HOOKFUNCTION(libKernelHandle, setreuid);
  HOOKFUNCTION(libKernelHandle, setregid);

  HOOKFUNCTION(libKernelHandle, sceKernelSendNotificationRequest);
  HOOKFUNCTION(libKernelHandle, sceKernelGetFsSandboxRandomWord);
  HOOKFUNCTION(libKernelHandle, sceKernelGetSystemSwVersion);

  HOOKFUNCTION(libKernelHandle, sceKernelGetCpuTemperature);
}
