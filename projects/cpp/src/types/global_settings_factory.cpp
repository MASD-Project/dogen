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
#include "dogen/cpp/types/cpp_settings.hpp"
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/cpp_settings_factory.hpp"
#include "dogen/cpp/types/facet_settings_factory.hpp"
#include "dogen/cpp/types/formatter_settings_factory.hpp"
#include "dogen/cpp/types/global_settings_factory.hpp"

namespace dogen {
namespace cpp {

std::unordered_map<std::string, facet_settings>
global_settings_factory::create_facet_settings(
    const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id, const sml::module& model_module) const {
    facet_settings_factory f;
    return f.build(default_facet_settings_by_facet_id,
        model_module.extensions());
}

std::unordered_map<std::string, formatter_settings>
global_settings_factory::create_formatter_settings(
    const std::unordered_map<std::string, formatter_settings>&
    default_formatter_settings_by_formatter_id,
    const sml::module& model_module) const {
    formatter_settings_factory f;
    return f.build(default_formatter_settings_by_formatter_id,
        model_module.extensions());
}

cpp_settings global_settings_factory::
create_cpp_settings(const sml::module& m) const {
    cpp_settings_factory f;
    return f.build(m.extensions());
}

std::unordered_map<std::string, global_settings> global_settings_factory::
build(const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id,
    /*const std::unordered_map<std::string, formatter_settings>&
      default_formatter_settings_by_formatter_id,FIXME*/
    const dogen::formatters::general_settings& gs,
    const sml::module& model_module) const {

    // const auto fmts(create_formatter_settings(
    //         default_formatter_settings_by_formatter_id, model_module));
    const auto cs(create_cpp_settings(model_module));
    const auto fs(create_facet_settings(
            default_facet_settings_by_facet_id, model_module));

    std::unordered_map<std::string, global_settings> r;
    for (auto pair : fs) {
        global_settings glob;
        glob.general_settings(gs);
        glob.cpp_settings(cs);
        glob.facet_settings(pair.second);
        r[pair.first] = glob;
    }
    return r;
}

} }
