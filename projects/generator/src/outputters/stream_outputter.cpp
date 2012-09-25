/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <iostream>
#include "dogen/generator/outputters/stream_outputter.hpp"

namespace {

const std::string outputter_name("Stream outputter");
const std::string file_name("Filename: ");
const std::string contents("Contents: ");

}

namespace dogen {
namespace generator {
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
