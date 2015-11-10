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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.name_factory"));

}

namespace dogen {
namespace yarn {

name name_factory::build_model_name(const std::string& model_name,
    const std::string& external_module_path) const {
    name_builder b;
    b.simple_name_contributes_to_qualifed_name(false);
    b.infer_simple_name_from_model_name(true);
    b.model_name(model_name);

    if (!external_module_path.empty())
        b.external_module_path(external_module_path);

    return b.build();
}

name name_factory::build_element_in_model(const name& model_name,
    const std::string& simple_name) const {

    yarn::name n;
    n.simple(simple_name);

    const auto& l(model_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());

    // FIXME: generate qualified name commented out for now
    // name_builder b(n);
    // return b.build();
    return n;
}

name name_factory::build_element_in_module(const name& module_name,
    const std::string& simple_name) const {
    yarn::name n;
    n.simple(simple_name);

    const auto& l(module_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());

    auto pp(l.internal_module_path());
    pp.push_back(module_name.simple());
    n.location().internal_module_path(pp);

    // FIXME:
    // name_builder b(n);
    // return b.build();
    return n;
}


} }
