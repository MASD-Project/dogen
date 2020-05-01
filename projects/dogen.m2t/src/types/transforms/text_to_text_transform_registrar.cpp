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
#include "dogen.m2t/types/transforms/text_to_text_transform.hpp"
#include "dogen.m2t/types/transforms/text_to_text_transform_registrar.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<dogen::m2t::transforms::text_to_text_transform>& lhs,
const std::shared_ptr<dogen::m2t::transforms::text_to_text_transform>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::m2t::transforms {

text_to_text_transform_registrar::text_to_text_transform_registrar(const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& transforms_for_logical_element_)
    : transforms_for_logical_element__(transforms_for_logical_element_) { }

void text_to_text_transform_registrar::swap(text_to_text_transform_registrar& other) noexcept {
    using std::swap;
    swap(transforms_for_logical_element__, other.transforms_for_logical_element__);
}

bool text_to_text_transform_registrar::operator==(const text_to_text_transform_registrar& rhs) const {
    return transforms_for_logical_element__ == rhs.transforms_for_logical_element__;
}

text_to_text_transform_registrar& text_to_text_transform_registrar::operator=(text_to_text_transform_registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& text_to_text_transform_registrar::transforms_for_logical_element_() const {
    return transforms_for_logical_element__;
}

std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& text_to_text_transform_registrar::transforms_for_logical_element_() {
    return transforms_for_logical_element__;
}

void text_to_text_transform_registrar::transforms_for_logical_element_(const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& v) {
    transforms_for_logical_element__ = v;
}

void text_to_text_transform_registrar::transforms_for_logical_element_(const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >&& v) {
    transforms_for_logical_element__ = std::move(v);
}

}
