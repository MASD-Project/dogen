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
#include "masd.dogen.generation/types/transforms/model_to_text_model_transform_interface.hpp"
#include "masd.dogen.generation/types/transforms/model_to_text_model_transform_registrar.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface>& lhs,
const std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::generation::transforms {

model_to_text_model_transform_registrar::model_to_text_model_transform_registrar(const std::unordered_map<masd::dogen::modeling::meta_model::languages, std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface> >& transforms_by_language_)
    : transforms_by_language__(transforms_by_language_) { }

void model_to_text_model_transform_registrar::swap(model_to_text_model_transform_registrar& other) noexcept {
    using std::swap;
    swap(transforms_by_language__, other.transforms_by_language__);
}

bool model_to_text_model_transform_registrar::operator==(const model_to_text_model_transform_registrar& rhs) const {
    return transforms_by_language__ == rhs.transforms_by_language__;
}

model_to_text_model_transform_registrar& model_to_text_model_transform_registrar::operator=(model_to_text_model_transform_registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<masd::dogen::modeling::meta_model::languages, std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface> >& model_to_text_model_transform_registrar::transforms_by_language_() const {
    return transforms_by_language__;
}

std::unordered_map<masd::dogen::modeling::meta_model::languages, std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface> >& model_to_text_model_transform_registrar::transforms_by_language_() {
    return transforms_by_language__;
}

void model_to_text_model_transform_registrar::transforms_by_language_(const std::unordered_map<masd::dogen::modeling::meta_model::languages, std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface> >& v) {
    transforms_by_language__ = v;
}

void model_to_text_model_transform_registrar::transforms_by_language_(const std::unordered_map<masd::dogen::modeling::meta_model::languages, std::shared_ptr<masd::dogen::generation::transforms::model_to_text_model_transform_interface> >&& v) {
    transforms_by_language__ = std::move(v);
}

}
