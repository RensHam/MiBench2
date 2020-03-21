
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pulpino.h"
#include "int.h"
#include "timer.h"
#include "event.h"

#include "picojpeg.h"
#include "jpegdata.h"
unsigned int doff;
//unsigned int dlen;
//unsigned char odat[128][256][3];

unsigned char pjpeg_need_bytes_callback(unsigned char* pBuf, unsigned char buf_size, unsigned char *pBytes_actually_read, void *pCallback_data)
{
    unsigned int ra;
//   uint n;
  // pCallback_data;

    printf("callback buf_size %u\n",buf_size);

//   n = min(g_nInFileSize - g_nInFileOfs, buf_size);
   //if (n && (fread(pBuf, 1, n, g_pInFile) != n))
      //return PJPG_STREAM_READ_ERROR;
   //*pBytes_actually_read = (unsigned char)(n);
   //g_nInFileOfs += n;

    //memcpy(pBuf,&data[doff],buf_size);
    for(ra=0;ra<buf_size;ra++) pBuf[ra]=jpegdata[doff+ra];
    doff+=buf_size;
    *pBytes_actually_read = buf_size;
    return 0;
}


int main ( void )
{
   ECP = 0xFFFFFFFF;
   IER = 1 << 29;
   int_enable();


   TPRA = 0x0;
   TIRA = 0x0;
   TOCRA = 1200000; 
   TPRA = 0x1;
    //FILE *fp;
    //FILE *fpout;
    unsigned char status;
    pjpeg_image_info_t pInfo;
    unsigned int sum;
    //unsigned int ra;
    unsigned int rb;
    //unsigned int x,rx;
    //unsigned int y,ry;


    //fp=fopen("base.bmp","rb");
    //if(fp==NULL) return(1);
    //dlen=fread(odat,1,122,fp);
    //fclose(fp);
    //if(dlen!=122) return(1);
    //fpout=fopen("out.bmp","wb");
    //if(fpout==NULL) return(1);
    //fwrite(odat,1,122,fpout);


    doff=0;

    status = pjpeg_decode_init(&pInfo, pjpeg_need_bytes_callback, NULL,0);

    if (status)
    {
        printf("pjpeg_decode_init() failed with status %u\n", status);
        return(1);
    }
    //x=0;
    //y=128-1;
    sum=0;
    while(status==0)
    {
        status=pjpeg_decode_mcu();
        //printf("decode %u\n",ra);
        if(status==0)
        {
            switch(pInfo.m_scanType)
            {
                case PJPG_GRAYSCALE: break;
                case PJPG_YH1V1:
                {
                    //rx=0;
                    //ry=0;
                    for(rb=0;rb<64;rb++)
                    {
                        sum+=pInfo.m_pMCUBufB[rb];
                        sum+=pInfo.m_pMCUBufG[rb];
                        sum+=pInfo.m_pMCUBufR[rb];
                        //odat[y-ry][x+rx][0]=pInfo.m_pMCUBufB[rb];
                        //odat[y-ry][x+rx][1]=pInfo.m_pMCUBufG[rb];
                        //odat[y-ry][x+rx][2]=pInfo.m_pMCUBufR[rb];
                        //rx++;
                        //if(rx>=8)
                        //{
                            //rx=0;
                            //ry++;
                        //}
                    }
                    //x+=8;
                    //if(x>=256)
                    //{
                        //y-=8;
                        //x=0;
                    //}
                    //// PJPG_H1V1: Each MCU contains is decoded to a single block of 8x8 RGB pixels.
////   unsigned char *m_pMCUBufR;
                    //for(rb=0;rb<64;rb++) sum+=pInfo.m_pMCUBufR[rb];
                    //fwrite(pInfo.m_pMCUBufR,1,64,fpout);
                    //fwrite(pInfo.m_pMCUBufR,1,64,fp);
   ////unsigned char *m_pMCUBufG;
                    //for(rb=0;rb<64;rb++) sum+=pInfo.m_pMCUBufG[rb];
                    //fwrite(pInfo.m_pMCUBufG,1,64,fpout);
                    //fwrite(pInfo.m_pMCUBufG,1,64,fp);
   ////unsigned char *m_pMCUBufB;
                    //for(rb=0;rb<64;rb++) sum+=pInfo.m_pMCUBufB[rb];
                    //fwrite(pInfo.m_pMCUBufB,1,64,fpout);
                    //fwrite(pInfo.m_pMCUBufB,1,64,fp);
                    break;
                }
                case PJPG_YH2V1: break;
                case PJPG_YH1V2: break;
                case PJPG_YH2V2: break;
            }
        }
    }
    if(status!=PJPG_NO_MORE_BLOCKS)
    {
        printf("status %u\n",status);
        return(1);
    }
    printf("----\n");
    printf("%d\n",pInfo.m_width);
    printf("%d\n",pInfo.m_height);
    printf("%d\n",pInfo.m_comps);
    printf("%d\n",pInfo.m_MCUSPerRow);
    printf("%d\n",pInfo.m_MCUSPerCol);
    printf("%d\n",pInfo.m_scanType);
    printf("%d\n",pInfo.m_MCUWidth);
    printf("%d\n",pInfo.m_MCUHeight);
    printf("---- sum 0x%08X %u\n",sum,sum);


    //fwrite(odat,1,sizeof(odat),fpout);
    //fclose(fpout);
   // disable timer
   TPRA = 0x0;
   ECP = 0x1;
   int_disable();

for(int runs = 0; runs < 109; runs++) 
ISR_TA_CMP();
    return(0);
}

