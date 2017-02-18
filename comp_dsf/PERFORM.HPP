#ifndef __PREFORM_HPP__
#define __PREFORM_HPP__


#include "..\mainsys.h"
#include "grfile.hpp"

class perform
{
 private:
   float delt,Time,CurTime;

   Boolean pnt,act;
   grfile  GRF;

 public:
   inline perform(NOARG)  { act=FALSE; }
  ~perform(NOARG);

   double DoStep(double val);    \\ calculate one step
   RetVal DoModel(NOARG);        \\ calculate all & save .GRF file
   RetVal ClearModel(NOARG);     \\ reset all to default values

   RetVal SetParam(float delt,float Time);  // model parameters
   RetVal SetPoint(PntLstP pnt);            // list of points to store
   RetVal SetGraph(char *name);             // file to store data
   RetVal SetModel(MdlLstP model);          // model

   inline VOID PointOn(NOARG)  { pnt=TRUE;  }
   inline VOID PointOff(NOARG) { pnt=FALSE; }
   inline IsStore(NOARG)       { return (pnt==TRUE) ? 1 : 0; }
};

#endif
