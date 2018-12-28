#ifndef DO_AUDIORESAMPLE_H
#define DO_AUDIORESAMPLE_H
#include "audiomix.h"
#include "aumixcom.h"

int do_audioresample(void* AMX, int insrt,int inch,char* inbuf,int* buflen,int outsrt);

#endif
