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

#ifndef __CRYPT_LOG_H
#error "Do not include directly; include <Crypt_log.h> instead"
#endif

#ifndef __CRYPT_INTERNAL_LOG_H
#define __CRYPT_INTERNAL_LOG_H

#include <stdio.h>
#include "Crypt.h"

struct __Crypt_log_t {
    FILE * fh;
    const char * name;
};

#endif
