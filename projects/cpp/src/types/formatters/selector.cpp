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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/selection_error.hpp"
#include "dogen/cpp/types/formatters/selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.selector"));

const std::string no_default_value_for_field(
    "Field definition does not have a default value: ");
const std::string dot(".");

}

namespace dogen {
namespace cpp {
namespace formatters {

selector::selector(const dynamic::schema::repository& rp,
    const dynamic::schema::object& o)
    : repository_(rp), object_(o), field_selector_(object_) { }

std::string selector::
qualify(const std::string& prefix, const std::string& field_name) const {
    return prefix + dot + field_name;
}

bool selector::is_formatter_enabled(const std::string& formatter_name) const {
    const std::string fn(qualify(formatter_name, traits::enabled()));
    if (field_selector_.has_field(fn))
        return field_selector_.get_boolean_content(fn);

    const dynamic::schema::repository_selector s(repository_);
    const auto& fd(s.select_field_by_name(fn));
    if (!fd.default_value()) {
        BOOST_LOG_SEV(lg, error) << no_default_value_for_field << fn;
        BOOST_THROW_EXCEPTION(selection_error(no_default_value_for_field + fn));
    }
    return field_selector_.get_boolean_content(*fd.default_value());
}

bool selector::is_facet_enabled(const std::string& facet_name) const {
    const std::string fn(qualify(facet_name, traits::enabled()));
    if (field_selector_.has_field(fn))
        return field_selector_.get_boolean_content(fn);

    const dynamic::schema::repository_selector s(repository_);
    const auto& fd(s.select_field_by_name(fn));
    if (!fd.default_value()) {
        BOOST_LOG_SEV(lg, error) << no_default_value_for_field << fn;
        BOOST_THROW_EXCEPTION(selection_error(no_default_value_for_field + fn));
    }
    return field_selector_.get_boolean_content(*fd.default_value());
}

bool selector::is_facet_integrated(const std::string& formatter_name,
    const std::string& facet_name) const {

    const std::string fn(qualify(formatter_name, traits::integrated_facet()));
    if (!field_selector_.has_field(fn))
        return false;

    const auto col(field_selector_.get_text_collection_content(fn));
    for (const auto f : col) {
        if (facet_name == f)
            return true;
    }
    return false;
}

} } }
