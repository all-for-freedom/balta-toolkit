#ifndef __BTMULINK_TYPES_H__
#define __BTMULINK_TYPES_H__

#ifndef REAL64_T
#define REAL64_T double
#endif
#ifdef REAL64_T
typedef REAL64_T real64_T;
#endif

#ifndef REAL_T
#ifdef REAL64_T
#define REAL_T real64_T
#endif
#endif
#ifdef REAL_T
typedef REAL_T real_T;
#endif

#ifndef TIME_T
#ifdef REAL_T
#define TIME_T real_T
#endif
#endif
#ifdef TIME_T
typedef TIME_T time_T;
#endif

#ifndef INTEGER_T
# define INTEGER_T int
#endif
typedef INTEGER_T int_T;

#ifndef CHARACTER_T
#define CHARACTER_T char
#endif
typedef CHARACTER_T char_T;

#endif