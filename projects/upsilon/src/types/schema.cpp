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
#include "dogen/upsilon/types/type.hpp"
#include "dogen/upsilon/types/schema.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::upsilon::type>& lhs,
const boost::shared_ptr<dogen::upsilon::type>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace upsilon {

schema::schema(
    const std::string& name,
    const std::string& id_min,
    const std::string& id_max,
    const std::string& base_guid,
    const std::list<dogen::upsilon::dependency>& dependencies,
    const std::vector<dogen::upsilon::tag>& tags,
    const std::vector<boost::shared_ptr<dogen::upsilon::type> >& types)
    : name_(name),
      id_min_(id_min),
      id_max_(id_max),
      base_guid_(base_guid),
      dependencies_(dependencies),
      tags_(tags),
      types_(types) { }

void schema::swap(schema& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(id_min_, other.id_min_);
    swap(id_max_, other.id_max_);
    swap(base_guid_, other.base_guid_);
    swap(dependencies_, other.dependencies_);
    swap(tags_, other.tags_);
    swap(types_, other.types_);
}

bool schema::operator==(const schema& rhs) const {
    return name_ == rhs.name_ &&
        id_min_ == rhs.id_min_ &&
        id_max_ == rhs.id_max_ &&
        base_guid_ == rhs.base_guid_ &&
        dependencies_ == rhs.dependencies_ &&
        tags_ == rhs.tags_ &&
        types_ == rhs.types_;
}

schema& schema::operator=(schema other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& schema::name() const {
    return name_;
}

std::string& schema::name() {
    return name_;
}

void schema::name(const std::string& v) {
    name_ = v;
}

void schema::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& schema::id_min() const {
    return id_min_;
}

std::string& schema::id_min() {
    return id_min_;
}

void schema::id_min(const std::string& v) {
    id_min_ = v;
}

void schema::id_min(const std::string&& v) {
    id_min_ = std::move(v);
}

const std::string& schema::id_max() const {
    return id_max_;
}

std::string& schema::id_max() {
    return id_max_;
}

void schema::id_max(const std::string& v) {
    id_max_ = v;
}

void schema::id_max(const std::string&& v) {
    id_max_ = std::move(v);
}

const std::string& schema::base_guid() const {
    return base_guid_;
}

std::string& schema::base_guid() {
    return base_guid_;
}

void schema::base_guid(const std::string& v) {
    base_guid_ = v;
}

void schema::base_guid(const std::string&& v) {
    base_guid_ = std::move(v);
}

const std::list<dogen::upsilon::dependency>& schema::dependencies() const {
    return dependencies_;
}

std::list<dogen::upsilon::dependency>& schema::dependencies() {
    return dependencies_;
}

void schema::dependencies(const std::list<dogen::upsilon::dependency>& v) {
    dependencies_ = v;
}

void schema::dependencies(const std::list<dogen::upsilon::dependency>&& v) {
    dependencies_ = std::move(v);
}

const std::vector<dogen::upsilon::tag>& schema::tags() const {
    return tags_;
}

std::vector<dogen::upsilon::tag>& schema::tags() {
    return tags_;
}

void schema::tags(const std::vector<dogen::upsilon::tag>& v) {
    tags_ = v;
}

void schema::tags(const std::vector<dogen::upsilon::tag>&& v) {
    tags_ = std::move(v);
}

const std::vector<boost::shared_ptr<dogen::upsilon::type> >& schema::types() const {
    return types_;
}

std::vector<boost::shared_ptr<dogen::upsilon::type> >& schema::types() {
    return types_;
}

void schema::types(const std::vector<boost::shared_ptr<dogen::upsilon::type> >& v) {
    types_ = v;
}

void schema::types(const std::vector<boost::shared_ptr<dogen::upsilon::type> >&& v) {
    types_ = std::move(v);
}

} }
