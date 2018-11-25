#ifndef _MACRO_DEFINED_
#define _MACRO_DEFINED_

#include "core.h"

/**
 * Logging
 **/
// Log message to standard error
#define ERROR(format, ...) fprintf(stderr, format, ##__VA_ARGS__);
#define LOG(format, ...) fprintf(stdout, format, ##__VA_ARGS__);

/**
 * .NET Style
 **/
typedef char Char;
typedef unsigned char Byte;
typedef short Int16;
typedef int Int32;
typedef long long Int64;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;
typedef float Single;
typedef double Double;

/**
 * Windows Style
 **/
#define TRUE 1
#define FALSE 0
typedef int BOOL;

/**
 * Useful macro
 **/
#define Q2D(x) (Double) x.num / x.den
#define ERRDESCRIPTION(x) \
	char __description[260]; \
	memset(__description, 0, sizeof(__description)); \
	av_make_error_string(__description, sizeof(__description), x);

#endif