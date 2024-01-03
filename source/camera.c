#include "../include/kernel.h"
#include "../include/module.h"
#include "../include/camera.h"

int libCamera;

int (*sceCameraOpen)(int userid, int type, int index, void *);
int (*sceCameraClose)(int handle);
int (*sceCameraIsAttached)(int index);
int (*sceCameraGetFrameData)(int handle, SceCameraFrameData *frame);
int (*sceCameraStart)(int handle, SceCameraStartParameter *param);
int (*sceCameraStop)(int handle);
int (*sceCameraGetDeviceInfo)(int handle, SceCameraDeviceInfo *info);
int (*sceCameraGetDeviceConfig)(int handle, SceCameraConfig *config);
int (*sceCameraGetConfig)(int handle, SceCameraConfig *config);
int (*sceCameraSetConfig)(int handle, SceCameraConfig *config);

void initCamera(void) {
  if (libCamera) return;

  libCamera = sceKernelLoadStartModule("libSceCamera.sprx", 0, 0, 0, NULL, NULL);

  HOOKFUNCTION(libCamera, sceCameraOpen);
  HOOKFUNCTION(libCamera, sceCameraClose);
  HOOKFUNCTION(libCamera, sceCameraIsAttached);
  HOOKFUNCTION(libCamera, sceCameraGetFrameData);
  HOOKFUNCTION(libCamera, sceCameraStart);
  HOOKFUNCTION(libCamera, sceCameraStop);
  HOOKFUNCTION(libCamera, sceCameraGetDeviceInfo);
  HOOKFUNCTION(libCamera, sceCameraGetDeviceConfig);
  HOOKFUNCTION(libCamera, sceCameraGetConfig);
  HOOKFUNCTION(libCamera, sceCameraSetConfig);
}
