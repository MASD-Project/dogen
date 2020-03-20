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
#ifndef DOGEN_ORCHESTRATION_TYPES_SPEC_DUMPER_HPP
#define DOGEN_ORCHESTRATION_TYPES_SPEC_DUMPER_HPP


#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/types/spec_dumper.hpp"
#include "dogen/types/spec_group.hpp"
#include "dogen.variability/types/entities/value.hpp"
#include "dogen.variability/types/entities/value_type.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"

namespace dogen::orchestration {

class spec_dumper final : public dogen::spec_dumper {
public:
    spec_dumper() = default;
    spec_dumper(const spec_dumper&) = delete;
    spec_dumper(spec_dumper&&) = delete;
    virtual ~spec_dumper() noexcept = default;
    spec_dumper& operator=(const spec_dumper&) = delete;

private:
    /**
     * @brief Pre-processes the string, removing new lines and adding
     * empty string markers as required.
     */
    std::string preprocess(std::string s) const;

    /**
     * @brief Transforms a binding point into a string description.
     */
    std::string process_binding_point(
        const variability::entities::binding_point bp) const;

    /**
     * @brief Transforms a value into a string description.
     */
    std::string process_value(
        const boost::shared_ptr<variability::entities::value> v) const;

    /**
     * @brief Transforms a value type into a string description.
     */
    std::string process_value_type(
        const variability::entities::value_type vt) const;

private:
    /**
     * @brief Creates specs for injection related items.
     */
    spec_group create_injection_group() const;

    /**
     * @brief Creates specs for conversion related items.
     */
    spec_group create_conversion_group() const;

    /**
     * @brief Creates specs for the backends.
     */
    spec_group create_generation_group() const;

    /**
     * @brief Creates specs for all features.
     */
    spec_group create_features_group(
        const variability::entities::feature_model& fm) const;

    /**
     * @brief Creates specs for all variability domains.
     */
    spec_group create_variability_domains_group(const
        std::unordered_map<std::string, std::vector<std::string>>& ds) const;

public:
    virtual specs dump(const dogen::configuration& cfg) const;
};

}

#endif
