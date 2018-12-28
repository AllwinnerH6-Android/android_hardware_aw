#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include "do_audioresample.h"

int do_audioresample(void* ptr, int insrt,int inch,char* inbuf,int* buflen,int outsrt)
{
	PcmInfo AmxInputA;
	PcmInfo AmxInputB;
	PcmInfo AmxOutput;
	AudioMix* AMX = (AudioMix*)ptr;
	int templen = 0,temptotallen = 0;
	short   pTempResampleBuffer[64*1024] = {0};	

	AMX->InputB = &AmxInputB;
	AMX->InputA = &AmxInputA;
	AMX->Output = &AmxOutput;
	temptotallen = templen = 0;

	AMX->InputB->SampleRate = insrt;
	AMX->InputB->Chan       = inch;
	AMX->InputB->PCMPtr     = (short*)inbuf;
	AMX->InputB->PcmLen     = *buflen / 2 / inch;
	AMX->InputA->PCMPtr = pTempResampleBuffer;
	AMX->InputA->SampleRate = outsrt;
	AMX->InputA->Chan = AMX->InputB->Chan;
	AMX->InputA->PcmLen = 1024 ;
	while(AMX->InputB->PcmLen)
	{
		do_AuMIX(AMX);
		templen = AMX->MixLen * 2 * AMX->Mixch;
		temptotallen += templen;
		AMX->InputA->PCMPtr += AMX->MixLen * AMX->Mixch;
	}
	memcpy(inbuf,pTempResampleBuffer,temptotallen);
	*buflen = temptotallen;
	return 0;

}
