#pragma once
/*----------------------------------------------------------------------------------*/
#ifndef CPP_DEF_DEBUG_H
#define CPP_DEF_DEBUG_H
/*-----------------------------------------*/
#ifndef ASSERT
#include <assert.h>
#define  ASSERT(Exp) assert(Exp)
#endif
/*-----------------------------------------*/
#ifndef TRACE_FUNC_ARGS
#define TRACE_FUNC_ARGS(fmt,...)  printf("%s(%d)-<%s>: "##fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__) 
#endif // 
/*-----------------------------------------*/
#ifndef TRACE_FUNC
#define TRACE_FUNC()  printf("\n>>>>>>CALL FUNC : %s(%d)\n", __FUNCTION__,__LINE__) 
#endif // 
/*-----------------------------------------*/
#if __GUNC__||linux||__linux||__linux__

#ifndef  TRACE
#define TRACE(FMT,ARGS...) {fprintf(stderr,"%s\t%s\t%d\t%s\n",__FILE__,__FUNCTION__,__LINE__,__TIME__);fprintf(stderr,FMT,##ARGS);}
#endif

#ifndef ASSERT
#include <assert.h>
#define  ASSERT(Exp) assert(Exp)
#endif

#endif
/*-----------------------------------------*/
#endif









