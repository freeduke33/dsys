#ifndef __dsys_II_
#define __dsys_II_

#include "signal.h"
#include "tcxldef.h"

#include "mainsys.h"

#ifdef __cplusplus
extern "C" {
#endif

void ExitError(const char *msg, ...);
extern TrigType trigger;
extern ParamT  ParBuf;      // для ввода новых параметров звеньев
extern EasyGenT GenBuf[];   // для ввода новых параметров генераторов
extern GenT     UseGen;

#ifdef __cplusplus
  }
#endif


#endif
