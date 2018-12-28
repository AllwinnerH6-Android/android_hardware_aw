#ifndef		OS_PLATFORM_H_
#define 	OS_PLATFORM_H_

//#define __OS_LINUX
#ifdef	__OS_LINUX
#ifndef	__OS_ANDROID
#include "../../sys/eldk_types.h"
#endif
//#include "statname.h"
#include <stdio.h>
#endif 

#ifndef __OS_ANDROID
#ifdef	__OS_LINUX
  #ifndef 	NULL
	#define 	NULL 0
	#endif
	typedef __s64  int64_t; 
	typedef __u64 uint64_t; 
	typedef __s64  __int64;
#else
	#ifndef 	int64_t
	  typedef __int64  int64_t; 
	#endif
	#ifndef 	uint64_t
	  typedef unsigned __int64 uint64_t; 
	#endif
#endif
#else //ANDROID
	typedef long long __int64;
#endif
	//#define DOS
#ifdef	DOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//#define UCOS
#ifdef	UCOS

#ifndef 	NULL
#define 	NULL 0
#endif
#ifndef 	size_t
typedef unsigned int size_t; 
#endif

#include "drv_adec_lib_cfg.h"
#endif
#endif

