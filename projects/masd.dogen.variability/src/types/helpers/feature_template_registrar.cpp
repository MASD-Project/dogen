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
#include "masd.dogen.variability/types/helpers/feature_template_registrar.hpp"

namespace masd::dogen::variability::helpers {

feature_template_registrar::feature_template_registrar(const masd::dogen::variability::meta_model::feature_template_repository& repository)
    : repository_(repository) { }

void feature_template_registrar::swap(feature_template_registrar& other) noexcept {
    using std::swap;
    swap(repository_, other.repository_);
}

bool feature_template_registrar::operator==(const feature_template_registrar& rhs) const {
    return repository_ == rhs.repository_;
}

feature_template_registrar& feature_template_registrar::operator=(feature_template_registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::variability::meta_model::feature_template_repository& feature_template_registrar::repository() const {
    return repository_;
}

masd::dogen::variability::meta_model::feature_template_repository& feature_template_registrar::repository() {
    return repository_;
}

void feature_template_registrar::repository(const masd::dogen::variability::meta_model::feature_template_repository& v) {
    repository_ = v;
}

void feature_template_registrar::repository(const masd::dogen::variability::meta_model::feature_template_repository&& v) {
    repository_ = std::move(v);
}

}
