#ifndef GEOHASH_H
#define GEOHASH_H

/*
 * Copyright (c) 2020 Simon J. Saunders
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Based on Geohash library for Javascript by David Troy
 * See https://github.com/davetroy/geohash-js/
 */

#include <string>
#include <utility>

namespace geohash {

/**
 * Calculates the geohash for a location specified as a latitude and
 * longitude in degrees with the desired precision.
 *
 * Results are undefined if the specified coordinates are invalid.
 *
 * @param latitude in degrees (-90 to +90)
 * @param longitude in degrees (-180 to +180)
 * @param precision the precision of the result
 * @return the geohash for the specified coordinates
 */
std::string encode(double latitude, double longitude, unsigned int precision);

/**
 * Given a geohash string, returns a pair where the first element
 * is the latitude range and the second element is the longitude
 * range. Ranges are pairs where the first element is the minimum
 * value and the second is the maximum value.
 *
 * Results are undefined if the string is not a valid geohash.
 *
 * @param geohash a geohash
 * @return min/max latitude and longitude
 */
std::pair<std::pair<double, double>, std::pair<double, double>>
decode(const std::string& geohash);

} // namespace geohash

#endif // GEOHASH_H
