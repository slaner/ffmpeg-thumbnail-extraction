#ifndef _CORE_DEFINED_
#define _CORE_DEFINED_

/**
 * Library References
 **/
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")


/**
 * ffmpeg Header
 **/
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

/**
 * Common Header
 **/
#include <stdio.h>
#include <conio.h>

/**
 * User Defined Header
 **/
#include "macro.h"
#include "media.h"

#endif