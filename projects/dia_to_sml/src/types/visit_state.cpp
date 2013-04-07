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
#include "dogen/dia_to_sml/types/visit_state.hpp"

namespace dogen {
namespace dia_to_sml {

visit_state::visit_state()
    : verbose_(static_cast<bool>(0)),
      is_target_(static_cast<bool>(0)) { }

visit_state::visit_state(
    const std::string& model_name,
    const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& pods,
    const std::list<std::string>& external_package_path,
    const bool verbose,
    const bool is_target,
    const std::unordered_map<std::string, std::string>& child_to_parent,
    const std::unordered_set<std::string>& parent_ids,
    const std::unordered_map<std::string, dogen::sml::package>& packages_by_id,
    const std::unordered_map<std::string, dogen::sml::qname>& dia_id_to_qname,
    const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& original_parent,
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& leaves,
    const std::unordered_set<std::string>& dependencies,
    const std::unordered_set<std::string>& top_level_packages)
    : model_name_(model_name),
      pods_(pods),
      external_package_path_(external_package_path),
      verbose_(verbose),
      is_target_(is_target),
      child_to_parent_(child_to_parent),
      parent_ids_(parent_ids),
      packages_by_id_(packages_by_id),
      dia_id_to_qname_(dia_id_to_qname),
      original_parent_(original_parent),
      leaves_(leaves),
      dependencies_(dependencies),
      top_level_packages_(top_level_packages) { }

void visit_state::swap(visit_state& other) noexcept {
    using std::swap;
    swap(model_name_, other.model_name_);
    swap(pods_, other.pods_);
    swap(external_package_path_, other.external_package_path_);
    swap(verbose_, other.verbose_);
    swap(is_target_, other.is_target_);
    swap(child_to_parent_, other.child_to_parent_);
    swap(parent_ids_, other.parent_ids_);
    swap(packages_by_id_, other.packages_by_id_);
    swap(dia_id_to_qname_, other.dia_id_to_qname_);
    swap(original_parent_, other.original_parent_);
    swap(leaves_, other.leaves_);
    swap(dependencies_, other.dependencies_);
    swap(top_level_packages_, other.top_level_packages_);
}

bool visit_state::operator==(const visit_state& rhs) const {
    return model_name_ == rhs.model_name_ &&
        pods_ == rhs.pods_ &&
        external_package_path_ == rhs.external_package_path_ &&
        verbose_ == rhs.verbose_ &&
        is_target_ == rhs.is_target_ &&
        child_to_parent_ == rhs.child_to_parent_ &&
        parent_ids_ == rhs.parent_ids_ &&
        packages_by_id_ == rhs.packages_by_id_ &&
        dia_id_to_qname_ == rhs.dia_id_to_qname_ &&
        original_parent_ == rhs.original_parent_ &&
        leaves_ == rhs.leaves_ &&
        dependencies_ == rhs.dependencies_ &&
        top_level_packages_ == rhs.top_level_packages_;
}

visit_state& visit_state::operator=(visit_state other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& visit_state::model_name() const {
    return model_name_;
}

std::string& visit_state::model_name() {
    return model_name_;
}

void visit_state::model_name(const std::string& v) {
    model_name_ = v;
}

void visit_state::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& visit_state::pods() const {
    return pods_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::pod>& visit_state::pods() {
    return pods_;
}

void visit_state::pods(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& v) {
    pods_ = v;
}

void visit_state::pods(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>&& v) {
    pods_ = std::move(v);
}

const std::list<std::string>& visit_state::external_package_path() const {
    return external_package_path_;
}

std::list<std::string>& visit_state::external_package_path() {
    return external_package_path_;
}

void visit_state::external_package_path(const std::list<std::string>& v) {
    external_package_path_ = v;
}

void visit_state::external_package_path(const std::list<std::string>&& v) {
    external_package_path_ = std::move(v);
}

bool visit_state::verbose() const {
    return verbose_;
}

void visit_state::verbose(const bool v) {
    verbose_ = v;
}

bool visit_state::is_target() const {
    return is_target_;
}

void visit_state::is_target(const bool v) {
    is_target_ = v;
}

const std::unordered_map<std::string, std::string>& visit_state::child_to_parent() const {
    return child_to_parent_;
}

std::unordered_map<std::string, std::string>& visit_state::child_to_parent() {
    return child_to_parent_;
}

void visit_state::child_to_parent(const std::unordered_map<std::string, std::string>& v) {
    child_to_parent_ = v;
}

void visit_state::child_to_parent(const std::unordered_map<std::string, std::string>&& v) {
    child_to_parent_ = std::move(v);
}

const std::unordered_set<std::string>& visit_state::parent_ids() const {
    return parent_ids_;
}

std::unordered_set<std::string>& visit_state::parent_ids() {
    return parent_ids_;
}

void visit_state::parent_ids(const std::unordered_set<std::string>& v) {
    parent_ids_ = v;
}

void visit_state::parent_ids(const std::unordered_set<std::string>&& v) {
    parent_ids_ = std::move(v);
}

const std::unordered_map<std::string, dogen::sml::package>& visit_state::packages_by_id() const {
    return packages_by_id_;
}

std::unordered_map<std::string, dogen::sml::package>& visit_state::packages_by_id() {
    return packages_by_id_;
}

void visit_state::packages_by_id(const std::unordered_map<std::string, dogen::sml::package>& v) {
    packages_by_id_ = v;
}

void visit_state::packages_by_id(const std::unordered_map<std::string, dogen::sml::package>&& v) {
    packages_by_id_ = std::move(v);
}

const std::unordered_map<std::string, dogen::sml::qname>& visit_state::dia_id_to_qname() const {
    return dia_id_to_qname_;
}

std::unordered_map<std::string, dogen::sml::qname>& visit_state::dia_id_to_qname() {
    return dia_id_to_qname_;
}

void visit_state::dia_id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>& v) {
    dia_id_to_qname_ = v;
}

void visit_state::dia_id_to_qname(const std::unordered_map<std::string, dogen::sml::qname>&& v) {
    dia_id_to_qname_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& visit_state::original_parent() const {
    return original_parent_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::qname>& visit_state::original_parent() {
    return original_parent_;
}

void visit_state::original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>& v) {
    original_parent_ = v;
}

void visit_state::original_parent(const std::unordered_map<dogen::sml::qname, dogen::sml::qname>&& v) {
    original_parent_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& visit_state::leaves() const {
    return leaves_;
}

std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& visit_state::leaves() {
    return leaves_;
}

void visit_state::leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >& v) {
    leaves_ = v;
}

void visit_state::leaves(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> >&& v) {
    leaves_ = std::move(v);
}

const std::unordered_set<std::string>& visit_state::dependencies() const {
    return dependencies_;
}

std::unordered_set<std::string>& visit_state::dependencies() {
    return dependencies_;
}

void visit_state::dependencies(const std::unordered_set<std::string>& v) {
    dependencies_ = v;
}

void visit_state::dependencies(const std::unordered_set<std::string>&& v) {
    dependencies_ = std::move(v);
}

const std::unordered_set<std::string>& visit_state::top_level_packages() const {
    return top_level_packages_;
}

std::unordered_set<std::string>& visit_state::top_level_packages() {
    return top_level_packages_;
}

void visit_state::top_level_packages(const std::unordered_set<std::string>& v) {
    top_level_packages_ = v;
}

void visit_state::top_level_packages(const std::unordered_set<std::string>&& v) {
    top_level_packages_ = std::move(v);
}

} }