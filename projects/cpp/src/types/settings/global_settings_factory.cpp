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
#include "dogen/cpp/types/settings/cpp_settings.hpp"
#include "dogen/cpp/types/settings/facet_settings.hpp"
#include "dogen/cpp/types/settings/cpp_settings_factory.hpp"
#include "dogen/cpp/types/settings/facet_settings_factory.hpp"
#include "dogen/cpp/types/settings/formatter_settings_factory.hpp"
#include "dogen/cpp/types/settings/global_settings_factory.hpp"

namespace dogen {
namespace cpp {
namespace settings {

std::unordered_map<std::string, facet_settings>
global_settings_factory::
create_facet_settings(const sml::module& model_module) const {
    facet_settings_factory f;
    return f.build(model_module.extensions());
}

std::unordered_map<std::string, formatter_settings>
global_settings_factory::
create_formatter_settings(const sml::module& model_module) const {
    formatter_settings_factory f;
    return f.build(model_module.extensions());
}

cpp_settings global_settings_factory::
create_cpp_settings(const sml::module& m) const {
    cpp_settings_factory f;
    return f.build(m.extensions());
}

// formatters::general_settings
// workflow::create_general_settings_activity(const sml::model& m) const {
//     BOOST_LOG_SEV(lg, debug) << "Creating general settings.";

//     boost::optional<formatters::general_settings> r;
//     using formatters::general_settings_factory;
//     general_settings_factory f(data_files_directories_);
//     f.load_reference_data();

//     for (const auto pair : m.modules()) {
//         const auto mod(pair.second);
//         if (mod.generation_type() != sml::generation_types::full_generation ||
//             mod.type() != sml::module_types::model)
//             continue;

//         if (r) {
//             const auto n(sml::string_converter::convert(mod.name()));
//             BOOST_LOG_SEV(lg, error) << multiple_generatable_model_modules << n;
//             BOOST_THROW_EXCEPTION(workflow_error(
//                     multiple_generatable_model_modules + n));
//         }
//         r = f.build(mod.extensions());
//     }

//     if (!r) {
//         BOOST_LOG_SEV(lg, error) << no_generatable_model_modules;
//         BOOST_THROW_EXCEPTION(workflow_error(no_generatable_model_modules));
//     }

//     BOOST_LOG_SEV(lg, debug) << "Finished creating general settings.";
//     return *r;
// }

std::unordered_map<std::string, global_settings> global_settings_factory::
build(const sml::module& model_module) const {

    dogen::formatters::general_settings gs;
    // const auto fmts(create_formatter_settings(model_module));
    const auto cs(create_cpp_settings(model_module));
    const auto fs(create_facet_settings(model_module));

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

} } }
