/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/filesystem/file_not_found.hpp"

namespace {

const std::string file_not_found("File not found: ");

}

namespace dogen {
namespace utility {
namespace filesystem {

file_not_found::file_not_found(std::string message)
    : dogen::utility::exception::exception(::file_not_found + message) { }

} } }
