/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * *    * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef A83T
#include "./platform/SUN8IW6P1_A83T.h"
#elif defined A64
#include "./platform/SUN50IW1P1_A64.h"
#elif defined A80
#include "./platform/SUN9IW1P1_A80.h"
#elif defined A33
#include "./platform/SUN8IW5P1_A33.h"
#elif defined A63
#include "./platform/SUN50IW3P1_A63.h"
#elif defined VR9
#include "./platform/SUN50IW3P1_VR9.h"
#elif defined A50
#include "./platform/SUN8IW15P1_A50.h"
#elif defined H6
#include "./platform/SUN50IW6P1_H6.h"
#endif



#define  INTERACTIVE_GOVERNOR     "interactive"


typedef enum {
	POWER_STATE_MUSIC = 1,
	POWER_STATE_HOME, //2
	POWER_STATE_SCAREEN_OFF, //3
	POWER_STATE_NORMAL, //4
	POWER_STATE_SUSTAINED, //5
	POWER_STATE_VR_SUSTAINED, //6
	POWER_STATE_VR, //7
	POWER_STATE_LAUNCH, //8
	POWER_STATE_BENCHMARK

}Power_Perfromance_State;



void sysfs_write(const char *path, char *s);

/*return true:hit case
 *       false:need follow deal
 */
bool power_hint_platform(unsigned int hint,int parmdata);
void power_set_interactive_platform(int enable);

Power_Perfromance_State get_cur_power_state();
Power_Perfromance_State get_pre_power_state();
void set_power_state(Power_Perfromance_State state);
