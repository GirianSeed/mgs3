#include "common.h"

/*!
 *  @brief      2nd-generation string-hashing function.
 *              Originally from "METAL GEAR SOLID 2" (2001).
 *
 *  Given that the digest is only 24 bits wide, this algorithm is rather
 *  prone to collisions. Check for collisions after precalculating a set
 *  of hashes intended for use at runtime. (e.g. stage data files)
 *
 *  @li Passing an empty string will return 1.
 *  @li Passing a single-char string will return the value of the char.
 *  @li Mutations of strings differing in only the last character will
 *      result in the lowest byte of the hash mirroring that difference.
 *  @li Mutations of strings differing by one or several characters often
 *      result in only small differences between returned values.
 *
 *  Input/Output Examples:
 *
 *  @li GV_StrCode("sna_mugen_bdn1") returns @c 0x0028021E
 *  @li GV_StrCode("sna_mugen_bdn2") returns @c 0x0028021F
 *  @li GV_StrCode("cbx_a_alp_ovl") returns @c 0x007BBF37
 *  @li GV_StrCode("cbx_b_alp_ovl") returns @c 0x007CBF37
 *
 *  @param      string      NULL-terminated string.
 *
 *  @retval      1          if @p string is empty.
 *  @retval     >1          24-bit hash of @p string.
 */
int GV_StrCode( const char *string )
{
    unsigned char c;
    unsigned char *p = (unsigned char *)string;
    unsigned int id = 0, mask = 0x00ffffff;

    while (( c = *p++ )) {
        id = ((id << 5) | (id >> 19));
        id += c;
        id &= mask;
    }
    if (id == 0) id = 1;

    return id;
}
