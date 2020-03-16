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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer_fwd.hpp"
#include "dogen.physical/types/location_repository_fwd.hpp"
#include "dogen.variability/types/entities/feature_model_fwd.hpp"
#include "dogen.logical/types/helpers/mapping_set_repository_fwd.hpp"

namespace dogen::logical::transforms {

/**
 *
 * Context for all assets transformations.
 *
 * Contains all of the external data required for the transformations
 * to execute. It's not ideal to have a huge "global" class, with lots
 * of unrelated state; however, over time, we found that a number of
 * arguments were being supplied across the call graph, resulting in a
 * lot of repetitive code. The context gathers together all of these.
 */
class context final {
public:
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context();

public:
    context(
        const bool compatibility_mode,
        const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
        const boost::shared_ptr<dogen::physical::location_repository>& archetype_location_repository,
        const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains,
        const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& mapping_repository,
        const boost::shared_ptr<dogen::tracing::tracer>& tracer);

public:
    bool compatibility_mode() const;
    void compatibility_mode(const bool v);

    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model() const;
    boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model();
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>& v);
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>&& v);

    const boost::shared_ptr<dogen::physical::location_repository>& archetype_location_repository() const;
    boost::shared_ptr<dogen::physical::location_repository>& archetype_location_repository();
    void archetype_location_repository(const boost::shared_ptr<dogen::physical::location_repository>& v);
    void archetype_location_repository(const boost::shared_ptr<dogen::physical::location_repository>&& v);

    /**
     * @brief Provides all of the domains to be used for template instantiation.
     *
     * Example of a domain is "masd.facet" which contains the list of all available facets.
     * Templates (facet and profile) are then instantiated over this range, depending on
     * user choices.
     */
    /**@{*/
    const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains() const;
    std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains();
    void template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >& v);
    void template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >&& v);
    /**@}*/

    const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& mapping_repository() const;
    boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& mapping_repository();
    void mapping_repository(const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& v);
    void mapping_repository(const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>&& v);

    const boost::shared_ptr<dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    bool compatibility_mode_;
    boost::shared_ptr<dogen::variability::entities::feature_model> feature_model_;
    boost::shared_ptr<dogen::physical::location_repository> archetype_location_repository_;
    std::unordered_map<std::string, std::vector<std::string> > template_instantiation_domains_;
    boost::shared_ptr<dogen::logical::helpers::mapping_set_repository> mapping_repository_;
    boost::shared_ptr<dogen::tracing::tracer> tracer_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::transforms::context& lhs,
    dogen::logical::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
