#ifndef CPP_DEF_H
#define CPP_DEF_H
/*-----------------------------------------*/
#include <cpp_def_type.h>
/*-----------------------------------------*/
#include <cpp_linux_def.h>
/*-----------------------------------------*/
#ifndef  C_STD_LIB_ASSERT
#include <assert.h>
#define  C_STD_LIB_ASSERT(Exp) assert(Exp)
#endif
/*-----------------------------------------*/
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
/*-----------------------------------------*/
#ifndef TRUE
#define TRUE 1
#endif
/*-----------------------------------------*/
#ifndef FALSE
#define FALSE 0
#endif
/*-----------------------------------------*/
#ifndef TimeCountClockTest
#define TimeCountClockTest

#define TimeCountStart()	double dur=0;clock_t start,end;start = clock();

#define TimeCountStop(MESSAGE_TIME_END)		end = clock();dur = (double)(end - start);printf("%s(S):%0.3f\n",MESSAGE_TIME_END,(dur/CLOCKS_PER_SEC));


#endif
/*-----------------------------------------*/
#endif









