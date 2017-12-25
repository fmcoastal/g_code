#include <stdint.h>
#include "g_code.h" 


// G90 sets position to Absolute.
//      X,Y,and Z define the end point of the move in the user coordinate system 
// G91 set position to Incremental
//      X,Y,and Z define the distance and direction to move from the current Postition.
int  g_AbsoluteOrRelative = ABS_POSITIONING;

// G90.1 sets ArcCenter to Absolute.
//      IF arc center mode is set to Incremental then, I,J,K are 
//      the distance and Direction from the start point to the center point fo the ARC.  
// G91.1 set ArcCenter to Incremental
//      If arc center mode is set to absolute, then I,J,K are 
//       the absolute center point in the current user coordinate system. 
//#define ABS_POSITIONING 1
int  g_ArcCenter  = ABS_POSITIONING;


// G02 Clockwise Cutter direction.
// G03 Counter-CLockWise Cutter Direction.
int  g_CutDirection  = CW;


void G02(void) { g_CutDirection = CW;}
void G03(void) { g_CutDirection = CCW;}


void G90(void) { g_AbsoluteOrRelative = ABS_POSITIONING;}
void G91(void) { g_AbsoluteOrRelative = INC_POSITIONING;}

void G90_1(void) { g_ArcCenter = ABS_POSITIONING;}
void G91_1(void) { g_ArcCenter = INC_POSITIONING;}












