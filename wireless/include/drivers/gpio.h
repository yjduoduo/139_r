#ifndef GPIO_H
#define GPIO_H

#include "includeall.h"


#ifdef EXTERN_GPIO
#define EXT_GPIO
#else
#define EXT_GPIO extern
#endif


EXT_GPIO void gpio_init(void);


#endif // GPIO_H
