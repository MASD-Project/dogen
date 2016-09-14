/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/formatters/types/file_properties_workflow.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_repository.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/properties/cmakelists_info.hpp"
#include "dogen/quilt.cpp/types/properties/odb_options_info.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_repository.hpp"
#include "dogen/quilt.cpp/types/properties/formatter_properties_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

class factory final {
private:
    std::unordered_map<std::string, settings::path_settings>
    clone_path_settings(
        const std::unordered_map<std::string, settings::path_settings>& source,
        const std::string& source_formatter_name,
        const std::string& destination_formatter_name) const;

    yarn::name create_name(const yarn::name& model_name,
        const std::string& simple_name) const;

    bool is_enabled(const formatter_properties_repository& fprp,
        const yarn::name& n, const std::string& formatter_name) const;

public:
    std::forward_list<std::shared_ptr<formattable> > make_cmakelists(
        const config::cpp_options& opts,
        const dogen::formatters::file_properties_workflow& fpwf,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const formatter_properties_repository& fprp,
        const yarn::model& m) const;

    std::shared_ptr<formattable> make_odb_options(
        const config::cpp_options& opts,
        const dogen::formatters::file_properties_workflow& fpwf,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const formatter_properties_repository& fprp,
        const yarn::model& m) const;
};

} } } }

#endif
