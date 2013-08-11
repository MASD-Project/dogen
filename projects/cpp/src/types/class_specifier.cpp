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
#include <ostream>
#include "dogen/cpp/io/class_head_io.hpp"
#include "dogen/cpp/io/entity_io.hpp"
#include "dogen/cpp/io/member_specification_io.hpp"
#include "dogen/cpp/types/class_specifier.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::member_specification>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace cpp {

class_specifier::class_specifier(
    const std::string& documentation,
    const dogen::cpp::class_head& head,
    const std::list<dogen::cpp::member_specification>& members)
    : dogen::cpp::entity(documentation),
      head_(head),
      members_(members) { }

void class_specifier::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::class_specifier\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"head\": " << head_ << ", "
      << "\"members\": " << members_
      << " }";
}

void class_specifier::swap(class_specifier& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(head_, other.head_);
    swap(members_, other.members_);
}

bool class_specifier::equals(const dogen::cpp::entity& other) const {
    const class_specifier* const p(dynamic_cast<const class_specifier* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool class_specifier::operator==(const class_specifier& rhs) const {
    return entity::compare(rhs) &&
        head_ == rhs.head_ &&
        members_ == rhs.members_;
}

class_specifier& class_specifier::operator=(class_specifier other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::class_head& class_specifier::head() const {
    return head_;
}

dogen::cpp::class_head& class_specifier::head() {
    return head_;
}

void class_specifier::head(const dogen::cpp::class_head& v) {
    head_ = v;
}

void class_specifier::head(const dogen::cpp::class_head&& v) {
    head_ = std::move(v);
}

const std::list<dogen::cpp::member_specification>& class_specifier::members() const {
    return members_;
}

std::list<dogen::cpp::member_specification>& class_specifier::members() {
    return members_;
}

void class_specifier::members(const std::list<dogen::cpp::member_specification>& v) {
    members_ = v;
}

void class_specifier::members(const std::list<dogen::cpp::member_specification>&& v) {
    members_ = std::move(v);
}

} }