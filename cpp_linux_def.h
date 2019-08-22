#ifndef CPP_LINUX_DEF_H
#define CPP_LINUX_DEF_H
/*---------------------------------------------------------------------*/
#if linux||__linux||__linux__||__GNUC__

#ifndef nullptr
#define nullptr 0
#endif

#ifndef memcpy_s
#define memcpy_s(D,Ds,S,Ss)  {memcpy(D,S,Ss);}
#endif

#ifndef  strcpy_s
#define strcpy_s(D,SizeBuff,S)  strncpy(D,S,SizeBuff)
#endif

#ifndef _MAX_FNAME
#define _MAX_FNAME  1024
#endif

#ifndef  XXXXXXXXXXXX
#define  XXXXXXXXXXXX  11111
#endif

#ifndef sprintf_s
#define sprintf_s  snprintf
#endif

#endif
/*---------------------------------------------------------------------*/
#endif









