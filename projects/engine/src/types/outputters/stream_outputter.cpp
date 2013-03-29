/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <iostream>
#include "dogen/engine/types/outputters/stream_outputter.hpp"

namespace {

const std::string outputter_name("Stream outputter");
const std::string file_name("Filename: ");
const std::string contents("Contents: ");

}

namespace dogen {
namespace engine {
namespace outputters {

stream_outputter::stream_outputter(std::ostream& stream) : stream_(stream) { }

std::string stream_outputter::outputter_name() {
    return ::outputter_name;
}

void stream_outputter::
output(outputter::value_type value) const {
    for (auto pair : value) {
        stream_ << file_name << pair.first.generic_string() << std::endl
                << contents << std::endl << pair.second << std::endl;
    }
}

} } }
