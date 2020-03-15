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
#ifndef DOGEN_TYPES_MODEL_PROCESSING_CONFIGURATION_HPP
#define DOGEN_TYPES_MODEL_PROCESSING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace dogen {

/**
 * @brief Configuration related to the behaviour of Dogen whilst processing models.
 */
class model_processing_configuration final {
public:
    model_processing_configuration(const model_processing_configuration&) = default;
    model_processing_configuration(model_processing_configuration&&) = default;
    ~model_processing_configuration() = default;

public:
    model_processing_configuration();

public:
    model_processing_configuration(
        const bool compatibility_mode_enabled,
        const bool dry_run_mode_enabled,
        const std::vector<std::string>& variability_overrides,
        const boost::posix_time::ptime& activity_timestamp);

public:
    /**
     * @brief Try to process models even if there are errors.
     *
     * Only a certain class of errors are allowed, believed to be caused by backwards or
     * forwards compatibility problems: missing types or types that do not exist.
     */
    /**@{*/
    bool compatibility_mode_enabled() const;
    void compatibility_mode_enabled(const bool v);
    /**@}*/

    /**
     * @brief If true, all transforms wil be executed but no code will be emitted.
     */
    /**@{*/
    bool dry_run_mode_enabled() const;
    void dry_run_mode_enabled(const bool v);
    /**@}*/

    /**
     * @brief Raw set of variability overrides.
     *
     * Overrides are CSV strings in the following format:
     *
     * MODEL_NAME,ELEMENT_NAME,ATTRIBUTE_NAME,KEY,VALUE
     *
     * ELEMENT_NAME and ATTRIBUTE_NAME can be left blank.
     *
     * Please note that you can only override elements in the following cases:
     *
     * - they must have been supplied by the user *directly* on a modeling element (e.g.
     * not as part of a profile).
     * - the type of the feature being overriden must be scalar.
     */
    /**@{*/
    const std::vector<std::string>& variability_overrides() const;
    std::vector<std::string>& variability_overrides();
    void variability_overrides(const std::vector<std::string>& v);
    void variability_overrides(const std::vector<std::string>&& v);
    /**@}*/

    /**
     * @brief Timepoint at which the activity started.
     */
    /**@{*/
    const boost::posix_time::ptime& activity_timestamp() const;
    boost::posix_time::ptime& activity_timestamp();
    void activity_timestamp(const boost::posix_time::ptime& v);
    void activity_timestamp(const boost::posix_time::ptime&& v);
    /**@}*/

public:
    bool operator==(const model_processing_configuration& rhs) const;
    bool operator!=(const model_processing_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_processing_configuration& other) noexcept;
    model_processing_configuration& operator=(model_processing_configuration other);

private:
    bool compatibility_mode_enabled_;
    bool dry_run_mode_enabled_;
    std::vector<std::string> variability_overrides_;
    boost::posix_time::ptime activity_timestamp_;
};

}

namespace std {

template<>
inline void swap(
    dogen::model_processing_configuration& lhs,
    dogen::model_processing_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
