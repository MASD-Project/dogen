/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Dogen Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/filesystem/file_not_found.hpp"
#include "dogen/utility/filesystem/file.hpp"

namespace dogen {
namespace utility {
namespace filesystem {

std::string read_file_content(boost::filesystem::path path) {
    if (!boost::filesystem::exists(path)) {
        throw file_not_found(path.string());
    }

    boost::filesystem::ifstream stream(path);
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string content(
        (std::istreambuf_iterator<char>(stream)),
        std::istreambuf_iterator<char>());
    return content;
}

void write_file_content(boost::filesystem::path path, std::string content) {
    boost::filesystem::ofstream stream(path);
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    stream << content;
}

} } }
