/*  This file is part of Crypt Engine.
 *
 *  Crypt Engine is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 *  Crypt Engine is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 *  You should have received a copy of the GNU General Public License along with
 * Crypt Engine. If not, see <https://www.gnu.org/licenses/>.
 *
 *  Copyright 2023 Anthony Panarello
 */

#include <Crypt.h>
#include <Crypt_log.h>
#include <Crypt_utils/internal_log.h>
#include <stdio.h>
#include <time.h>

flag_t Crypt_log_init(cryptlog_t * cl, const char * file_name) {
    /* TODO: Move to a main function */
    freopen("/dev/null", "a+", stdout);
    freopen("/dev/null", "a+", stderr);

    FILE * fh = fopen(file_name, "a");

    if (fh == NULL) {
        return FAIL;
    }

    const time_t ti = time(NULL);
    struct tm *t = gmtime(&ti);

    fprintf((cl->fh = fh), "[%d-%02d-%02d %02d:%02d:%02d UTC] Opening log file.\n",
          t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
          t->tm_sec);

    cl->name = file_name;
    return SUCCESS;
}
