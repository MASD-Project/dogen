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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONFIGURATION_PROCESSING_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONFIGURATION_PROCESSING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_template.hpp"

namespace masd::dogen::variability::transforms {

class configuration_processing final {
public:
    configuration_processing(const configuration_processing&) = default;
    configuration_processing(configuration_processing&&) = default;
    ~configuration_processing() = default;

public:
    configuration_processing();

public:
    configuration_processing(
        const masd::dogen::variability::meta_model::configuration_template& configuration_template,
        const masd::dogen::variability::meta_model::configuration& configuration,
        const bool merged);

public:
    const masd::dogen::variability::meta_model::configuration_template& configuration_template() const;
    masd::dogen::variability::meta_model::configuration_template& configuration_template();
    void configuration_template(const masd::dogen::variability::meta_model::configuration_template& v);
    void configuration_template(const masd::dogen::variability::meta_model::configuration_template&& v);

    const masd::dogen::variability::meta_model::configuration& configuration() const;
    masd::dogen::variability::meta_model::configuration& configuration();
    void configuration(const masd::dogen::variability::meta_model::configuration& v);
    void configuration(const masd::dogen::variability::meta_model::configuration&& v);

    bool merged() const;
    void merged(const bool v);

public:
    bool operator==(const configuration_processing& rhs) const;
    bool operator!=(const configuration_processing& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration_processing& other) noexcept;
    configuration_processing& operator=(configuration_processing other);

private:
    masd::dogen::variability::meta_model::configuration_template configuration_template_;
    masd::dogen::variability::meta_model::configuration configuration_;
    bool merged_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::transforms::configuration_processing& lhs,
    masd::dogen::variability::transforms::configuration_processing& rhs) {
    lhs.swap(rhs);
}

}

#endif
