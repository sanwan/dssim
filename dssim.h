/*
 * © 2011-2015 Kornel Lesiński. All rights reserved.
 *
 * This file is part of DSSIM.
 *
 * DSSIM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * DSSIM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the license along with DSSIM.
 * If not, see <http://www.gnu.org/licenses/agpl.txt>.
 */

typedef struct dssim_image dssim_image;
typedef struct dssim_attr dssim_attr;

typedef struct {
    unsigned char r, g, b, a;
} dssim_rgba;

typedef enum dssim_colortype {
    DSSIM_GRAY = 1, // 1 byte per pixel, gamma applied
    DSSIM_RGB  = 2, // 3 bytes per pixel, gamma applied
    DSSIM_RGBA = 3, // 4 bytes per pixel, gamma applied
    DSSIM_LUMA = 4, // 1 byte per pixel, used as-is
    DSSIM_LAB  = 5, // 3 bytes per pixel, used as-is
    DSSIM_RGBA_TO_GRAY = 3 | 32, // 4 bytes per pixel, but only luma is used
} dssim_colortype;

dssim_attr *dssim_create_attr(void);
void dssim_dealloc_attr(dssim_attr *);

/*
  Write one row (from index `y`) of `width` pixels to pre-allocated arrays in `channels`.
  if num_channels == 1 write only to channels[0][0..width-1]
  if num_channels == 3 the write luma to channel 0, and chroma to 1 and 2.
 */
typedef void dssim_row_callback(float *const restrict channels[], const int num_channels, const int y, const int width, void *user_data);

dssim_image *dssim_create_image(dssim_attr *,unsigned char *row_pointers[], dssim_colortype color_type, const int width, const int height, const double gamma);
dssim_image *dssim_create_image_float_callback(dssim_attr *, const int num_channels, const int width, const int height, dssim_row_callback cb, void *callback_user_data);
void dssim_dealloc_image(dssim_image *);

double dssim_compare(dssim_attr *, const dssim_image *restrict original, dssim_image *restrict modified, float **ssim_map_out);
