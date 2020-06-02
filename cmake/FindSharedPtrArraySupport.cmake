# Ceres Solver - A fast non-linear least squares minimizer
# Copyright 2015 Google Inc. All rights reserved.
# http://ceres-solver.org/
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# * Neither the name of Google Inc. nor the names of its contributors may be
#   used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Author: sergey.vfx@gmail.com (Sergey Sharybin)
#
# FindSharedPtrArraySuport.cmake - Determine support to array types in shared pointer.
#
# This module defines the following variables:
#
# SHARED_PTR_ARRAY_SUPPORT_FOUND: TRUE if some kind of support is found.
macro(FIND_SHARED_PTR_ARRAY_SUPPORT)
  message(STATUS "Checking for shared ptr array support.")
  unset(HAVE_STD_SHARED_PTR_CUSTOM_DELETER)
  unset(HAVE_STD_SHARED_PTR_ARRAYS)
  unset(HAVE_STD_MAKE_SHARED_ARRAYS)
  set(SHARED_PTR_ARRAY_SUPPORT_FOUND FALSE)
  check_include_file_cxx(memory HAVE_STD_MEMORY_HEADER)
  if (HAVE_STD_MEMORY_HEADER)
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("#include <memory>
                               int main() {
                                 std::shared_ptr<int> ptr(new int[10], std::default_delete<int[]>());
                                 return 0;
                               }"
            HAVE_STD_SHARED_PTR_CUSTOM_DELETER)

    if (HAVE_STD_SHARED_PTR_CUSTOM_DELETER)
      message(STATUS "Found support to std::shared_ptr<T>::shared_ptr(T*, Deleter).")
      set(SHARED_PTR_ARRAY_SUPPORT_FOUND TRUE)
    endif (HAVE_STD_SHARED_PTR_CUSTOM_DELETER)

    check_cxx_source_compiles("#include <memory>
                               int main() {
                                 std::shared_ptr<int[]> ptr(new int[10]);
                                 return 0;
                               }"
            HAVE_STD_SHARED_PTR_ARRAYS)

    if (HAVE_STD_SHARED_PTR_ARRAYS)
      message(STATUS "Found support to std::shared_ptr<T[]>::shared_ptr(T[]).")
      set(SHARED_PTR_ARRAY_SUPPORT_FOUND TRUE)
    endif (HAVE_STD_SHARED_PTR_ARRAYS)

    check_cxx_source_compiles("#include <memory>
                               int main() {
                                 std::shared_ptr<T[]> sh_array = std::make_shared<T[]>(std::size_t);
                                 return 0;
                               }"
            HAVE_STD_MAKE_SHARED_ARRAYS)

    if (HAVE_STD_MAKE_SHARED_ARRAYS)
      message(STATUS "Found support to std::shared_ptr<T[]> std::make_shared<T[]>(std::size_t)")
      set(SHARED_PTR_ARRAY_SUPPORT_FOUND TRUE)
    endif (HAVE_STD_MAKE_SHARED_ARRAYS)

  endif (HAVE_STD_MEMORY_HEADER)
endmacro(FIND_SHARED_PTR_ARRAY_SUPPORT)
