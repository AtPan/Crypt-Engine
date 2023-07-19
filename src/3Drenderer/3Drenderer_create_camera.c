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

#include <Crypt_3D.h>
#include <Crypt_utils/3Drenderer/internal_type.h>

Crypt_3D_camera_t * Crypt_3D_init_camera(Crypt_3D_camera_t * restrict camera, float focal_length, float camera_angle_width, float camera_render_distance) {
    if(camera == NULL) return NULL;

    camera->focal_length = focal_length;
    camera->camera_angle_width = camera_angle_width;
    camera->camera_render_distance = camera_render_distance;

    return camera;
}
