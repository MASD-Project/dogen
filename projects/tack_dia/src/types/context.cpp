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
#include "dogen/tack_dia/types/context.hpp"

namespace dogen {
namespace tack_dia {

context::context(
    const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids,
    const std::unordered_set<std::string>& parent_ids,
    const std::unordered_map<std::string, dogen::tack::qname>& id_to_qname,
    const std::unordered_set<std::string>& top_level_module_names,
    const dogen::tack::model& model)
    : child_id_to_parent_ids_(child_id_to_parent_ids),
      parent_ids_(parent_ids),
      id_to_qname_(id_to_qname),
      top_level_module_names_(top_level_module_names),
      model_(model) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(child_id_to_parent_ids_, other.child_id_to_parent_ids_);
    swap(parent_ids_, other.parent_ids_);
    swap(id_to_qname_, other.id_to_qname_);
    swap(top_level_module_names_, other.top_level_module_names_);
    swap(model_, other.model_);
}

bool context::operator==(const context& rhs) const {
    return child_id_to_parent_ids_ == rhs.child_id_to_parent_ids_ &&
        parent_ids_ == rhs.parent_ids_ &&
        id_to_qname_ == rhs.id_to_qname_ &&
        top_level_module_names_ == rhs.top_level_module_names_ &&
        model_ == rhs.model_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::list<std::string> >& context::child_id_to_parent_ids() const {
    return child_id_to_parent_ids_;
}

std::unordered_map<std::string, std::list<std::string> >& context::child_id_to_parent_ids() {
    return child_id_to_parent_ids_;
}

void context::child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >& v) {
    child_id_to_parent_ids_ = v;
}

void context::child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    child_id_to_parent_ids_ = std::move(v);
}

const std::unordered_set<std::string>& context::parent_ids() const {
    return parent_ids_;
}

std::unordered_set<std::string>& context::parent_ids() {
    return parent_ids_;
}

void context::parent_ids(const std::unordered_set<std::string>& v) {
    parent_ids_ = v;
}

void context::parent_ids(const std::unordered_set<std::string>&& v) {
    parent_ids_ = std::move(v);
}

const std::unordered_map<std::string, dogen::tack::qname>& context::id_to_qname() const {
    return id_to_qname_;
}

std::unordered_map<std::string, dogen::tack::qname>& context::id_to_qname() {
    return id_to_qname_;
}

void context::id_to_qname(const std::unordered_map<std::string, dogen::tack::qname>& v) {
    id_to_qname_ = v;
}

void context::id_to_qname(const std::unordered_map<std::string, dogen::tack::qname>&& v) {
    id_to_qname_ = std::move(v);
}

const std::unordered_set<std::string>& context::top_level_module_names() const {
    return top_level_module_names_;
}

std::unordered_set<std::string>& context::top_level_module_names() {
    return top_level_module_names_;
}

void context::top_level_module_names(const std::unordered_set<std::string>& v) {
    top_level_module_names_ = v;
}

void context::top_level_module_names(const std::unordered_set<std::string>&& v) {
    top_level_module_names_ = std::move(v);
}

const dogen::tack::model& context::model() const {
    return model_;
}

dogen::tack::model& context::model() {
    return model_;
}

void context::model(const dogen::tack::model& v) {
    model_ = v;
}

void context::model(const dogen::tack::model&& v) {
    model_ = std::move(v);
}

} }
