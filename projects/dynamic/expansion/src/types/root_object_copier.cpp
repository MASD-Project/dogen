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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/dynamic/expansion/types/default_value_expander.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/dynamic/expansion/types/root_object_copier.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion.root_object_copier"));

const std::string model_module_not_found("Could not find the model module: ");

}

namespace dogen {
namespace dynamic {
namespace expansion {

std::string root_object_copier::static_name() {
    static std::string name("root_object_copier");
    return name;
}

root_object_copier::~root_object_copier() noexcept { }

std::string root_object_copier::name() const {
    return static_name();
}

const std::forward_list<std::string>& root_object_copier::dependencies() const {
    static std::forward_list<std::string> r {
        default_value_expander::static_name()
    };
    return r;
}

void root_object_copier::setup(const expansion_context& ec) {
    const auto& m(ec.model());
    const auto i(m.modules().find(m.name()));
    if (i == m.modules().end()) {
        const auto n(sml::string_converter::convert(m.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;
        BOOST_THROW_EXCEPTION(expansion_error(model_module_not_found + n));
    }

    root_object_ = i->second.extensions();
}

void root_object_copier::expand(const sml::qname& /*qn*/,
    const schema::scope_types& st, schema::object& o) const {

    if (st == schema::scope_types::root_module)
        return;

    unsigned int c(0);
    for (const auto& pair : root_object_.fields())
        c += o.fields().insert(pair).second ? 1 : 0;

    BOOST_LOG_SEV(lg, debug) << "Total fields copied from root: " << c;
}

} } }
