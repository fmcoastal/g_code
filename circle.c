#include <stdarg.h>
#include <stdio.h>
#include <math.h>       // need -lm for linking

#include "g_code.h"
#include "circle.h"

/*
typedef struct circleparms_struct{
      float xS;     // x start
      float yS;     // y start
      float xF;     // x final
      float yF;     // y final
      float xC;     // x Center
      float yC;     // y Center
      int   dir;  //  1=CCW  0 = CW
} CircleParms_t;
*/


int g_test_cnt=3;

CircleParms_t g_test[] = {
       {-.5      ,  0    ,  0     ,  -.5    ,0   ,0  , DIR_CCW},
       {  0      ,  -.5  , .5     ,    0    ,0   ,0  , DIR_CCW},
       { -0.866  ,  .5   , -.866  ,  -.5    ,0   ,0  , DIR_CCW},
       { .5      , .866  , .866   ,   .5    ,0   ,0  , DIR_CCW},
       { .5      , .866  , -.866  ,   .5    ,0   ,0  , DIR_CCW}
} ;
 

void PrintCircleParms(CircleParms_t * d, char * string)
{
    printf("%s\n",string);
    printf("Sx:%4.4f  Sy:%4.4f  Fx:%4.4f  Fy:%4.4f Cx:%4.4f  Cy:%4.4f %s\n",
                    d->xS, d->yS, 
                    d->xF, d->yF, 
                    d->xC, d->yC,
                   ((d->dir == DIR_CCW) ? "CCW" : "CW" )); // CCW = 0
}

// cos 30 = .8660
// sin 30 = .5

float g_xDelta = 0.001;

int WellBehaved(CircleParms_t *d)
{
    float r2;
    float r;
    float x_min;
    float x_max;
    float x;
    float x_next;
    float y;
    float y_next;
    float x_stop;
    float sign;
    int flag = 0;
    r2 = (d->xC - d->xS)*(d->xC - d->xS) + (d->yC - d->yS)*(d->yC - d->yS);
    r = sqrt (r2);
    x_min = d->xC - r ;
    x_max = d->xC + r ;
    x_stop = roundf(d->xF * 1000) / 1000;
    printf("Circle Radius  %4.4f\n",sqrt(r2));
    printf("        x_min  %4.4f\n",x_min);
    printf("        x_max  %4.4f\n",x_max);
    printf("        x_stop  %4.4f\n",x_stop);
 
    if(d->dir == 0) // CCW
    {
        if(( d->xS == x_min ) || ( d->yS < d->yC )) // left most and y below the circle center
        {
             flag = 1;
             // x will increment
      
             x = d->xS;
             y = d->yS;
             sign = ( y < d->yC ? -1 : 1 );
             do{
                x_next = x + g_xDelta;  
                // r2 = x2 + y2 ;
                y_next = sqrt( r2 - ( x_next )*( x_next )  ) * sign ;
                printf("m1 x,y %4.4f,%4.4f   x_next,y_next %4.4f,%4.4f\n",x,y,x_next,y_next);
                x = x_next;
                y = y_next; 
             } while(  x_next  < x_stop ); 
             // need one more move toget to final spot.        
        }
        else   // Right Most and y above the circle center
        {
             flag = 1;     
             // x will increment
             x = d->xS;
             y = d->yS;
             sign = ( y < d->yC ? -1 : 1 );

             if (y < d->yC) sign = -1.0 ;
             do{
                x_next = x - g_xDelta;  
                // r2 = x2 + y2 ;
                y_next = sqrt( r2 - ( x_next )*( x_next )  ) * sign ;
                printf("m2 x,y %4.4f,%4.4f   x_next,y_next %4.4f,%4.4f\n",x,y,x_next,y_next);
                x = x_next;
                y = y_next; 
             } while(  x_next >  x_stop ); 
             // need one more move toget to final spot.        
 
        }
        if(flag == 0)
        {
           printf("%d:%s-%s  Error should not get here \n",__LINE__,__FILE__,__FUNCTION__);
        }
           
    }
    else // CW
    {
        if(( d->xS == x_min ) || ( d->yS > d->yC )) // left most and y above the circle center
        {
             flag = 1;
             // x will increment
      
             x = d->xS;
             y = d->yS;
             sign = ( y < d->yC ? -1 : 1 );
             do{
                x_next = x + g_xDelta;  
                // r2 = x2 + y2 ;
                y_next = sqrt( r2 - ( x_next )*( x_next )  ) * sign ;
                printf("m2 x,y %4.4f,%4.4f   x_next,y_next %4.4f,%4.4f\n",x,y,x_next,y_next);
                x = x_next;
                y = y_next; 
             } while(  x_next  < x_stop ); 
             // need one more move toget to final spot.        
        }
        else   // Right Most and y below the circle center
        {
             flag = 1;     
             // x will increment
             x = d->xS;
             y = d->yS;
             sign = ( y < d->yC ? -1 : 1 );

             if (y < d->yC) sign = -1.0 ;
             do{
                x_next = x - g_xDelta;  
                // r2 = x2 + y2 ;
                y_next = sqrt( r2 - ( x_next )*( x_next )  ) * sign ;
                printf("m3 x,y %4.4f,%4.4f   x_next,y_next %4.4f,%4.4f\n",x,y,x_next,y_next);
                x = x_next;
                y = y_next; 
             } while(  x_next >  x_stop ); 
             // need one more move toget to final spot.        
 
        }
        if(flag == 0)
        {
           printf("%d:%s-%s  Error should not get here \n",__LINE__,__FILE__,__FUNCTION__);
        }
           
    }

return 0;
}

