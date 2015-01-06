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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/registrar_error.hpp"
#include "dogen/dynamic/types/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.registrar"));

const std::string no_definitions("No field definitions provided.");

}

namespace dogen {
namespace dynamic {

void registrar::validate() const {
    if (field_definitions_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_definitions;
        BOOST_THROW_EXCEPTION(registrar_error(no_definitions));
    }
    BOOST_LOG_SEV(lg, debug) << "Total field definitions found: "
                             << std::distance(field_definitions_.begin(),
                                 field_definitions_.end());
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void registrar::register_field_definition(const field_definition& fd) {
    field_definitions_.push_front(fd);
}

const std::forward_list<field_definition>&
registrar::field_definitions() const {
    return field_definitions_;
}

} }
