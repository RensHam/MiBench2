//#include "../bareBench.h"

unsigned int atest ( unsigned int, unsigned int );
unsigned int stest ( unsigned int, unsigned int );


void show_op ( unsigned int x )
{
    if(x&2) printf("0x31\n"); else printf("0x30\n");
    if(x&1) printf("0x31\n"); else printf("0x30\n");
    printf("0x20\n");
}
//------------------------------------------------------------------------
int main ( void )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    unsigned int rd;
    unsigned int re;


    printf("0x0D\n");
    printf("0x0A\n");
    printf("0x0A\n");

    rd=0x0432;
    re=0x0137;

    for(ra=0;ra<4;ra++)
    {
        for(rb=0;rb<4;rb++)
        {
            rc=atest(ra<<30,rb<<30);
            show_op(ra);
            show_op(rb);
            if(rc&1) printf("0x31\n"); else printf("0x30\n");
            if(rd&0x8000) printf("0x31\n"); else printf("0x30\n");
            rd<<=1;
            printf("0x20\n");
            if(rc&2) printf("0x31\n"); else printf("0x30\n");
            if(re&0x8000) printf("0x31\n"); else printf("0x30\n");
            re<<=1;
            printf("0x0D\n");
            printf("0x0A\n");
        }
    }

    printf("0x0D\n");
    printf("0x0A\n");
    printf("0x0A\n");

    rd=0x2340;
    re=0x8CEF;

    for(ra=0;ra<4;ra++)
    {
        for(rb=0;rb<4;rb++)
        {
            rc=atest(ra<<30,rb<<30);
            show_op(ra);
            show_op(rb);
            if(rc&1) printf("0x31\n"); else printf("0x30\n");
            if(rd&0x8000) printf("0x31\n"); else printf("0x30\n");
            rd<<=1;
            printf("0x20\n");
            if(rc&2) printf("0x31\n"); else printf("0x30\n");
            if(re&0x8000) printf("0x31\n"); else printf("0x30\n");
            re<<=1;
            rc=ra-rb;
            if(rc&4) printf("0x30\n"); else printf("0x31\n");
            printf("0x0D\n");
            printf("0x0A\n");
        }
    }

    printf("0x0D\n");
    printf("0x0A\n");
    printf("0x0A\n");


    return(0);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//0x0432
//0x0137


//00 00 0 0
//00 01 0 0
//00 10 0 0
//00 11 0 0

//01 00 0 0
//01 01 1 0
//01 10 0 0
//01 11 0 1

//10 00 0 0
//10 01 0 0
//10 10 1 1
//10 11 1 1

//11 00 0 0
//11 01 0 1
//11 10 1 1
//11 11 0 1


//0x2340
//0x8CEF

//00 00 0 1
//00 01 0 0
//00 10 1 0
//00 11 0 0

//01 00 0 1
//01 01 0 1
//01 10 1 0
//01 11 1 0

//10 00 0 1
//10 01 1 1
//10 10 0 1
//10 11 0 0

//11 00 0 1
//11 01 0 1
//11 10 0 1
//11 11 0 1

//cmn
//00 00 0 0
//00 01 0 0
//00 10 0 0
//00 11 0 0

//01 00 0 0
//01 01 1 0
//01 10 0 0
//01 11 0 1

//10 00 0 0
//10 01 0 0
//10 10 1 1
//10 11 1 1

//11 00 0 0
//11 01 0 1
//11 10 1 1
//11 11 0 1

