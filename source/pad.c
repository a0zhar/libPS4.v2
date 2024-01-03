#include "../include/kernel.h"
#include "../include/module.h"
#include "../include/pad.h"

int libPad;

int (*scePadInit)(void);
int (*scePadOpen)(int userID, int, int, void *);
int (*scePadClose)(int handle);
int (*scePadRead)(int handle, void *data, int count);
int (*scePadReadState)(int handle, void *data);

void initPad(void) {
  if (libPad) return;
  
  libPad = sceKernelLoadStartModule("libScePad.sprx", 0, 0, 0, NULL, NULL);

  HOOKFUNCTION(libPad, scePadInit);
  HOOKFUNCTION(libPad, scePadOpen);
  HOOKFUNCTION(libPad, scePadClose);
  HOOKFUNCTION(libPad, scePadRead);
  HOOKFUNCTION(libPad, scePadReadState);

  scePadInit();
}
