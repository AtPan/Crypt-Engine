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

#include <Crypt.h>
#include <Crypt_utils/internal_log.h>
#include <time.h>

void Crypt_log_quit(cryptlog_t * cl) {
    const time_t ti = time(NULL);
    struct tm * t = gmtime(&ti);

    fprintf(cl->fh, "[%d-%02d-%02d %02d:%02d:%02d UTC] Closing log file.\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

    fflush(cl->fh);
    fclose(cl->fh);

    cl->fh = NULL;
    cl->name = NULL;
}
