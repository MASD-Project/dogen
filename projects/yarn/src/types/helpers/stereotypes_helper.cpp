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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/yarn/io/meta_model/well_known_stereotypes_io.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"

namespace {

const std::string transform_id("yarn.transforms.stereotypes_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stereotype_object("yarn::object");
const std::string stereotype_object_template("yarn::object_template");
const std::string stereotype_exception("yarn::exception");
const std::string stereotype_primitive("yarn::primitive");
const std::string stereotype_enumeration("yarn::enumeration");
const std::string stereotype_module("yarn::module");
const std::string stereotype_builtin("yarn::builtin");
const std::string stereotype_visitable("yarn::visitable");
const std::string stereotype_fluent("yarn::fluent");
const std::string stereotype_immutable("yarn::immutable");
const std::string stereotype_orm_object("yarn::orm::object");
const std::string stereotype_orm_value("yarn::orm::value");

const std::string unsupported_stereotype("Invalid or unsupported stereotype: ");

}

namespace dogen {
namespace yarn {
namespace helpers {

using meta_model::well_known_stereotypes;

well_known_stereotypes
stereotypes_helper::from_string(const std::string& s) const {
    if (s == stereotype_object)
        return well_known_stereotypes::object;
    else if (s == stereotype_object_template)
        return well_known_stereotypes::object_template;
    else if (s == stereotype_exception)
        return well_known_stereotypes::exception;
    else if (s == stereotype_primitive)
        return well_known_stereotypes::primitive;
    else if (s == stereotype_enumeration)
        return well_known_stereotypes::enumeration;
    else if (s == stereotype_module)
        return well_known_stereotypes::module;
    else if (s == stereotype_builtin)
        return well_known_stereotypes::builtin;
    else if (s == stereotype_visitable)
        return well_known_stereotypes::visitable;
    else if (s == stereotype_fluent)
        return well_known_stereotypes::fluent;
    else if (s == stereotype_immutable)
        return well_known_stereotypes::immutable;
    else if (s == stereotype_orm_object)
        return well_known_stereotypes::orm_object;
    else if (s == stereotype_orm_value)
        return well_known_stereotypes::orm_value;

    return well_known_stereotypes::invalid;
}

stereotypes_conversion_result
stereotypes_helper::from_csv_string(const std::string& s) const {
    if (s.empty()) {
        stereotypes_conversion_result r;
        return r;
    }

    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));
    return from_string(stereotypes);
}

stereotypes_conversion_result stereotypes_helper::
from_string(const std::list<std::string>& stereotypes) const {
    stereotypes_conversion_result r;
    if (stereotypes.empty())
        return r;

    for (const auto& stereotype : stereotypes) {
        const auto wks(from_string(stereotype));
        if (wks != well_known_stereotypes::invalid)
            r.well_known_stereotypes().push_back(wks);
        else
            r.unknown_stereotypes().push_back(stereotype);
    }
    return r;
}

std::string stereotypes_helper::
to_string(const well_known_stereotypes st) const {
    switch(st) {
    case well_known_stereotypes::object: return stereotype_object;
    case well_known_stereotypes::object_template: return stereotype_object;
    case well_known_stereotypes::exception: return stereotype_exception;
    case well_known_stereotypes::primitive: return stereotype_primitive;
    case well_known_stereotypes::enumeration: return stereotype_enumeration;
    case well_known_stereotypes::module: return stereotype_module;
    case well_known_stereotypes::builtin: return stereotype_builtin;
    case well_known_stereotypes::visitable: return stereotype_visitable;
    case well_known_stereotypes::fluent: return stereotype_fluent;
    case well_known_stereotypes::immutable: return stereotype_immutable;
    case well_known_stereotypes::orm_object: return stereotype_orm_object;
    case well_known_stereotypes::orm_value: return stereotype_orm_value;
    default: {
        const std::string s(boost::lexical_cast<std::string>(st));
        BOOST_LOG_SEV(lg, error) << unsupported_stereotype << s;
        using dogen::utility::exception::invalid_enum_value;
        BOOST_THROW_EXCEPTION(invalid_enum_value(unsupported_stereotype + s));
    } }
}

bool stereotypes_helper::
is_element_type(const well_known_stereotypes wkst) const {
    return
        wkst == well_known_stereotypes::object ||
        wkst == well_known_stereotypes::object_template ||
        wkst == well_known_stereotypes::exception ||
        wkst == well_known_stereotypes::primitive ||
        wkst == well_known_stereotypes::enumeration ||
        wkst == well_known_stereotypes::module ||
        wkst == well_known_stereotypes::builtin;
}

std::list<well_known_stereotypes> stereotypes_helper::extract_element_types(
    const std::list<well_known_stereotypes>& wkst) const {

    std::list<well_known_stereotypes> r;
    for (const auto st : wkst) {
        if (is_element_type(st))
            r.push_back(st);
    }

    return r;
}

std::list<well_known_stereotypes> stereotypes_helper::
extract_non_element_types(const std::list<well_known_stereotypes>& wkst) const {
    std::list<well_known_stereotypes> r;
    for (const auto st : wkst) {
        if (!is_element_type(st))
            r.push_back(st);
    }

    return r;
}

} } }
