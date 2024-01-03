#include "../include/file.h"
#include "../include/kernel.h"
#include "../include/libc.h"
#include "../include/module.h"
#include "../include/network.h"

int libNet;
int libNetCtl;

int *(*sceNetErrnoLoc)(void);

int (*sceNetSocket)(const char *, int, int, int);
int (*sceNetSocketClose)(int);
int (*sceNetConnect)(int, struct sockaddr *, int);
int (*sceNetSend)(int, const void *, size_t, int);
int (*sceNetBind)(int, struct sockaddr *, int);
int (*sceNetListen)(int, int);
int (*sceNetAccept)(int, struct sockaddr *, unsigned int *);
int (*sceNetRecv)(int, void *, size_t, int);
int (*sceNetSocketAbort)(int, int);

int (*sceNetGetsockname)(int, struct sockaddr *, unsigned int *);
int (*sceNetGetsockopt)(int s, int level, int optname, void *restrict optval, socklen_t *restrict optlen);
int (*sceNetSetsockopt)(int s, int level, int optname, const void *optval, socklen_t optlen);

char (*sceNetInetNtop)(int af, const void *src, char *dst, int size);
int (*sceNetInetPton)(int af, const char *src, void *dst);

uint64_t (*sceNetHtonll)(uint64_t host64);
uint32_t (*sceNetHtonl)(uint32_t host32);
uint16_t (*sceNetHtons)(uint16_t host16);
uint64_t (*sceNetNtohll)(uint64_t net64);
uint32_t (*sceNetNtohl)(uint32_t net32);
uint16_t (*sceNetNtohs)(uint16_t net16);

int (*sceNetCtlInit)(void);
void (*sceNetCtlTerm)(void);
int (*sceNetCtlGetInfo)(int code, SceNetCtlInfo *info);

void initNetwork(void) {
  if (!libNet) {
    libNet = sceKernelLoadStartModule("libSceNet.sprx", 0, 0, 0, NULL, NULL);

    HOOKFUNCTION(libNet, sceNetErrnoLoc);

    HOOKFUNCTION(libNet, sceNetSocket);
    HOOKFUNCTION(libNet, sceNetSocketClose);
    HOOKFUNCTION(libNet, sceNetConnect);
    HOOKFUNCTION(libNet, sceNetSend);
    HOOKFUNCTION(libNet, sceNetBind);
    HOOKFUNCTION(libNet, sceNetListen);
    HOOKFUNCTION(libNet, sceNetAccept);
    HOOKFUNCTION(libNet, sceNetRecv);
    HOOKFUNCTION(libNet, sceNetSocketAbort);

    HOOKFUNCTION(libNet, sceNetGetsockname);
    HOOKFUNCTION(libNet, sceNetGetsockopt);
    HOOKFUNCTION(libNet, sceNetSetsockopt);

    HOOKFUNCTION(libNet, sceNetInetNtop);
    HOOKFUNCTION(libNet, sceNetInetPton);

    HOOKFUNCTION(libNet, sceNetHtonll);
    HOOKFUNCTION(libNet, sceNetHtonl);
    HOOKFUNCTION(libNet, sceNetHtons);
    HOOKFUNCTION(libNet, sceNetNtohll);
    HOOKFUNCTION(libNet, sceNetNtohl);
    HOOKFUNCTION(libNet, sceNetNtohs);
  }

  if (!libNetCtl) {
    libNetCtl = sceKernelLoadStartModule("libSceNetCtl.sprx", 0, 0, 0, NULL, NULL);

    HOOKFUNCTION(libNetCtl, sceNetCtlInit);
    HOOKFUNCTION(libNetCtl, sceNetCtlTerm);
    HOOKFUNCTION(libNetCtl, sceNetCtlGetInfo);
  }
}

int SckConnect(char *hostIP, int hostPort) {
  struct in_addr ip_addr;
  sceNetInetPton(AF_INET, hostIP, &ip_addr);
  struct sockaddr_in sk;
  sk.sin_len = sizeof(sk);
  sk.sin_family = AF_INET;
  sk.sin_addr = ip_addr;
  sk.sin_port = sceNetHtons(hostPort);
  memset(sk.sin_zero, 0, sizeof(sk.sin_zero));
  char socketName[] = "psocket";
  int sck = sceNetSocket(socketName, AF_INET, SOCK_STREAM, 0);
  sceNetConnect(sck, (struct sockaddr *)&sk, sizeof(sk));
  return sck;
}

void SckClose(int socket) {
  sceNetSocketClose(socket);
}

void SckSend(int socket, char *sdata, int length) {
  sceNetSend(socket, sdata, length, 0);
}

char *SckRecv(int socket) {
  char rbuf[4096], *retval = malloc(sizeof(char) * 1);
  int plen, length = 0, i;
  while ((plen = sceNetRecv(socket, rbuf, sizeof(rbuf), 0)) > 0) {
    void *tmp = (char *)realloc(retval, sizeof(char) * (length + plen) + 1);
    if (tmp == NULL) {
      free(retval);
      return NULL;
    } else {
      retval = tmp;
    }
    for (i = 0; i < plen; i++) {
      retval[length] = rbuf[i];
      length++;
    }
    memset(rbuf, 0, sizeof rbuf);
  }
  return retval;
}

void SckRecvf(int socket, char *destfile) {
  char rbuf[4096];
  int plen, fid = open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  while ((plen = sceNetRecv(socket, rbuf, sizeof(rbuf), 0)) > 0) {
    write(fid, rbuf, plen);
    memset(rbuf, 0, sizeof rbuf);
  }
  close(fid);
}
