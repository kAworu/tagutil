#ifndef T_TOOLKIT_H
#define T_TOOLKIT_H
/*
 * t_toolkit.h
 *
 * handy functions toolkit for tagutil.
 *
 */

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "t_config.h"


/* compute the length of a fixed size array */
#define NELEM(ary) (sizeof(ary) / sizeof((ary)[0]))

/* some handy macros */
#define	ABANDON_SHIP() abort()


/*
 * upperize a given string.
 */
char	*t_strtoupper(char *str);

/*
 * lowerize a given string.
 */
char	*t_strtolower(char *str);

/*
 * convert string from UTF-8 to the locale charset.
 *
 * @param src
 *   The string to convert encoded in UTF-8. If NULL, NULL is returned.
 *
 * @return
 *   A C-string encoded in the locale charset or NULL on error.
 */
char	*t_iconv_utf8_to_loc(const char *src);

/*
 * convert string from the locale charset to UTF-8.
 *
 * @param src
 *   The string to convert encoded in the locale charset. If NULL, NULL is
 *   returned.
 *
 * @return
 *   A C-string encoded in UTF-8 or NULL on error.
 */
char	*t_iconv_loc_to_utf8(const char *src);

/*
 * dirname() routine that does not modify its argument.
 */
char	*t_dirname(const char *);
/*
 * basename() routine that does not modify its argument.
 */
char	*t_basename(const char *);

/* XXX: to avoid -Werror=return-type */
void	 xasprintf(char **strp, const char *fmt, ...);
#endif /* ndef T_TOOLKIT_H */