void __attribute__((optimize("O0"))) ISR_TA_CMP(void) { 
 ICP = (1 << 29); 
static int i = 1048572; 
for (int x = 0; x < 32; x++) {
i += 4; 
 asm volatile ( 
 "mv	x5, %0\n" // should be x5 = i; 
"lw	x6, 0(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x5)\n" // * i = a;
"lw	x6, 4(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x5)\n" // * i = a;
"lw	x6, 8(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x5)\n" // * i = a;
"lw	x6, 12(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x5)\n" // * i = a;
"lw	x6, 16(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x5)\n" // * i = a;
"lw	x6, 20(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x5)\n" // * i = a;
"lw	x6, 24(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x5)\n" // * i = a;
"lw	x6, 28(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x5)\n" // * i = a;
"lw	x6, 32(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x5)\n" // * i = a;
"lw	x6, 36(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x5)\n" // * i = a;
"lw	x6, 40(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x5)\n" // * i = a;
"lw	x6, 44(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x5)\n" // * i = a;
"lw	x6, 48(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x5)\n" // * i = a;
"lw	x6, 52(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x5)\n" // * i = a;
"lw	x6, 56(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x5)\n" // * i = a;
"lw	x6, 60(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x5)\n" // * i = a;
"lw	x6, 64(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x5)\n" // * i = a;
"lw	x6, 68(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x5)\n" // * i = a;
"lw	x6, 72(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x5)\n" // * i = a;
"lw	x6, 76(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x5)\n" // * i = a;
"lw	x6, 80(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x5)\n" // * i = a;
"lw	x6, 84(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x5)\n" // * i = a;
"lw	x6, 88(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x5)\n" // * i = a;
"lw	x6, 92(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x5)\n" // * i = a;
"lw	x6, 96(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x5)\n" // * i = a;
"lw	x6, 100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x5)\n" // * i = a;
"lw	x6, 104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x5)\n" // * i = a;
"lw	x6, 108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x5)\n" // * i = a;
"lw	x6, 112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x5)\n" // * i = a;
"lw	x6, 116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x5)\n" // * i = a;
"lw	x6, 120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x5)\n" // * i = a;
"lw	x6, 124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x5)\n" // * i = a;
"lw	x6, 0(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x5)\n" // * i = a;
"lw	x6, 4(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x5)\n" // * i = a;
"lw	x6, 8(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x5)\n" // * i = a;
"lw	x6, 12(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x5)\n" // * i = a;
"lw	x6, 16(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x5)\n" // * i = a;
"lw	x6, 20(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x5)\n" // * i = a;
"lw	x6, 24(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x5)\n" // * i = a;
"lw	x6, 28(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x5)\n" // * i = a;
"lw	x6, 32(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x5)\n" // * i = a;
"lw	x6, 36(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x5)\n" // * i = a;
"lw	x6, 40(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x5)\n" // * i = a;
"lw	x6, 44(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x5)\n" // * i = a;
"lw	x6, 48(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x5)\n" // * i = a;
"lw	x6, 52(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x5)\n" // * i = a;
"lw	x6, 56(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x5)\n" // * i = a;
"lw	x6, 60(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x5)\n" // * i = a;
"lw	x6, 64(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x5)\n" // * i = a;
"lw	x6, 68(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x5)\n" // * i = a;
"lw	x6, 72(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x5)\n" // * i = a;
"lw	x6, 76(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x5)\n" // * i = a;
"lw	x6, 80(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x5)\n" // * i = a;
"lw	x6, 84(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x5)\n" // * i = a;
"lw	x6, 88(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x5)\n" // * i = a;
"lw	x6, 92(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x5)\n" // * i = a;
"lw	x6, 96(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x5)\n" // * i = a;
"lw	x6, 100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x5)\n" // * i = a;
"lw	x6, 104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x5)\n" // * i = a;
"lw	x6, 108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x5)\n" // * i = a;
"lw	x6, 112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x5)\n" // * i = a;
"lw	x6, 116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x5)\n" // * i = a;
"lw	x6, 120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x5)\n" // * i = a;
"lw	x6, 124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x5)\n" // * i = a;
:"=r"(i) : : "x5", "x6", "x7");
i += 124; 
}
if (i > 1073151) { i = 1048572;} //Flip arround memory should not be 2047 because of +4 at beginning 
TIRA = 0x0;
}
