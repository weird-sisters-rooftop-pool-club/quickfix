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

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#include "stdafx.h"
#else
#include "config.h"
#endif

#include <gtest/gtest.h>
#include "SharedArrayAdapter.h"

using namespace FIX;

#ifdef HAVE_STD_MAKE_SHARED_ARRAYS
TEST(SharedArrayAdapterTests, SharedArrayAdapterStdMakeSharedArraysEqualsOperator_SharedArraySetEqualToItself)
{
  using shared_array = shared_array_adapter_helper<make_shared_array_strategy>::type<std::string>;
  shared_array shared;
  shared_array * pShared = &shared;

  shared = *pShared;

  ASSERT_EQ(*pShared, shared);
}
#endif

#ifdef HAVE_STD_MAKE_SHARED_ARRAYS
TEST(SharedArrayAdapterTests, CreateSharedArrayAdapterStdMakeSharedArrays_SizeZeroArray)
{
  using shared_array = shared_array_adapter_helper<make_shared_array_strategy>::type<std::string>;
  shared_array shared = shared_array::create(0);

  ASSERT_EQ(0, (int) shared.size());
}
#endif

#ifdef HAVE_STD_SHARED_PTR_ARRAYS
TEST(SharedArrayAdapterTests, SharedArrayAdapterStdSharedPtrArraysEqualsOperator_SharedArraySetEqualToItself)
{
  using shared_array = shared_array_adapter_helper<shared_ptr_array_strategy>::type<std::string>;
  shared_array shared;
  shared_array * pShared = &shared;

  shared = *pShared;

  ASSERT_EQ(*pShared, shared);
}
#endif

#ifdef HAVE_STD_SHARED_PTR_ARRAYS
TEST(SharedArrayAdapterTests, CreateSharedArrayAdapterStdSharedPtrArrays_SizeZeroArray)
{
  using shared_array = shared_array_adapter_helper<shared_ptr_array_strategy>::type<std::string>;
  shared_array shared = shared_array::create(0);

  ASSERT_EQ(0, (int) shared.size());
}
#endif

#ifdef HAVE_STD_SHARED_PTR_CUSTOM_DELETER
TEST(SharedArrayAdapterTests, SharedArrayAdapterStdSharedPtrCustomDeleterEqualsOperator_SharedArraySetEqualToItself)
{
  using shared_array = shared_array_adapter_helper<shared_ptr_custom_deleter>::type<std::string>;
  shared_array shared;
  shared_array * pShared = &shared;

  shared = *pShared;

  ASSERT_EQ(*pShared, shared);
}
#endif

#ifdef HAVE_STD_SHARED_PTR_CUSTOM_DELETER
TEST(SharedArrayAdapterTests, CreateSharedArrayAdapterStdSharedPtrCustomDeleter_SizeZeroArray)
{
  using shared_array = shared_array_adapter_helper<shared_ptr_custom_deleter>::type<std::string>;
  shared_array shared = shared_array::create(0);

  ASSERT_EQ(0, (int) shared.size());
}
#endif
