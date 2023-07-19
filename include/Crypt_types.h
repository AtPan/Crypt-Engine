/*  This file is part of Crypt Engine.
 *
 *  Crypt Engine is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *
 *  Crypt Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with Crypt Engine.
 *  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Copyright 2023 Anthony Panarello
 */

#ifndef __CRYPT_TYPES_H
#define __CRYPT_TYPES_H

// --------------------------------
/* Enumerated Types */

/* This type is meant to pass signals between functions.
 * The two most common flags are FAIL and SUCCESS.
 */
typedef enum {
    FAIL,
    SUCCESS,
} flag_t;

/* This type is meant to tell the logger the severity of a message.
 */
typedef enum {
    LOG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
} log_level_t;

/* This type is meant to act as a basic boolean type.
 */
typedef enum {
    FALSE = 0,
    TRUE = 1,
} bool_t;

typedef struct __vector2_t {
    double x;
    double y;
} vector2_t;

typedef struct __vector3_t {
    double x;
    double y;
    double z;
} vector3_t;

/* End of Enumerated Types */
// ----------------------------

#endif
