#ifndef INIT_H
#define INIT_H
#include "includeall.h"


#ifdef EXTERN_INIT
#define EXT_INIT
#else
#define EXT_INIT extern
#endif



EXT_INIT void hardware_init(void);


#endif // INIT_H
