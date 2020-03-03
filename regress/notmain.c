//#include "../bareBench.h"

//------------------------------------------------------------------------

int regression ( void );


#define THUL_UART_BASE 0xE0000000
void hexstring ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        printf("%d\n", rc);
        if(rb==0) break;
    }
    printf("0x0D");
    printf("0x0A");
}
//------------------------------------------------------------------------
int main ( void )
{
    regression();
    return(0);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

