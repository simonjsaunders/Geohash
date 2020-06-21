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

#include <iomanip>
#include <iostream>
#include "geohash.hpp"

void encode(double latitude, double longitude, unsigned int precision) {
    std::cout << "Encode latitude " << latitude << ", longitude "
        << longitude << ", precision " << precision
        << "\ngeohash = " << geohash::encode(latitude, longitude, precision)
    << '\n';
}

void decode(const std::string& geohash) {
    auto p = geohash::decode(geohash);
    std::cout << "Decode geohash " << geohash << '\n';
    std::cout << "latitude range: " << p.first.first << " to " << p.first.second << '\n';
    std::cout << "longitude range: " << p.second.first << " to " << p.second.second << '\n';
}

int main() {
    std::cout << std::setprecision(10);
    encode(52.809455, 0.361597, 3);
    std::cout << '\n';
    encode(52.809455, 0.361597, 10);
    std::cout << '\n';
    decode("u12");
    std::cout << '\n';
    decode("u12k2jxm3g");
    std::cout << '\n';
    return 0;
}
