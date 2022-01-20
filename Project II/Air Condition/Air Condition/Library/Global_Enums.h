/*
 * Global_Enums.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Ahmed Hassan
 */

#ifndef GLOBAL_ENUMS_H_
#define GLOBAL_ENUMS_H_


#define ENABLE    1
#define DISABLE   0


#define NULL_PTR ((void *)0)
//#define NULL     NULL_PTR

#define ERROR_OK	0
#define ERROR_NOK   1

/* Boolean Values */

#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

#define STD_HIGH    (1u)   	  /* Standard HIGH */
#define STD_LOW     (0u)	  /* Standard LOW */

#define E_OK        (0u)      /* Function Return OK */
#define E_NOT_OK    (1u)      /* Function Return NOT OK */

//#define NULL_PTR    ((void*)0)


#endif /* GLOBAL_ENUMS_H_ */
