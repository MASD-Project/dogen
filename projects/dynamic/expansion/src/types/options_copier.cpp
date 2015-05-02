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

const std::string split_project("cpp.split_project");
const std::string disable_complete_constructor(
    "cpp.type.disable_complete_constructor");

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

    BOOST_LOG_SEV(lg, debug) << "Total fields copied: " << c;
}

} } }
