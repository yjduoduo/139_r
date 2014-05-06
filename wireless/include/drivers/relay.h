#ifndef RELAY_H
#define RELAY_H
#include "includeall.h"


#ifdef EXTERN_RELAY
#define EXT_RELAY
#else
#define EXT_RELAY extern
#endif

EXT_RELAY void Relay_Init(void);
EXT_RELAY void Fire_Relay_On(void);
EXT_RELAY void Fire_Relay_Off(void);
EXT_RELAY void Fault_Relay_On(void);
EXT_RELAY void Fault_Relay_Off(void);




#endif // RELAY_H