#define  PT_GT_CENTER(p,c)        ((p - c) >= 0)
#define  PT_LT_CENTER(p,c)        ((p - c) < 0)
#define  PTS_GT__CENTER(s,f,c)   (((s - c) >= 0) && ((f -c) >= 0))  

/* 
                 3                           
              2  |  4                        
           1     |     5                 
       0 --------+------- 6                         
          11     |     7                   
             10  |  8
                 9   

                  {starting Point}            {Ending Point  }     What to do 
1)  If CCW && ( Sx > Fx ) && (Sy GT Center) && (Fy GT Center)
                  {      4       }      {   4-0        }  --1 St -end
2)  If CCW && ( Sx > Fx ) && (Sy GT Center) && (Fy LT Center)
                  {      4       }      {   0-8        }  --2 St Limit -end
3)  If CCW && ( Sx < Fx ) && (Sy GT Center) && (Fy GT Center)
                  {      4       }      {   6-4        }  --3 St limit limit -end
4)  If CCW && ( Sx < Fx ) && (Sy GT Center) && (Fy LT Center)
                  {      4       }      {   8- 6       }  --2 st limit -end 
 
5)  If CCW && ( Sx < Fx ) && (Sy LT Center) && (Fy LT Center)
                  {     10       }      {   10-6      }  --1 St -end
6)  If CCW && ( Sx < Fx ) && (Sy LT Center) && (Fy GT Center)
                  {     10       }      {   6-2       }  --2 St limit -end
7)  If CCW && ( Sx > Fx ) && (Sy LT Center) && (Fy GT Center)
                  {     10       }      {   2-0       }  --2 St limit -end
8)  If CCW && ( Sx > Fx ) && (Sy LT Center) && (Fy LT Center)
                  {     10       }      {   0-10      }  --3 st limit limit -end


9)  If CW && ( Sx < Fx ) && (Sy GT Center) && (Fy GT Center)
                  {      2       }      {   2-6       }  --1  st -end
10) If CW && ( Sx < Fx ) && (Sy GT Center) && (Fy LT Center)
                  {      2       }      {   6-10      }  --2  st limit -end
11) If CW && ( Sx > Fx ) && (Sy GT Center) && (Fy GT Center)
                  {      2       }      {   0-2       }  --3  st limit limit end
12) If CW && ( Sx > Fx ) && (Sy GT Center) && (Fy LT Center)
                  {      2       }      {   10-0      }  --2  st limit -end
 
13) If CW && ( Sx > Fx ) && (Sy LT Center) && (Fy LT Center)
                  {      8       }      {   8-0       }  --1 st -end
14) If CW && ( Sx > Fx ) && (Sy LT Center) && (Fy GT Center)
                  {      8       }      {   0-4       }  --2 st limit -end
15) If CW && ( Sx < Fx ) && (Sy LT Center) && (Fy GT Center)
                  {      8       }      {   4-6       }  --2 st limit -end 
16) If CW && ( Sx < Fx ) && (Sy LT Center) && (Fy LT Center)  
                  {      8       }      {   6-8       }  --3 St limit Limit end
 
 */



