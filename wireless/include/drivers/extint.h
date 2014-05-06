#ifndef EXTINT_H
#define EXTINT_H

#include "includeall.h"


#ifdef EXTERN_EXTINT
#define EXT_EXTINT
#else
#define EXT_EXTINT extern
#endif


EXT_EXTINT void extint3_init(void);
EXT_EXTINT void extint1_init(void);


#endif // EXTINT_H
