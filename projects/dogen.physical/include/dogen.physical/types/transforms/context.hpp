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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer_fwd.hpp"
#include "dogen/types/diffing_configuration.hpp"
#include "dogen/types/reporting_configuration.hpp"
#include "dogen.physical/types/entities/meta_model_fwd.hpp"
#include "dogen.variability/types/entities/feature_model_fwd.hpp"

namespace dogen::physical::transforms {

class context final {
public:
    context(const context&) = default;
    ~context() = default;

public:
    context();

public:
    context(context&& rhs);

public:
    context(
        const boost::optional<dogen::diffing_configuration>& diffing_configuration,
        const boost::optional<dogen::reporting_configuration>& reporting_configuration,
        const bool dry_run_mode_enabled,
        const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
        const boost::shared_ptr<dogen::physical::entities::meta_model>& meta_model,
        const boost::shared_ptr<dogen::tracing::tracer>& tracer);

public:
    const boost::optional<dogen::diffing_configuration>& diffing_configuration() const;
    boost::optional<dogen::diffing_configuration>& diffing_configuration();
    void diffing_configuration(const boost::optional<dogen::diffing_configuration>& v);
    void diffing_configuration(const boost::optional<dogen::diffing_configuration>&& v);

    const boost::optional<dogen::reporting_configuration>& reporting_configuration() const;
    boost::optional<dogen::reporting_configuration>& reporting_configuration();
    void reporting_configuration(const boost::optional<dogen::reporting_configuration>& v);
    void reporting_configuration(const boost::optional<dogen::reporting_configuration>&& v);

    bool dry_run_mode_enabled() const;
    void dry_run_mode_enabled(const bool v);

    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model() const;
    boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model();
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>& v);
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>&& v);

    /**
     * @brief Meta-model for the physical dimension.
     */
    /**@{*/
    const boost::shared_ptr<dogen::physical::entities::meta_model>& meta_model() const;
    boost::shared_ptr<dogen::physical::entities::meta_model>& meta_model();
    void meta_model(const boost::shared_ptr<dogen::physical::entities::meta_model>& v);
    void meta_model(const boost::shared_ptr<dogen::physical::entities::meta_model>&& v);
    /**@}*/

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
    boost::optional<dogen::diffing_configuration> diffing_configuration_;
    boost::optional<dogen::reporting_configuration> reporting_configuration_;
    bool dry_run_mode_enabled_;
    boost::shared_ptr<dogen::variability::entities::feature_model> feature_model_;
    boost::shared_ptr<dogen::physical::entities::meta_model> meta_model_;
    boost::shared_ptr<dogen::tracing::tracer> tracer_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::transforms::context& lhs,
    dogen::physical::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