FILE * g_log = NULL;

int circle(CircleParms_t *d)
{
//   should we look at start and stop Quadrents?
    float r2;
    float r;
    float x_min;
    float x_max;
    float x;
    float x_next;
    float y;
    float y_next;
    float x_stop;
    float sign;
    int flag = 0;
    r2 = (d->xC - d->xS)*(d->xC - d->xS) + (d->yC - d->yS)*(d->yC - d->yS);
    r = sqrt (r2);
    x_min = d->xC - r ;
    x_max = d->xC + r ;
    x_stop = roundf(d->xF * 1000) / 1000;
    printf("Circle Radius  %4.4f\n",sqrt(r2));
    printf("        x_min  %4.4f\n",x_min);
    printf("        x_max  %4.4f\n",x_max);
    printf("        x_stop  %4.4f\n",x_stop);
     


    if(d->dir == 0) // CCW
    {
        if (( d->xS > d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {
          printf(" case 1:   --1  st  end \n"); 
        }
        if (( d->xS > d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {
          printf(" case 2:   --2  st  Limit (xmin)  end \n"); 
        }
        if (( d->xS < d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {
          printf(" case 3:   --3  st  Limit (xmin)  Limit(xmax)  end \n"); 
        }
        if (( d->xS < d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {
          printf(" case 4:   --2  st  Limit(xmin)  end \n"); 
        }


        if (( d->xS < d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 5:   --1  st  end \n"); 
        }
        if (( d->xS < d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {
          printf(" case 6:   --2  st  Limit(xmax) end \n"); 
        }
        if (( d->xS > d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {
          printf(" case 7:   --2  st  Limit(xmax)  end \n"); 
        }
        if (( d->xS > d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {
          printf(" case 8:   --3  st  Limit(xmax) Limit(xmin)  end \n"); 
        }
 
    }
    else
    {

        if (( d->xS < d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 9:   --1  st  end \n"); 
        }

        if (( d->xS < d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 10:   --2  st  Limit(xmax) end \n"); 
        }

        if (( d->xS > d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 11:   --3  st  Limit(xmax)  Limit(xmin)  end \n"); 
        }

        if (( d->xS > d->xF ) && (PT_GT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 12:   --2  st  Limit(xmax)  end \n"); 
        }
 
        if (( d->xS > d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 13:   --1  st  end \n"); 
        }

        if (( d->xS > d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 14:   --2  st  Limit(xmin) end \n"); 
        }

        if (( d->xS < d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_GT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 15:   --2  st  Limit(xmin) end \n"); 
        }

        if (( d->xS < d->xF ) && (PT_LT_CENTER(d->yS,d->yC)) && (PT_LT_CENTER(d->yF,d->yC)))
        {           
          printf(" case 16:   --3  st  Limit(xmin) Limit(xmax)  end \n"); 
        }
 

    }


return 0;
}


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


float g_xc = 2;              // current position x
float g_yc = 3.828427125;    // current position y
float g_CirclePoints = 10;   // number of points to create around the circle

#define PI  3.1415926535





// format 1
void arc_ij(float x, float y, float i, float j, float f)
{
float x_cntr;
float y_cntr;

float s_theta;  // start theta
float e_theta;  // end theta
float d_theta;  // end theta
float steps;
float r;

float dy,dx;
int   n;
float xc = g_xc;
float yc = g_yc;

steps = g_CirclePoints;
    
// for not assume relative i,j
   printf("[%d]%s:%s  i  %f\n",__LINE__,__FILE__,__FUNCTION__, i);
   printf("[%d]%s:%s  j  %f\n",__LINE__,__FILE__,__FUNCTION__, j);
   printf("[%d]%s:%s  x (end)  %f\n",__LINE__,__FILE__,__FUNCTION__, x);
   printf("[%d]%s:%s  y (end)  %f\n",__LINE__,__FILE__,__FUNCTION__, y);
 
   if(g_ArcCenter == INC_POSITIONING)
   {
       x_cntr = xc + i;
       y_cntr = yc + j;
   }
   else
   {
       x_cntr =  i;
       y_cntr =  j;
   }

   r  = sqrt( (x_cntr - x)* (x_cntr - x) + (y_cntr - y) * (y_cntr - y));

   printf(" xstart  %f\n", xc);
   printf(" ystart  %f\n", yc);
   printf(" xcenter  %f\n", x_cntr);
   printf(" ycenter  %f\n", y_cntr);
 
   // calculat the start angle
   dx = xc - x_cntr ;
   dy = yc - y_cntr ;
   printf(" dy  %f  dx   %f     dy/dx  %f\n",dy, dx, (dy/dx));
   if( (dy == 0) && (dx < 0))
   {
      s_theta = PI;
   }
   else
   {   
      s_theta = atan( dy/dx);
   }
   printf(" start_theta  %f rad   %f Deg\n", s_theta, s_theta*180/PI);

   // calculat the end angle
   dx = x - x_cntr ;
   dy = y - y_cntr ;
   printf(" xend    %f\n", x);
   printf(" yend    %f\n", y);
   printf(" xcenter  %f\n", x_cntr);
   printf(" ycenter  %f\n", y_cntr);
   printf(" dy  %f  dx   %f     dy/dx  %f\n",dy, dx, (dy/dx));
   if( (dy == 0) && (dx < 0))
   {
      e_theta = PI;
   }
   else
   {   
      e_theta = atan( dy/dx);
   }
 
   printf(" end_theta  %f rad   %f Deg\n", e_theta, e_theta*180/PI);
   // calculate the delta angle  
   d_theta = (e_theta - s_theta)/steps;

   printf(" radius  %f\n", r); 

   printf("         theta       cos(t)           x          sin(t)           y  \n");     
   printf("         ------------------------------------------------------------\n");     
   for(n = 0 ; n <= steps ; n++)
   {
      float theta,xt,yt;
      
      theta = d_theta * n + s_theta;
      xt = x_cntr + r * cos(theta);
      yt = y_cntr + r * sin(theta);
      
      printf("%2d)\t%f\t%f\t%f\t%f\t%f\n",n,theta, cos(theta),xt,sin(theta),yt);     


   }

   printf("[%d]%s:%s\n",__LINE__,__FILE__,__FUNCTION__);

}


// format2  - specify R 
// let h be the x center
// let y be the y center
// let x be a point on the circle
// Let y be a point on the circle
// Equation of a circle:     sqrt ( (x - h)(x-h) + (y-k)(y-k)) = r 


 
void arc_r(float x, float y, float r, float f)
{
float x_cntr;
float y_cntr;

float s_theta;  // start theta
float e_theta;  // end theta
float d_theta;  // end theta
float steps;
float r_local;

float dy,dx;
float mid_y,mid_x;

float slope , b;
int   n;
float A,B,C;
float h1,h2,k1,k2;

float xc = g_xc;
float yc = g_yc;
int MinorCircle = TRUE;

// for not assume  i,j
   printf("[%d]%s:%s  radius r  %f\n",__LINE__,__FILE__,__FUNCTION__, r);
   printf("[%d]%s:%s  start  x  %f\n",__LINE__,__FILE__,__FUNCTION__, xc);
   printf("[%d]%s:%s  start  y  %f\n",__LINE__,__FILE__,__FUNCTION__, yc);
   printf("[%d]%s:%s  end    x  %f\n",__LINE__,__FILE__,__FUNCTION__, x);
   printf("[%d]%s:%s  end    y  %f\n",__LINE__,__FILE__,__FUNCTION__, y);
 

 
   steps = g_CirclePoints;

//  find the center....  
//      The detail here is knowing the sign of the Radius
//      and the direction of cut ?????? 
   // validate Radius info  
   if (r == 0) return ;  // why have a radius of 0
   MinorCircle = r > 0 ? TRUE : FALSE ;


// make a chord between start P1 and end P2 on the cycle.
   dy = y - yc;    // y2 - y1
   dx = x - xc;    // x2 - x1

   mid_x = xc + dx/2;
   mid_y = yc + dy/2;

   slope = -1*dx/dy;    // reversed be cause we want slope of Perpendicular Bisector  
    
   b = mid_y - (slope * mid_x);

   printf(" dy   %f      dx  %f   \n",dy,dx);
   printf(" mid_y   %f     mid_x  %f   \n",mid_y,mid_x);
   printf(" slope   %f      b  %f   \n",slope,b);
   //  k  = slope * h + b

   // so now we have the equation of a line which is the perpendicular bisector of
   //   the chord between the two points. 

   // and we know that  (x-h)(x-h)+(y-k)(y-k) = r*r
   //                   xx -2xh + hh + yy -2yk + kk = rr
  
   // substitute  (y= mx + b) for center point of the circle so  k = sh+b
   //
   //          xx -2xh + hh + yy -2y(sh+b)   + (sh+b)*(sh+b) = rr         
   //          xx -2xh + hh + yy -2ysh -2yb  +  sshh + 2bsh + bb = rr
   //  put in form of quadratic
   //         hh (1+ss) + h (-2x -2ys+2sb) + (xx + yy -2yb +bb -rr) =0       

   // (-B +/- Sqrt(BB -4AC))/2A

   //Calculate A, B, and C based on 
   A = 1 + slope*slope;
   B = (-2*x) + (-2*y*slope) + (2 *slope *b);
   C = x*x + (y*y) - (2*y*b) + (b * b) - (r * r);

   printf(" A  %f      B  %f    C %f\n",A,B,C);

   h1 = ((-1*B) + sqrt ( B * B - 4 *A*C))/ (2 * A);
   h2 = ((-1*B) - sqrt ( B * B - 4 *A*C))/ (2 * A);
   k1 = h1*slope +b;   
   k2 = h2*slope +b;   

   printf(" h1  %f      k1  %f    \n",h1,k1);
   printf(" h2  %f      k2  %f    \n",h2,k2);

   arc_ij(x, y, h2, k2, 1);

#if 0

   x_cntr = xc + i;
   y_cntr = yc + j;

   r = sqrt( (i * i) + (j * j));

   printf(" xstart  %f\n", xc);
   printf(" ystart  %f\n", yc);
   printf(" xcenter  %f\n", x_cntr);
   printf(" ycenter  %f\n", y_cntr);
 
   // calculat the start angle
   dx = xc - x_cntr ;
   dy = yc - y_cntr ;
   printf(" dy  %f  dx   %f     dy/dx  %f\n",dy, dx, (dy/dx));
   if( (dy == 0) && (dx < 0))
   {
      s_theta = PI;
   }
   else
   {   
      s_theta = atan( dy/dx);
   }
   printf(" s_theta  %f rad   %f Deg\n", s_theta, s_theta*180/PI);

   // calculat the end angle
   dx = x - x_cntr ;
   dy = y - y_cntr ;
   printf(" xend    %f\n", x);
   printf(" yend    %f\n", y);
   printf(" xcenter  %f\n", x_cntr);
   printf(" ycenter  %f\n", y_cntr);
   printf(" dy  %f  dx   %f     dy/dx  %f\n",dy, dx, (dy/dx));
   if( (dy == 0) && (dx < 0))
   {
      e_theta = PI;
   }
   else
   {   
      e_theta = atan( dy/dx);
   }
 
   // calculate the delta angle  
   d_theta = (e_theta - s_theta)/steps;

   printf(" radius  %f\n", r); 

   printf(" theta   cos(t)    x   sin(t)     y  \n");     
   for(n = 0 ; n <= steps ; n++)
   {
      float theta,xt,yt;
      
      theta = d_theta * n + s_theta;
      xt = x_cntr + r * cos(theta);
      yt = y_cntr + r * sin(theta);
      
      printf("%2d)\t%f\t%f\t%f\t%f\t%f\n",n,theta, cos(theta),xt,sin(theta),yt);     


   }
#endif


}
