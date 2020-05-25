#ifndef CONFIG_ALL_H
#define CONFIG_ALL_H

#include "config_shared_array.h"

#if !defined(__x86_64) && !defined(_M_X64) && !defined(__i386) && !defined(_M_IX86)

#define NO_UNALIGNED_ACCESS 1

#endif

#endif
