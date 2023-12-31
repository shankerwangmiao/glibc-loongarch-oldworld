/* Copyright (C) 2005-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Ho hum, since fxstatat == fxstatat64 we must get rid of the
   prototype or gcc will complain since they don't strictly match.  */
#define __fxstatat64 __fxstatat64_disable

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <sysdep.h>
#include <sys/syscall.h>

#include <xstatconv.h>
#include <statx_cp.h>

/* Get information about the file NAME relative to FD in ST.  */
int
__fxstatat (int vers, int fd, const char *file, struct stat *st, int flag)
{
  if (vers != _STAT_VER_KERNEL && vers != _STAT_VER_LINUX)
    {
      __set_errno (EINVAL);
      return -1;
    }
  struct stat64 kst64;
  struct statx tmp;

  INTERNAL_SYSCALL_DECL (err);
  unsigned long sys_result
      = INTERNAL_SYSCALL (statx, err, 5, fd, file, AT_NO_AUTOMOUNT | flag,
                          STATX_BASIC_STATS, &tmp);
  if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (sys_result, err), 0))
    {
      if (INTERNAL_SYSCALL_ERRNO (sys_result, err) == ENOSYS)
        {
          return INLINE_SYSCALL (newfstatat, 4, fd, file, st, flag);
        }
      else
        {
          __set_errno (INTERNAL_SYSCALL_ERRNO (sys_result, err));
          return -1;
        }
    }

  __cp_stat64_statx (&kst64, &tmp);
  return __xstat32_conv (vers, &kst64, st);
}
libc_hidden_def (__fxstatat)
#undef __fxstatat64
strong_alias (__fxstatat, __fxstatat64);
strong_alias (__fxstatat64, __GI___fxstatat64)
