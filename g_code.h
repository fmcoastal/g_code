#ifndef _g_code_h
#define _g_code_h


#define INC_POSITIONING 0 
#define ABS_POSITIONING 1

// G90 sets position to Absolute.
//      X,Y,and Z define the end point of the move in the user coordinate system 
// G91 set position to Incremental
//      X,Y,and Z define the distance and direction to move from the current Postition.
extern int  g_AbsoluteOrRelative;  ;

// G90.1 sets ArcCenter to Absolute.
//      IF arc center mode is set to Incremental then, I,J,K are 
//      the distance and Direction from the start point to the center point fo the ARC.  
// G91.1 set ArcCenter to Incremental
//      If arc center mode is set to absolute, then I,J,K are 
//       the absolute center point in the current user coordinate system. 
//#define ABS_POSITIONING 1
extern int  g_ArcCenter;


#define CW  1
#define CCW 0 
// G02 Clockwise Cutter direction.
// G03 Counter-CLockWise Cutter Direction.
extern int  g_CutDirection;
















#endif
