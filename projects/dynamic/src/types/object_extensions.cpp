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
#include "dogen/dynamic/types/text.hpp"
#include "dogen/dynamic/types/boolean.hpp"
#include "dogen/dynamic/types/text_collection.hpp"
#include "dogen/dynamic/types/field_access_error.hpp"
#include "dogen/dynamic/types/object_extensions.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("dynamic.object_extensions.cpp"));

const std::string field_not_found("Field not found: ");
const std::string unexpected_field_type("Field has an unexpected type: ");

}

namespace dogen {
namespace dynamic {

bool has_field(const object& o, const field_definition& fd) {
    const auto i(o.fields().find(fd.name().complete_name()));
    return (i != o.fields().end());
}

const field& get_field(const object& o, const field_definition& fd) {
    const auto n(fd.name().complete_name());
    const auto i(o.fields().find(n));

    if (i == o.fields().end()) {
        BOOST_LOG_SEV(lg, error) << field_not_found << n;
        BOOST_THROW_EXCEPTION(field_access_error(field_not_found + n));
    }

    return i->second;
}

std::string
get_text_content(const object& o, const field_definition& fd) {
    const auto& f(get_field(o, fd));
    const auto& v(*f.value());

    try {
        const auto& t(dynamic_cast<const text&>(v));
        return t.content();
    } catch(const std::bad_cast& e) {
        const auto n(fd.name().complete_name());
        BOOST_LOG_SEV(lg, error) << unexpected_field_type << n;
        BOOST_THROW_EXCEPTION(field_access_error(unexpected_field_type + n));
    }
}

std::list<std::string>
get_text_collection_content(const object& o, const field_definition& fd) {
    const auto& f(get_field(o, fd));
    const auto& v(*f.value());

    try {
        const auto& tc(dynamic_cast<const text_collection&>(v));
        return tc.content();
    } catch(const std::bad_cast& e) {
        const auto n(fd.name().complete_name());
        BOOST_LOG_SEV(lg, error) << unexpected_field_type << n;
        BOOST_THROW_EXCEPTION(field_access_error(unexpected_field_type + n));
    }
}

bool get_boolean_content(const object& o, const field_definition& fd) {
    const auto& f(get_field(o, fd));
    const auto& v(*f.value());

    try {
        const auto& b(dynamic_cast<const boolean&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        const auto n(fd.name().complete_name());
        BOOST_LOG_SEV(lg, error) << unexpected_field_type << n;
        BOOST_THROW_EXCEPTION(field_access_error(unexpected_field_type + n));
    }
}

} }
