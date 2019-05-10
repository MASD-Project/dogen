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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_HELPERS_FEATURE_TEMPLATE_REGISTRAR_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_HELPERS_FEATURE_TEMPLATE_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen.variability/types/meta_model/feature_template_repository.hpp"

namespace masd::dogen::variability::helpers {

class feature_template_registrar final {
public:
    feature_template_registrar() = default;
    feature_template_registrar(const feature_template_registrar&) = default;
    feature_template_registrar(feature_template_registrar&&) = default;
    ~feature_template_registrar() = default;

public:
    explicit feature_template_registrar(const masd::dogen::variability::meta_model::feature_template_repository& repository);

public:
    const masd::dogen::variability::meta_model::feature_template_repository& repository() const;
    masd::dogen::variability::meta_model::feature_template_repository& repository();
    void repository(const masd::dogen::variability::meta_model::feature_template_repository& v);
    void repository(const masd::dogen::variability::meta_model::feature_template_repository&& v);

public:
    bool operator==(const feature_template_registrar& rhs) const;
    bool operator!=(const feature_template_registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(feature_template_registrar& other) noexcept;
    feature_template_registrar& operator=(feature_template_registrar other);

private:
    masd::dogen::variability::meta_model::feature_template_repository repository_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::helpers::feature_template_registrar& lhs,
    masd::dogen::variability::helpers::feature_template_registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
