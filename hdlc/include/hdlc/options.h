/*
* @Author: Lukasz
* @Date:   20-11-2018
* @Last Modified by:   Lukasz
* @Last Modified time: 20-11-2018
*/

#pragma once

#ifdef __unix__
#define HDLC_USE_STREAM_HELPER 1
#define HDLC_USE_RANDOM 1
#else
#define HDLC_USE_STREAM_HELPER 0
#define HDLC_USE_RANDOM 0
#endif