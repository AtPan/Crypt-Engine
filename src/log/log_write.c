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

#include <Crypt_log.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

extern FILE * __log_file;

void Crypt_log_write(const char * restrict fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const time_t ti = time(NULL);
    struct tm * t = gmtime(&ti);

    fprintf(__log_file, "[%d-%02d-%02d %02d:%02d:%02d UTC]: ",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    vfprintf(__log_file, fmt, args);
    fflush(__log_file);

    va_end(args);
}
