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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.codec.dia/types/validation_error.hpp"
#include "dogen.codec.dia/types/validator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("codec.dia.validator"));

const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");

const std::string no_uml_type("No UML type.");

}

namespace dogen::codec::dia {

void validator::validate_uml(const entities::object& po) {
    /*
     * All objects must have a valid UML type.
     *
     * FIXME: should we check against the list of supported object
     * types?
     */
    if (po.object_type().empty()) {
        BOOST_LOG_SEV(lg, error) << no_uml_type;
        BOOST_THROW_EXCEPTION(validation_error(no_uml_type));
    }
}

void validator::validate(const entities::object& po) {
    validate_uml(po);
}

void validator::validate(const std::list<entities::object>& pos) {
    for (const auto& po : pos)
        validate(po);
}

}
