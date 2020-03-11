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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_FEATURE_SELECTOR_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_FEATURE_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Performs a set of canned queries over a feature model.
 */
class feature_selector final {
public:
    explicit feature_selector(const meta_model::feature_model& fm);

private:
    /**
     * @brief Returns a qualified field name.
     */
    std::string qualify(const std::string& prefix,
        const std::string& feature_name) const;

public:
    /**
     * @brief Tries to get the feature corresponding to the supplied
     * qualified name.
     *
     * @return if one exists, returns it. Returns null otherwise.
     */
    boost::optional<const meta_model::feature&>
    try_get_by_name(const std::string& n) const;

    /**
     * @brief Tries to get the feature corresponding to the qualified
     * name made up of the prefix and the simple name.
     *
     * Prefixes are expected to be formatter and facet names.
     *
     * @return if one exists, returns it. Returns Null otherwise.
     */
    boost::optional<const meta_model::feature&>
    try_get_by_name(const std::string& prefix,
        const std::string& simple_name) const;

public:
    /**
     * @brief Returns the feature corresponding to the supplied
     * qualified name.
     *
     * @pre name must exist.
     */
    const meta_model::feature&
    get_by_name(const std::string& n) const;

    /**
     * @brief Returns the feature corresponding to the qualified name
     * made up of the prefix and the simple name.
     *
     * Prefixes are expected to be formatter and facet names.
     *
     * @pre qualified field name must exist.
     */
    const meta_model::feature& get_by_name(
        const std::string& prefix, const std::string& simple_name) const;

private:
    const meta_model::feature_model& model_;
};

}

#endif
