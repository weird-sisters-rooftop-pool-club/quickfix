/* -*- C++ -*- */

/****************************************************************************
** Copyright (c) 2001-2014
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifndef CONFIG_SHARED_ARRAY_H
#define CONFIG_SHARED_ARRAY_H

#if defined(__cplusplus) &&  __cplusplus >= 201103L
#   define HAVE_CXX_11
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#   define HAVE_CXX_11
#endif

#ifndef HAVE_CXX_11
#   define SharedArray FIX::shared_array
#   include "AtomicCount.h"
#elif HAVE_STD_MAKE_SHARED_ARRAYS
#   define SharedArray FIX::shared_array_adapter_helper<make_shared_array_strategy>::type
#   include "SharedArrayAdapter.h"
#elif HAVE_STD_SHARED_PTR_ARRAYS
#   define SharedArray FIX::shared_array_adapter_helper<shared_ptr_array_strategy>::type
#   include "SharedArrayAdapter.h"
#elif HAVE_STD_SHARED_PTR_CUSTOM_DELETER
#   define SharedArray FIX::shared_array_adapter_helper<shared_ptr_custom_deleter>::type
#   include "SharedArrayAdapter.h"
#else
#   define SharedArray FIX::shared_array
#   include "AtomicCount.h"
#endif

#endif // CONFIG_SHARED_ARRAY_H
