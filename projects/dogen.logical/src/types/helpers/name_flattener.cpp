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
#include <boost/thread/exceptions.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/io/helpers/flattening_strategy_io.hpp"
#include "dogen.logical/types/helpers/flattening_error.hpp"
#include "dogen.logical/types/helpers/name_flattener.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.name_flattener"));

const std::string
unsupported_strategy("Flattening strategy is not supported: ");

}

namespace dogen::logical::helpers {

name_flattener::name_flattener(const flattening_strategy flattening_strategy)
    : flattening_strategy_(flattening_strategy) {}

std::list<std::string>
name_flattener::flatten(const entities::name& n) const {
    const auto& l(n.location());
    std::list<std::string> r(l.external_modules());

    for (const auto& m : l.model_modules())
        r.push_back(m);

    for (const auto& m : l.internal_modules())
        r.push_back(m);

    switch(flattening_strategy_) {
    case flattening_strategy::exclude_simple_name:
        break;

    case flattening_strategy::include_simple_name:
        r.push_back(n.simple());
        break;

    case flattening_strategy::exclude_simple_name_conditionally: {
        /*
         * if the name belongs to the model's module, we need to remove the
         * module's simple name from the module path (it is in both the
         * module path and it is also the module's simple name).
         */
        const bool no_internal_modules(l.internal_modules().empty());
        const bool has_model_modules(!l.model_modules().empty());
        const bool is_model_name(no_internal_modules && has_model_modules &&
            n.simple() == l.model_modules().back());

        if (is_model_name)
            r.pop_back();

        break;
    }
    default: {
        std::ostringstream os;
        os << unsupported_strategy << flattening_strategy_;
        const auto s(os.str());
        BOOST_LOG_SEV(lg, error) << s;
        BOOST_THROW_EXCEPTION(flattening_error(s));
    } }

    return r;
}

}
