
//------------------------------------------------------------------------
void hexstring ( unsigned int d )
{
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
       rb-=4;
       rc=(d>>rb)&0xF;
       if(rc>9) rc+=0x37; else rc+=0x30;
       printf("rc: %d\n", rc);
       if(rb==0) break;
    }
    printf("AAP\n");
    printf("AAP\n");
}

unsigned int abcmath ( void );

//------------------------------------------------------------------------
int main ( void )
{
    hexstring(abcmath());
    return(0);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

