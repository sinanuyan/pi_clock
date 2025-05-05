/*
 * gw.h
 *
 *  Created on: Feb 27, 2024
 *      Author: sinan
 */

#ifndef INC_CRITICAL_SECTION_H_
#define INC_CRITICAL_SECTION_H_


#define CS1_CriticalVariable() \
  uint8_t cpuSR; /* variable to store current status */

/*
** ===================================================================
**     Method      :  CS1_CriticalVariable (component CriticalSection)
**     Description :
**         Defines a variable if necessary. This is a macro.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define CS1_EnterCritical() \
  do {                                  \
    asm (                               \
    "MRS   R0, PRIMASK\n\t"             \
    "CPSID I\n\t"                       \
    "STRB R0, %[output]"                \
    : [output] "=m" (cpuSR) :: "r0");   \
  } while(0)

/*
** ===================================================================
**     Method      :  CS1_EnterCritical (component CriticalSection)
**     Description :
**         Enters a critical section
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define CS1_ExitCritical() \
  do{                                  \
    asm (                              \
    "ldrb r0, %[input]\n\t"            \
    "msr PRIMASK,r0;\n\t"              \
    ::[input] "m" (cpuSR) : "r0");     \
  } while(0)

/*
** ===================================================================
**     Method      :  CS1_ExitCritical (component CriticalSection)
**     Description :
**         Exits a critical section
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/



#endif /* INC_CRITICAL_SECTION_H_ */
