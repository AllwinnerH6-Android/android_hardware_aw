#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "do_audioresample.h"

int main(int argv, char** argc)
{
    FILE* in = NULL,*out = NULL;
    int ret = 0;
    AudioMix AMX;
    char buf[64*1024];
    int lentable[6] = {1024, 512, 768, 256, 2048, 128};
    int idx = 0;
    char *p = buf;
    in  = fopen("Z:\\DS5-WORK\\audioresample\\Debug\\1ch_apology_48k.pcm","rb");
    out = fopen("Z:\\DS5-WORK\\audioresample\\Debug\\1ch_apology_96k.pcm","wb");
    AMX.RESI = Init_ResampleInfo();
    AMX.ByPassflag = 2;//Resample only
    do{
    	int len = lentable[idx];
    	ret = fread(p,1,len,in);
    	if(!ret) break;
    	do_audioresample((void*)&AMX,44100,1,p,&ret,96000);
    	fwrite(p,1,ret,out);

    }while(1);
    Destroy_ResampleInfo(AMX.RESI);
    fclose(in);
    fclose(out);
	return 0;
}
