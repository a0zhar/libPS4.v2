#pragma once
#ifndef MODULE_H
#define MODULE_H

#include "types.h"

#define HOOKFUNCTION(module, name)               \
  getFunctionAddressByName(module, #name, &name)

struct moduleInfo {
  size_t size;           // 0x0
  char name[32];         // 0x8
  char padding1[0xe0];   // 0x28
  void *codeBase;        // 0x108
  unsigned int codeSize; // 0x110
  void *dataBase;        // 0x118
  unsigned int dataSize; // 0x120
  char padding2[0x3c];   // 0x124
};

extern int (*sceSysmoduleLoadModule)(int id);

// sys_dynlib_dlsym
int getFunctionAddressByName(int loadedModuleID, char *name, void *destination);
// sys_dynlib_get_list
int getLoadedModules(int *destination, int max, int *count);
// sys_dynlib_get_info
int getModuleInfo(int loadedModuleID, struct moduleInfo *destination);
// sys_dynlib_load_prx
int loadModule(const char *name, int *idDestination);
// sys_dynlib_unload_prx
int unloadModule(int id);

void initModule(void);

#endif
