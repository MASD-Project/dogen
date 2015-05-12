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
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/hash/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/selection_error.hpp"
#include "dogen/cpp/types/formatters/selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.selector"));

}

namespace dogen {
namespace cpp {
namespace formatters {

selector::selector(const dynamic::schema::repository& rp,
    const dynamic::schema::object& o)
    : repository_(rp), object_(o), field_selector_(object_) { }

bool selector::is_formatter_enabled(const std::string& formatter_name) const {
    const auto enabled(cpp::traits::enabled());
    const dynamic::schema::repository_selector s(repository_);
    const auto& fd(s.select_field_by_name(formatter_name, enabled));
    return field_selector_.get_boolean_content_or_default(fd);
}

bool selector::is_facet_enabled(const std::string& facet_name) const {
    const auto enabled(cpp::traits::enabled());
    const dynamic::schema::repository_selector s(repository_);
    const auto& fd(s.select_field_by_name(facet_name, enabled));
    return field_selector_.get_boolean_content_or_default(fd);
}

bool selector::is_facet_integrated(const std::string& formatter_name,
    const std::string& facet_name) const {

    const auto int_fct(cpp::traits::integrated_facet());
    const dynamic::schema::repository_selector s(repository_);
    const auto& fd(s.select_field_by_name(formatter_name, int_fct));

    if (!field_selector_.has_field(fd))
        return false;

    const auto col(field_selector_.get_text_collection_content(fd));
    for (const auto f : col) {
        if (facet_name == f)
            return true;
    }
    return false;
}

bool selector::is_io_enabled() const {
    const auto io_fn(formatters::io::traits::facet_name());
    return is_formatter_enabled(io_fn);
}

bool selector::is_integrated_io_enabled() const {
    if (is_io_enabled()) {
        const auto io_fn(formatters::io::traits::facet_name());
        const auto types_fn(formatters::types::traits::facet_name());
        return is_facet_integrated(types_fn, io_fn);
    }
    return false;
}

bool selector::is_serialization_enabled() const {
    const auto fn(formatters::serialization::traits::facet_name());
    return is_facet_enabled(fn);
}

bool selector::is_hash_enabled() const {
    const auto fn(formatters::hash::traits::facet_name());
    return is_facet_enabled(fn);
}

} } }
