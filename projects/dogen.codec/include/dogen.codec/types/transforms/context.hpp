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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.tracing/types/tracer_fwd.hpp"
#include "dogen.variability/types/entities/feature_model_fwd.hpp"

namespace dogen::codec::transforms {

class context final {
public:
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context();

public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
        const boost::shared_ptr<dogen::tracing::tracer>& tracer,
        const bool compatibility_mode,
        const std::vector<std::string>& variability_overrides);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    std::vector<boost::filesystem::path>& data_directories();
    void data_directories(const std::vector<boost::filesystem::path>& v);
    void data_directories(const std::vector<boost::filesystem::path>&& v);

    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model() const;
    boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model();
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>& v);
    void feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>&& v);

    const boost::shared_ptr<dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v);

    bool compatibility_mode() const;
    void compatibility_mode(const bool v);

    /**
     * @brief Raw set of variability overrides.
     */
    /**@{*/
    const std::vector<std::string>& variability_overrides() const;
    std::vector<std::string>& variability_overrides();
    void variability_overrides(const std::vector<std::string>& v);
    void variability_overrides(const std::vector<std::string>&& v);
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
    std::vector<boost::filesystem::path> data_directories_;
    boost::shared_ptr<dogen::variability::entities::feature_model> feature_model_;
    boost::shared_ptr<dogen::tracing::tracer> tracer_;
    bool compatibility_mode_;
    std::vector<std::string> variability_overrides_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::transforms::context& lhs,
    dogen::codec::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
