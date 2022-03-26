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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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

#include "geohash.hpp"
#include <algorithm>
#include <stdexcept>

namespace geohash {

namespace {

constexpr char base32[] = "0123456789bcdefghjkmnpqrstuvwxyz";
constexpr int bits[] = {16, 8, 4, 2, 1};

void refine_interval(std::pair<double, double>& interval, unsigned int index,
                     unsigned int mask) {
    if (index & mask)
        interval.first = (interval.first + interval.second)/2;
    else
        interval.second = (interval.first + interval.second)/2;
}

bool bisect(double coord, std::pair<double, double>& range) {
    double mid = (range.first + range.second)/2.0;
    if (coord > mid) {
        range.first = mid;
        return true;
    }
    range.second = mid;
    return false;
}

}

std::string encode(double latitude, double longitude, unsigned int precision) {
    bool is_even = true;
    std::pair<double, double> lat{-90.0, 90.0};
    std::pair<double, double> lon{-180.0, 180.0};
    unsigned int bit = 0;
    unsigned int index = 0;
    std::string geohash;
    while (geohash.size() < precision) {
        if (is_even ? bisect(longitude, lon) : bisect(latitude, lat))
            index |= bits[bit];
        is_even = !is_even;
        if (bit < 4)
            ++bit;
        else {
            geohash += base32[index];
            bit = 0;
            index = 0;
        }
    }
    return geohash;
}

std::pair<std::pair<double, double>, std::pair<double, double>>
decode(const std::string& geohash) {
    bool is_even = true;
    std::pair<double, double> lat{-90.0, 90.0};
    std::pair<double, double> lon{-180.0, 180.0};
    for (char c : geohash) {
        auto p = std::find(std::begin(base32), std::end(base32), c);
        if (p == std::end(base32))
            throw std::runtime_error("invalid geohash");
        unsigned int index = std::distance(std::begin(base32), p);
        for (unsigned int j = 0; j < std::size(bits); ++j) {
            refine_interval(is_even ? lon : lat, index, bits[j]);
            is_even = !is_even;
        }
    }
    return std::make_pair(lat, lon);
}

} // namespace geohash
