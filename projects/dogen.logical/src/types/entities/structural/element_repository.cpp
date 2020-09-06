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
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/entry_point.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/structural/element_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::module>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::object_template>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::object_template>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::builtin>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::builtin>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::enumeration>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::enumeration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::primitive>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::primitive>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::object>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::object>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::exception>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::exception>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::visitor>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::visitor>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::entry_point>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::entry_point>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::structural::assistant>& lhs,
const boost::shared_ptr<dogen::logical::entities::structural::assistant>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::structural {

element_repository::element_repository(
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::module> >& modules,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object_template> >& object_templates,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::builtin> >& builtins,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::enumeration> >& enumerations,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::primitive> >& primitives,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object> >& objects,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::exception> >& exceptions,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::visitor> >& visitors,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::entry_point> >& entry_points,
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::assistant> >& assistants)
    : modules_(modules),
      object_templates_(object_templates),
      builtins_(builtins),
      enumerations_(enumerations),
      primitives_(primitives),
      objects_(objects),
      exceptions_(exceptions),
      visitors_(visitors),
      entry_points_(entry_points),
      assistants_(assistants) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(modules_, other.modules_);
    swap(object_templates_, other.object_templates_);
    swap(builtins_, other.builtins_);
    swap(enumerations_, other.enumerations_);
    swap(primitives_, other.primitives_);
    swap(objects_, other.objects_);
    swap(exceptions_, other.exceptions_);
    swap(visitors_, other.visitors_);
    swap(entry_points_, other.entry_points_);
    swap(assistants_, other.assistants_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return modules_ == rhs.modules_ &&
        object_templates_ == rhs.object_templates_ &&
        builtins_ == rhs.builtins_ &&
        enumerations_ == rhs.enumerations_ &&
        primitives_ == rhs.primitives_ &&
        objects_ == rhs.objects_ &&
        exceptions_ == rhs.exceptions_ &&
        visitors_ == rhs.visitors_ &&
        entry_points_ == rhs.entry_points_ &&
        assistants_ == rhs.assistants_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::module> >& element_repository::modules() const {
    return modules_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::module> >& element_repository::modules() {
    return modules_;
}

void element_repository::modules(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::module> >& v) {
    modules_ = v;
}

void element_repository::modules(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::module> >&& v) {
    modules_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object_template> >& element_repository::object_templates() const {
    return object_templates_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object_template> >& element_repository::object_templates() {
    return object_templates_;
}

void element_repository::object_templates(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object_template> >& v) {
    object_templates_ = v;
}

void element_repository::object_templates(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object_template> >&& v) {
    object_templates_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::builtin> >& element_repository::builtins() const {
    return builtins_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::builtin> >& element_repository::builtins() {
    return builtins_;
}

void element_repository::builtins(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::builtin> >& v) {
    builtins_ = v;
}

void element_repository::builtins(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::builtin> >&& v) {
    builtins_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::enumeration> >& element_repository::enumerations() const {
    return enumerations_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::enumeration> >& element_repository::enumerations() {
    return enumerations_;
}

void element_repository::enumerations(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::enumeration> >& v) {
    enumerations_ = v;
}

void element_repository::enumerations(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::enumeration> >&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::primitive> >& element_repository::primitives() const {
    return primitives_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::primitive> >& element_repository::primitives() {
    return primitives_;
}

void element_repository::primitives(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::primitive> >& v) {
    primitives_ = v;
}

void element_repository::primitives(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::primitive> >&& v) {
    primitives_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object> >& element_repository::objects() const {
    return objects_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object> >& element_repository::objects() {
    return objects_;
}

void element_repository::objects(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object> >& v) {
    objects_ = v;
}

void element_repository::objects(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::object> >&& v) {
    objects_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::exception> >& element_repository::exceptions() const {
    return exceptions_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::exception> >& element_repository::exceptions() {
    return exceptions_;
}

void element_repository::exceptions(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::exception> >& v) {
    exceptions_ = v;
}

void element_repository::exceptions(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::exception> >&& v) {
    exceptions_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::visitor> >& element_repository::visitors() const {
    return visitors_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::visitor> >& element_repository::visitors() {
    return visitors_;
}

void element_repository::visitors(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::visitor> >& v) {
    visitors_ = v;
}

void element_repository::visitors(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::visitor> >&& v) {
    visitors_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::entry_point> >& element_repository::entry_points() const {
    return entry_points_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::entry_point> >& element_repository::entry_points() {
    return entry_points_;
}

void element_repository::entry_points(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::entry_point> >& v) {
    entry_points_ = v;
}

void element_repository::entry_points(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::entry_point> >&& v) {
    entry_points_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::assistant> >& element_repository::assistants() const {
    return assistants_;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::assistant> >& element_repository::assistants() {
    return assistants_;
}

void element_repository::assistants(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::assistant> >& v) {
    assistants_ = v;
}

void element_repository::assistants(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::structural::assistant> >&& v) {
    assistants_ = std::move(v);
}

}
