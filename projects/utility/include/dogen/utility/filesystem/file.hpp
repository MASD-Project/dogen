/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace filesystem {

std::string read_file_content(boost::filesystem::path path);
void write_file_content(boost::filesystem::path path, std::string content);

} } }
