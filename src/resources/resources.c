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

#include <stddef.h>
#include <Crypt_utils/internal_resources.h>

static void *__Crypt_resource_table[__CRYPT_RESOURCES_MAX_RESOURCES] = {NULL};

flag_t __Crypt_resources_add_resource(enum __Crypt_resource_type_t t, void *p) {
  if (p == NULL || (size_t)t >= __CRYPT_RESOURCES_MAX_RESOURCES ||
      __Crypt_resource_table[(size_t)t] != NULL)
    return FAIL;

  __Crypt_resource_table[(size_t)t] = p;

  return SUCCESS;
}

void __Crypt_resources_remove_resource(enum __Crypt_resource_type_t t) {
  if ((size_t)t > __CRYPT_RESOURCES_MAX_RESOURCES - 1)
    return;
  __Crypt_resource_table[(size_t)t] = NULL;
}

void * __Crypt_resources_get_resource(enum __Crypt_resource_type_t t) {
    return (size_t)t >= __CRYPT_RESOURCES_MAX_RESOURCES ? NULL : __Crypt_resource_table[(size_t)t];
}

bool_t __Crypt_resources_get_resource_bool(enum __Crypt_resource_type_t t) {
  return (size_t)t < __CRYPT_RESOURCES_MAX_RESOURCES &&
                 __Crypt_resource_table[(size_t)t] != NULL
             ? TRUE
             : FALSE;
}
