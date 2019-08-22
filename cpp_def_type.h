#ifndef _CPP_DEF_TYPE_H_
#define _CPP_DEF_TYPE_H_
/*-----------------------------------------*/
#ifndef DWORD
typedef unsigned long       DWORD;
#endif
/*-----------------------------------------*/
#ifndef BOOL
typedef int                 BOOL;
#endif
/*-----------------------------------------*/
#ifndef BYTE
typedef unsigned char       BYTE;
#endif
/*-----------------------------------------*/
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------*/
#ifndef BOOL
typedef int BOOL;
#endif
/*-----------------------------------------*/
#ifndef INT32
typedef signed int INT32;
#endif
/*-----------------------------------------*/
#ifndef LONGLONG
typedef long long LONGLONG;
#endif
/*-----------------------------------------*/
#ifndef ULONGLONG
typedef unsigned long long ULONGLONG;
#endif
/*-----------------------------------------*/
#ifndef PVOID
typedef void *PVOID;
#endif
/*-----------------------------------------*/
#ifndef HANDLE
typedef PVOID HANDLE;
#endif
/*-----------------------------------------*/
#ifndef UINT
typedef unsigned int UINT;
#endif // !UINT
/*-----------------------------------------*/
#ifndef PUINT
typedef unsigned int        *PUINT;
#endif // !1
/*-----------------------------------------*/
#ifndef boolean
typedef unsigned char boolean;
#endif // !boolean
/*-----------------------------------------*/
#ifndef LPVOID

#if __GNUC__
#define LPVOID  void *
#endif

#endif
/*-----------------------------------------*/
#endif









