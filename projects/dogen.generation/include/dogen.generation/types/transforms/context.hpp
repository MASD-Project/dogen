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
#ifndef DOGEN_GENERATION_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_GENERATION_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.tracing/types/tracer_fwd.hpp"
#include "dogen.variability/types/entities/feature_model_fwd.hpp"
#include "dogen.physical/types/entities/location_repository_fwd.hpp"
#include "dogen.generation/types/entities/intra_backend_segment_properties.hpp"

namespace dogen::generation::transforms {

class context final {
public:
    context() = default;
    context(const context&) = default;
    ~context() = default;

public:
    context(context&& rhs);

public:
    context(
        const boost::shared_ptr<dogen::physical::entities::location_repository>& archetype_location_repository,
        const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties,
        const boost::filesystem::path& output_directory_path,
        const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
        const boost::shared_ptr<dogen::tracing::tracer>& tracer,
        const std::string& generation_timestamp);

public:
    const boost::shared_ptr<dogen::physical::entities::location_repository>& archetype_location_repository() const;
    boost::shared_ptr<dogen::physical::entities::location_repository>& archetype_location_repository();
    void archetype_location_repository(const boost::shared_ptr<dogen::physical::entities::location_repository>& v);
    void archetype_location_repository(const boost::shared_ptr<dogen::physical::entities::location_repository>&& v);

    const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties() const;
    std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& intra_backend_segment_properties();
    void intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>& v);
    void intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties>&& v);

    /**
     * @brief FIXME: to be removed
     */
    /**@{*/
    const boost::filesystem::path& output_directory_path() const;
    boost::filesystem::path& output_directory_path();
    void output_directory_path(const boost::filesystem::path& v);
    void output_directory_path(const boost::filesystem::path&& v);
    /**@}*/

    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model() const;
    boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model();
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>& v);
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>&& v);

    const boost::shared_ptr<dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v);

    /**
     * @brief Human readable timestamp of when the generation took place.
     */
    /**@{*/
    const std::string& generation_timestamp() const;
    std::string& generation_timestamp();
    void generation_timestamp(const std::string& v);
    void generation_timestamp(const std::string&& v);
    /**@}*/

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    boost::shared_ptr<dogen::physical::entities::location_repository> archetype_location_repository_;
    std::unordered_map<std::string, dogen::generation::entities::intra_backend_segment_properties> intra_backend_segment_properties_;
    boost::filesystem::path output_directory_path_;
    boost::shared_ptr<dogen::variability::entities::feature_model> feature_model_;
    boost::shared_ptr<dogen::tracing::tracer> tracer_;
    std::string generation_timestamp_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::transforms::context& lhs,
    dogen::generation::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
