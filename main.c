#include <stdarg.h>
#include <stdio.h>

#include "circle.h"
 



int main(int argc, char ** argv);

int main(int argc, char ** argv)
{
//CircleParms_t c;
int i;

#if 1
         // x   y   i  j   f
//    arc_ij( 2,  0,  1, 0,  0);
    arc_ij ( 2.5,  3.598076211,  1, 1, 0);
    arc_r ( 2.5,  3.598076211,  3,  0);
#else
for( i = 0 ; i < g_test_cnt ; i++)
{
    PrintCircleParms(&(g_test[i]),"tests" );
    circle( &(g_test[i]));

}
#endif







}






