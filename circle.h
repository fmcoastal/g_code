#ifndef _circle_h
#define _circle_h 

#define DIR_CCW 0
#define DIR_CW  1


typedef struct circleparms_struct{
      float xS;     // x start
      float yS;     // y start
      float xF;     // x final
      float yF;     // y final
      float xC;     // x Center
      float yC;     // y Center
      int   dir;  //  1=CCW  0 = CW
} CircleParms_t;

extern int  g_test_cnt;
extern CircleParms_t g_test[];
 

void PrintCircleParms(CircleParms_t * d, char * string);

// cos 30 = .8660
// sin 30 = .5


extern FILE * g_log;

int circle(CircleParms_t *d);



/*
 *  Parameters
 *
 *  x - end x position
 *  y - end y position
 *  i - Either Center of Circle X ( = 0 ) or Deltx to center from current position x ( = 1)
 *  j - 
 *  f - Feed rate, but 
 */
extern void arc_ij(float x, float y, float i, float j, float f);


extern void arc_r(float x, float y, float r, float f);

#endif



