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
#define __CRYPT_LOG_H

#include <Crypt_types.h>
#include <Crypt_utils/internal_log.h>

typedef struct __Crypt_log_t cryptlog_t;

// -------------------------------------------------------------------------
// Initializers and Destructors

/* Initializes the log module.
 * This function must be called before any other log function is called.
 *
 * Parameters:
 * @cl - A pointer to the cryptlog_t struct to place logging information in.
 * @fn - The name of the file to open.
 *
 * Returns:
 * SUCCESS if the log file was opened without issue. FAIL on error.
 */
extern flag_t Crypt_log_init(cryptlog_t * cl, const char * restrict fn);

/* Ends the log module and frees all resources used by the log module.
 * Must be called when the log module is done being used.
 *
 * Parameters:
 * @cl - A pointer to the cryptlog_t struct to uninitialize. Does not free the pointer.
 */
extern void Crypt_log_quit(cryptlog_t * cl);

// End of Initializers and Destructors
// -------------------------------------------------------------------------


// -------------------------------------------------------------------------
// Writers

/* Writes a message to an open log file.
 * The log module must have been initiated before this function can be called.
 *
 * Parameters:
 * @cl - A pointer to the cryptlog_t struct to log.
 * @fmt - The format string used in stdio functions like printf.
 */
extern void Crypt_log_write(cryptlog_t * cl, const char * restrict fmt, ...);

// End of Writers
// -------------------------------------------------------------------------


#endif
