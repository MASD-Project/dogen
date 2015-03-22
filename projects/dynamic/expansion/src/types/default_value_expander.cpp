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
#include "dogen/dynamic/expansion/types/default_value_expander.hpp"


namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion.default_value_expander"));

}

namespace dogen {
namespace dynamic {
namespace expansion {

std::string default_value_expander::static_name() {
    static std::string name("default_value_expander");
    return name;
}

default_value_expander::default_value_expander() : factory_() { }
default_value_expander::~default_value_expander() noexcept { }

unsigned int default_value_expander::create_field_instances(
    const schema::scope_types st, schema::object& o) const {
    auto i(fields_by_scope_.find(st));
    if (i == fields_by_scope_.end())
        return 0;

    unsigned int r(0);
    for (const auto& fd : i->second) {
        const auto n(fd.name().qualified());
        const auto pair(std::make_pair(n, factory_.make(fd)));
        const auto inserted(o.fields().insert(pair).second);
        if (inserted)
            ++r;
    }
    return r;
}

std::string default_value_expander::name() const {
    return static_name();
}

const std::forward_list<std::string>&
default_value_expander::dependencies() const {
    static std::forward_list<std::string> r { options_copier::static_name() };
    return r;
}

void default_value_expander::setup(const expansion_context& ec) {
    for (const auto& fd : ec.field_definitions()) {
        if (!fd.default_value())
            continue;

        fields_by_scope_[fd.scope()].push_back(fd);
    }
}

void default_value_expander::expand(const sml::qname& /*qn*/,
    const schema::scope_types& st, schema::object& o) const {

    unsigned int c(create_field_instances(schema::scope_types::any, o));
    c += create_field_instances(st, o);
    BOOST_LOG_SEV(lg, debug) << "Total fields created: " << c;
}

} } }
