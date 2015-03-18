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
#include "dogen/cpp/types/settings/bundle_factory.hpp"
#include "dogen/cpp/types/settings/type_settings_factory.hpp"
#include "dogen/cpp/types/settings/common_formatter_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.bundle_factory"));

}

namespace dogen {
namespace cpp {
namespace settings {

bundle_factory::bundle_factory(
    const std::unordered_map<
        std::string, std::forward_list<dynamic::schema::field_definition>
        >& field_definitions_by_formatter_name,
    const std::forward_list<
        boost::shared_ptr<const special_formatter_settings_factory_interface>
        >& special_formatter_settings_factories) :
    field_definitions_by_formatter_name_(field_definitions_by_formatter_name),
    special_formatter_settings_factories_(special_formatter_settings_factories),
    general_settings_factory_(
        std::forward_list<boost::filesystem::path> {
            dogen::utility::filesystem::data_files_directory() }) {
    general_settings_factory_.load_reference_data();
}

dogen::formatters::general_settings bundle_factory::
create_general_settings(const dynamic::schema::object& o) const {
    return general_settings_factory_.make(o);
}

type_settings bundle_factory::
create_type_settings(const dynamic::schema::object& o) const {
    type_settings_factory f;
    return f.make(o);
}

std::unordered_map<std::string, common_formatter_settings>
bundle_factory::create_common_formatter_settings(
    const dynamic::schema::object& o) const {
    common_formatter_settings_factory f(field_definitions_by_formatter_name_);
    return f.make(o);
}

std::unordered_map<
    std::string,
    boost::shared_ptr<special_formatter_settings>
    > bundle_factory::create_special_formatter_settings(
        const dynamic::schema::object& o) const {

    std::unordered_map<
        std::string,
        boost::shared_ptr<special_formatter_settings>
        > r;

    for (const auto f : special_formatter_settings_factories_)
        r[f->formatter_name()] = f->make(o);

    return r;
}

bundle bundle_factory::make(const dynamic::schema::object& o) const {
    bundle r;
    r.general_settings(create_general_settings(o));
    r.type_settings(create_type_settings(o));
    r.common_formatter_settings(create_common_formatter_settings(o));
    r.special_formatter_settings(create_special_formatter_settings(o));
    return r;
}

} } }
