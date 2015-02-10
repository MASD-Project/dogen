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
#include "dogen/cpp/io/formattables/abilities_io.hpp"
#include "dogen/cpp/io/formattables/class_aspects_io.hpp"
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/io/formattables/inheritance_io.hpp"
#include "dogen/cpp/io/formattables/state_io.hpp"
#include "dogen/cpp/types/formattables/new_class_info.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

new_class_info::new_class_info(
    const std::string& identity,
    const std::unordered_map<std::string, boost::filesystem::path>& file_path_by_formatter_name,
    const std::string& name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const std::unordered_map<std::string, boost::filesystem::path>& include_path_by_formatter_name,
    const std::unordered_map<std::string, dogen::cpp::formattables::includes>& includes_by_formatter_name,
    const dogen::cpp::formattables::state& state,
    const dogen::cpp::formattables::inheritance& inheritance,
    const dogen::cpp::formattables::abilities& abilities,
    const dogen::cpp::formattables::class_aspects& aspects)
    : dogen::cpp::formattables::entity(identity,
      file_path_by_formatter_name,
      name,
      documentation,
      namespaces,
      include_path_by_formatter_name,
      includes_by_formatter_name),
      state_(state),
      inheritance_(inheritance),
      abilities_(abilities),
      aspects_(aspects) { }

void new_class_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::new_class_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"state\": " << state_ << ", "
      << "\"inheritance\": " << inheritance_ << ", "
      << "\"abilities\": " << abilities_ << ", "
      << "\"aspects\": " << aspects_
      << " }";
}

void new_class_info::swap(new_class_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(state_, other.state_);
    swap(inheritance_, other.inheritance_);
    swap(abilities_, other.abilities_);
    swap(aspects_, other.aspects_);
}

bool new_class_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const new_class_info* const p(dynamic_cast<const new_class_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool new_class_info::operator==(const new_class_info& rhs) const {
    return entity::compare(rhs) &&
        state_ == rhs.state_ &&
        inheritance_ == rhs.inheritance_ &&
        abilities_ == rhs.abilities_ &&
        aspects_ == rhs.aspects_;
}

new_class_info& new_class_info::operator=(new_class_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::cpp::formattables::state& new_class_info::state() const {
    return state_;
}

dogen::cpp::formattables::state& new_class_info::state() {
    return state_;
}

void new_class_info::state(const dogen::cpp::formattables::state& v) {
    state_ = v;
}

void new_class_info::state(const dogen::cpp::formattables::state&& v) {
    state_ = std::move(v);
}

const dogen::cpp::formattables::inheritance& new_class_info::inheritance() const {
    return inheritance_;
}

dogen::cpp::formattables::inheritance& new_class_info::inheritance() {
    return inheritance_;
}

void new_class_info::inheritance(const dogen::cpp::formattables::inheritance& v) {
    inheritance_ = v;
}

void new_class_info::inheritance(const dogen::cpp::formattables::inheritance&& v) {
    inheritance_ = std::move(v);
}

const dogen::cpp::formattables::abilities& new_class_info::abilities() const {
    return abilities_;
}

dogen::cpp::formattables::abilities& new_class_info::abilities() {
    return abilities_;
}

void new_class_info::abilities(const dogen::cpp::formattables::abilities& v) {
    abilities_ = v;
}

void new_class_info::abilities(const dogen::cpp::formattables::abilities&& v) {
    abilities_ = std::move(v);
}

const dogen::cpp::formattables::class_aspects& new_class_info::aspects() const {
    return aspects_;
}

dogen::cpp::formattables::class_aspects& new_class_info::aspects() {
    return aspects_;
}

void new_class_info::aspects(const dogen::cpp::formattables::class_aspects& v) {
    aspects_ = v;
}

void new_class_info::aspects(const dogen::cpp::formattables::class_aspects&& v) {
    aspects_ = std::move(v);
}

} } }