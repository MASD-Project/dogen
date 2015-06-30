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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include "dogen/sml/types/model.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/cpp/types/formattables/registrar_info.hpp"
#include "dogen/cpp/types/formattables/includers_info.hpp"
#include "dogen/cpp/types/formattables/cmakelists_info.hpp"
#include "dogen/cpp/types/formattables/odb_options_info.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class factory final {
private:
    std::unordered_map<std::string, settings::path_settings>
    clone_path_settings(
        const std::unordered_map<std::string, settings::path_settings>& source,
        const std::string& source_formatter_name,
        const std::string& destination_formatter_name) const;

    sml::qname create_qname(const sml::model& m,
        const std::string& simple_name) const;

    path_derivatives create_path_derivatives(
        const config::cpp_options& opts,
        const sml::model& m,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const sml::qname& qn,
        const std::string& formatter_name) const;

    bool is_enabled(const formatter_properties_repository& fprp,
        const sml::qname& qn, const std::string& formatter_name) const;

public:
    std::shared_ptr<formattable> make_registrar_info(
        const config::cpp_options& opts,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const formatter_properties_repository& fprp,
        const sml::model& m) const;

    std::forward_list<std::shared_ptr<formattable> > make_includers(
        const config::cpp_options& opts,
        const std::unordered_map<std::string, settings::path_settings>& ps,
        const formattables::path_derivatives_repository& pdrp,
        const std::forward_list<
        std::shared_ptr<formatters::formatter_interface>>& formatters,
        const formatter_properties_repository& fprp,
        const sml::model& m) const;

    std::forward_list<std::shared_ptr<formattable> > make_cmakelists(
        const config::cpp_options& opts, const sml::model& m) const;

    std::shared_ptr<formattable> make_odb_options(
        const config::cpp_options& opts, const sml::model& m) const;
};

} } }

#endif
