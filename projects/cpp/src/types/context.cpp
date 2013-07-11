/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/context.hpp"

namespace dogen {
namespace cpp {

context::context(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& qname_to_class_info)
    : qname_to_class_info_(qname_to_class_info) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(qname_to_class_info_, other.qname_to_class_info_);
}

bool context::operator==(const context& rhs) const {
    return qname_to_class_info_ == rhs.qname_to_class_info_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& context::qname_to_class_info() const {
    return qname_to_class_info_;
}

std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& context::qname_to_class_info() {
    return qname_to_class_info_;
}

void context::qname_to_class_info(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& v) {
    qname_to_class_info_ = v;
}

void context::qname_to_class_info(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>&& v) {
    qname_to_class_info_ = std::move(v);
}

} }