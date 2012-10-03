/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/config/configuration_error.hpp"
#include "dogen/generator/config/validator.hpp"

namespace {

const std::string missing_target("Mandatory parameter target is missing");
const std::string missing_source_include(
    "You must supply source and include directories for split projects");
const std::string missing_project_dir(
    "You must supply the project directory for split projects");
const std::string unexpected_source_include(
    "Source and include directories cannot be used with non-split projects");
const std::string unexpected_project_dir(
    "Project directories cannot be used with split projects");

}

namespace dogen {
namespace generator {
namespace config {

void validator::validate(const settings& s) {
    if (s.modeling().target().empty())
        throw configuration_error(missing_target);

    const auto cpp(s.cpp());
    if (cpp.split_project()) {
        if (cpp.include_directory().empty() || cpp.source_directory().empty())
            throw configuration_error(missing_source_include);

        if (!cpp.project_directory().empty())
            throw configuration_error(unexpected_project_dir);
    } else {
        if (!cpp.include_directory().empty() || !cpp.source_directory().empty())
            throw configuration_error(unexpected_source_include);

        if (cpp.project_directory().empty())
            throw configuration_error(missing_project_dir);
    }
}

} } }
