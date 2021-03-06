/*
    $Id: mjpeg_types.h,v 1.7 2006-04-29 19:18:11 achurch Exp $

    Copyright (C) 2000 Herbert Valerio Riedel <hvr@gnu.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __MJPEG_TYPES_H__
#define __MJPEG_TYPES_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_ASM_MMX
# ifdef emms
#  undef emms
# endif
# define    emms() __asm__ __volatile__ ("emms")
#else
# define emms() do {} while(0)
#endif


#include <stdint.h>
#include <sys/types.h>

#if defined(HAVE_STDBOOL_H) && !defined(__cplusplus)
#include <stdbool.h>
#else
/* ISO/IEC 9899:1999 <stdbool.h> missing -- enabling workaround */

# ifndef __cplusplus
typedef enum
  {
    false = 0,
    true = 1
  } locBool;

#  define false   false
#  define true    true
#  define bool locBool
# endif
#endif

#ifndef PRId64
#define PRId64 PRID64_STRING_FORMAT
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#define GNUC_PRINTF( format_idx, arg_idx )    \
  __attribute__((format (printf, format_idx, arg_idx)))
#define GNUC_SCANF( format_idx, arg_idx )     \
  __attribute__((format (scanf, format_idx, arg_idx)))
#define GNUC_FORMAT( arg_idx )                \
  __attribute__((format_arg (arg_idx)))
#define GNUC_NORETURN                         \
  __attribute__((noreturn))
#define GNUC_CONST                            \
  __attribute__((const))
#define GNUC_UNUSED                           \
  __attribute__((unused))
#define GNUC_PACKED                           \
  __attribute__((packed))
#else   /* !__GNUC__ */
#define GNUC_PRINTF( format_idx, arg_idx )
#define GNUC_SCANF( format_idx, arg_idx )
#define GNUC_FORMAT( arg_idx )
#define GNUC_NORETURN
#define GNUC_CONST
#define GNUC_UNUSED
#define GNUC_PACKED
#endif  /* !__GNUC__ */


#endif /* __MJPEG_TYPES_H__ */


/*
 * Local variables:
 *  c-file-style: "gnu"
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
