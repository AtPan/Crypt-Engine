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

/* This file should NOT be included directly!
 * This module is responsible for tracking resources across modules and should not be used by hand!
 * This is your warning.
 */

#ifndef __CRYPT_RESOURCES_H
#define __CRYPT_RESOURCES_H

/* Needed for common types such as flag_t */
#include <Crypt.h>


// -------------------------------------------------------------------------
// Macros

/* Defines the maximum amount of resources that can be allocated at once. */
#define __CRYPT_RESOURCES_MAX_RESOURCES 2

// End of Macros
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
// Enumerated Types

/* This type is meant to be indices into the resource table to identify what
 * that resource is.
 */
enum __Crypt_resource_type_t {
    __Crypt_resource_type_memory = 0,
    __Crypt_resource_type_logger = 1,
};

// End of Enumerated Types
// -------------------------------------------------------------------------

/* Adds a resource to the resource table.
 * Only one of each resource can be saved at any given time.
 *
 * Parameters:
 * @t - The type of resource being added.
 * @p - The resource itself.
 *
 * Returns:
 * FAIL if that resource is already saved or an error occurs, SUCCESS otherwise.
 */
extern flag_t __Crypt_resources_add_resource(enum __Crypt_resource_type_t t, const void * p);

/* Removes a resource from the resource table.
 * This function only marks a resource as free to other modules, it does not actually free the resource.
 * If you wish to free the resource, you must do so yourself.
 *
 * Parameters:
 * @t - The type of resource to remove.
 */
extern void __Crypt_resources_remove_resource(enum __Crypt_resource_type_t t);

/* Retrieves a resource from the resource table.
 *
 * Parameters:
 * @t - The type of resource to retrieve.
 *
 * Returns:
 * The resource, or NULL if the resource does not exist.
 */
extern void * __Crypt_resources_get_resource(enum __Crypt_resource_type_t t);

/* Checks if a given resource is saved to the table.
 *
 * Parameters:
 * @t - The type of resource.
 *
 * Returns:
 * TRUE if the resource exists, FALSE otherwise.
 */
extern bool_t __Crypt_resources_get_resource_bool(enum __Crypt_resource_type_t t);

#endif
