#include "../include/kernel.h"
#include "../include/module.h"
#include "../include/pthread.h"

int libPthread;

int (*scePthreadCreate)(ScePthread *thread, const ScePthreadAttr *attr, void *(*entry)(void *), void *arg, const char *name);
void (*scePthreadExit)(void *value);
int (*scePthreadDetach)(ScePthread thread);
int (*scePthreadJoin)(ScePthread thread, void **value_ptr);
void (*scePthreadYield)(void);
ScePthread (*scePthreadSelf)(void);
int (*scePthreadCancel)(ScePthread thread);

int (*scePthreadMutexInit)(ScePthreadMutex *mutex, const ScePthreadMutexattr *attr, const char *name);
int (*scePthreadMutexDestroy)(ScePthreadMutex *mutex);
int (*scePthreadMutexLock)(ScePthreadMutex *mutex);
int (*scePthreadMutexTrylock)(ScePthreadMutex *mutex);
int (*scePthreadMutexTimedlock)(ScePthreadMutex *mutex, SceKernelUseconds usec);
int (*scePthreadMutexUnlock)(ScePthreadMutex *mutex);

void initPthread(void) {
  if (libPthread) return;

  HOOKFUNCTION(libKernelHandle, scePthreadCreate);
  HOOKFUNCTION(libKernelHandle, scePthreadExit);
  HOOKFUNCTION(libKernelHandle, scePthreadDetach);
  HOOKFUNCTION(libKernelHandle, scePthreadJoin);
  HOOKFUNCTION(libKernelHandle, scePthreadYield);
  HOOKFUNCTION(libKernelHandle, scePthreadSelf);
  HOOKFUNCTION(libKernelHandle, scePthreadCancel);

  HOOKFUNCTION(libKernelHandle, scePthreadMutexInit);
  HOOKFUNCTION(libKernelHandle, scePthreadMutexDestroy);
  HOOKFUNCTION(libKernelHandle, scePthreadMutexLock);
  HOOKFUNCTION(libKernelHandle, scePthreadMutexTrylock);
  HOOKFUNCTION(libKernelHandle, scePthreadMutexTimedlock);
  HOOKFUNCTION(libKernelHandle, scePthreadMutexUnlock);

  libPthread = 1;
}
