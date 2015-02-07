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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/cpp/io/settings/settings_io.hpp"
#include "dogen/cpp/types/settings/cpp_settings_factory.hpp"
#include "dogen/cpp/types/settings/facet_settings_factory.hpp"
#include "dogen/cpp/types/settings/formatter_settings_factory.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.workflow"));

const std::string model_module_not_found(
    "No generatable model modules found.");
const std::string multiple_model_modules(
    "More than one model module is generatable: ");

}

namespace dogen {
namespace cpp {
namespace settings {

sml::module workflow::obtain_model_module(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining model's module.";

    sml::module r;
    bool found(false);
    for (const auto pair : m.modules()) {
        const auto mod(pair.second);
        if (mod.generation_type() != sml::generation_types::full_generation ||
            mod.type() != sml::module_types::model)
            continue;

        if (found) {
            const auto n(sml::string_converter::convert(mod.name()));
            BOOST_LOG_SEV(lg, error) << multiple_model_modules << n;
            BOOST_THROW_EXCEPTION(workflow_error(multiple_model_modules + n));
        }
        r = pair.second;
        found = true;
    }

    if (!found) {
        const auto n(sml::string_converter::convert(r.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;
        BOOST_THROW_EXCEPTION(workflow_error(model_module_not_found + n));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained model's module.";
    return r;
}

dogen::formatters::general_settings
workflow::create_general_settings(const dynamic::object& o) const {
    using namespace dogen::utility::filesystem;
    const std::forward_list<boost::filesystem::path>
        dirs({data_files_directory()});

    using dogen::formatters::general_settings_factory;
    general_settings_factory f(dirs);
    f.load_reference_data();
    return f.make(o);
}

cpp_settings workflow::
create_cpp_settings(const dynamic::object& o) const {
    cpp_settings_factory f;
    return f.make(o);
}

std::unordered_map<std::string, facet_settings> workflow::
create_facet_settings(const dynamic::indexer& idx,
    const dynamic::object& o) const {
    facet_settings_factory f;
    return f.make(idx.field_definitions_by_facet_name(), o);
}

std::unordered_map<std::string, formatter_settings> workflow::
create_formatter_settings(const dynamic::indexer& idx,
    const dynamic::object& o) const {
    formatter_settings_factory f;
    return f.make(idx.field_definitions_by_formatter_name(), o);
}

global_settings workflow::create_global_settings_activity(
    const dynamic::indexer& idx, const sml::model& m) const {
    const auto mm(obtain_model_module(m));
    const auto o(mm.extensions());

    global_settings r;
    r.general_settings(create_general_settings(o));
    r.cpp_settings(create_cpp_settings(o));
    r.facet_settings(create_facet_settings(idx, o));
    r.formatter_settings(create_formatter_settings(idx, o));
    return r;
}

local_settings workflow::create_local_settings(const dynamic::indexer& /*idx*/,
    const sml::qname& /*qn*/, const dynamic::object& /*o*/) const {
    local_settings r;
    return r;
}

std::unordered_map<std::string, local_settings>
workflow::create_local_settings_activity(const dynamic::indexer& /*idx*/,
    const sml::model& /*m*/) const {
    std::unordered_map<std::string, local_settings> r;
    return r;
}

settings workflow::
execute(const std::forward_list<dynamic::field_definition>& fds,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Creating settings.";

    dynamic::indexer idx;
    idx.index(fds);

    settings r;
    r.global_settings(create_global_settings_activity(idx, m));
    r.local_settings(create_local_settings_activity(idx, m));

    BOOST_LOG_SEV(lg, debug) << "Settings: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished creating settings.";

    return r;
}

} } }
