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
#include <string>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/expansion/types/options_copier.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion.options_copier"));

// FIXME: we are not referencing cpp::traits to avoid circular
// dependencies.
const std::string split_project("cpp.split_project");
const std::string disable_complete_constructor(
    "cpp.type.disable_complete_constructor");

const std::string cpp_types_enabled("cpp.types.enabled");
const std::string cpp_hash_enabled("cpp.hash.enabled");
const std::string cpp_serialization_enabled("cpp.serialization.enabled");
const std::string cpp_io_enabled("cpp.io.enabled");
const std::string cpp_test_data_enabled("cpp.test_data.enabled");
const std::string cpp_odb_enabled("cpp.odb.enabled");

}

namespace dogen {
namespace dynamic {
namespace expansion {

std::string options_copier::static_name() {
    static std::string name("options_copier");
    return name;
}

options_copier::options_copier() : factory_() { }
options_copier::~options_copier() noexcept { }

unsigned int options_copier::insert_field(const std::string& n, const bool v,
    schema::object& o) const {
    const auto pair(std::make_pair(n, factory_.make_boolean(v)));
    return o.fields().insert(pair).second ? 1 : 0;
}

unsigned int options_copier::insert_field(const std::string& n,
    const std::string& v, schema::object& o) const {
    const auto pair(std::make_pair(n, factory_.make_text(v)));
    return o.fields().insert(pair).second ? 1 : 0;
}

bool options_copier::
is_facet_enabled(const config::cpp_facet_types ft) const {
    const auto i(options_.enabled_facets().find(ft));
    return i != options_.enabled_facets().end();
}

std::string options_copier::name() const {
    return static_name();
}

const std::forward_list<std::string>&
options_copier::dependencies() const {
    static std::forward_list<std::string> r;
    return r;
}

void options_copier::setup(const expansion_context& ec) {
    options_ = ec.cpp_options();
}

void options_copier::expand(const sml::qname& /*qn*/,
    const schema::scope_types& st, schema::object& o) const {

    if (st != schema::scope_types::root_module)
        return;

    unsigned int c(insert_field(split_project, options_.split_project(), o));
    c += insert_field(disable_complete_constructor,
        options_.disable_complete_constructor(), o);

    using ft = config::cpp_facet_types;
    c += insert_field(cpp_types_enabled, is_facet_enabled(ft::types), o);
    c += insert_field(cpp_hash_enabled, is_facet_enabled(ft::hash), o);
    c += insert_field(cpp_serialization_enabled,
        is_facet_enabled(ft::serialization), o);
    c += insert_field(cpp_io_enabled, is_facet_enabled(ft::io), o);
    c += insert_field(cpp_test_data_enabled,
        is_facet_enabled(ft::test_data), o);
    c += insert_field(cpp_odb_enabled, is_facet_enabled(ft::odb), o);

    BOOST_LOG_SEV(lg, debug) << "Total fields copied: " << c;
}

} } }
