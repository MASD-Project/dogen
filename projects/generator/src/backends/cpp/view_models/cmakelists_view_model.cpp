/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/backends/cpp/view_models/cmakelists_view_model.hpp"

namespace {

const std::string file_name("CMakeLists.txt");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

std::string cmakelists_view_model::file_name() const {
    return ::file_name;
}

} } } } }
