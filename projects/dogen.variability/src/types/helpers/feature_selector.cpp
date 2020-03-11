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
#include "dogen.variability/types/helpers/selection_exception.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("variability.helpers.feature_selector"));

const std::string dot(".");
const std::string feature_not_found("Could not find expected feature: ");

}

namespace dogen::variability::helpers {

feature_selector::feature_selector(const meta_model::feature_model& fm)
    : model_(fm) {}

std::string feature_selector::
qualify(const std::string& prefix, const std::string& feature_name) const {
    return prefix + dot + feature_name;
}

boost::optional<const meta_model::feature&>
feature_selector::try_get_by_name(const std::string& n) const {
    const auto& c(model_.by_name());
    const auto i(c.find(n));
    if (i == c.end())
        return boost::optional<const meta_model::feature&>();

    return i->second;
}

boost::optional<const meta_model::feature&>
feature_selector::try_get_by_name(const std::string& prefix,
    const std::string& simple_name) const {
    return try_get_by_name(qualify(prefix, simple_name));
}

const meta_model::feature&
feature_selector::get_by_name(const std::string& n) const {
    const auto r(try_get_by_name(n));
    if (!r) {
        BOOST_LOG_SEV(lg, error) << feature_not_found << n;
        BOOST_THROW_EXCEPTION(selection_exception(feature_not_found + n));
    }
    return *r;
}

const meta_model::feature& feature_selector::get_by_name(
    const std::string& prefix, const std::string& simple_name) const {
    return get_by_name(qualify(prefix, simple_name));
}

}
