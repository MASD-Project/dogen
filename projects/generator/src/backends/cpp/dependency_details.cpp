/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#include "dogen/generator/backends/cpp/dependency_details.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

const std::unordered_set<sml::qname>& dependency_details::names() const {
    return names_;
}

std::unordered_set<sml::qname>& dependency_details::names() {
    return names_;
}

void dependency_details::names(const std::unordered_set<sml::qname>& v) {
    names_ = v;
}

void dependency_details::names(const std::unordered_set<sml::qname>&& v) {
    names_ = std::move(v);
}

const std::unordered_set<sml::qname>&
dependency_details::forward_decls() const {
    return forward_decls_;
}

std::unordered_set<sml::qname>& dependency_details::forward_decls() {
    return forward_decls_;
}

void dependency_details::
forward_decls(const std::unordered_set<sml::qname>& v) {
    forward_decls_ = v;
}

void dependency_details::
forward_decls(const std::unordered_set<sml::qname>&& v) {
    forward_decls_ = std::move(v);
}

const std::unordered_set<sml::qname>& dependency_details::keys() const {
    return keys_;
}

std::unordered_set<sml::qname>& dependency_details::keys() {
    return keys_;
}

void dependency_details::keys(const std::unordered_set<sml::qname>& v) {
    keys_ = v;
}

void dependency_details::keys(const std::unordered_set<sml::qname>&& v) {
    keys_ = std::move(v);
}

const std::unordered_set<sml::qname>& dependency_details::leaves() const {
    return leaves_;
}

std::unordered_set<sml::qname>& dependency_details::leaves() {
    return leaves_;
}

void dependency_details::leaves(const std::unordered_set<sml::qname>& v) {
    leaves_ = v;
}

void dependency_details::leaves(const std::unordered_set<sml::qname>&& v) {
    leaves_ = std::move(v);
}

bool dependency_details::has_std_string() const {
    return has_std_string_;
}

void dependency_details::has_std_string(const bool v) {
    has_std_string_ = v;
}

bool dependency_details::has_variant() const {
    return has_variant_;
}

void dependency_details::has_variant(const bool v) {
    has_variant_ = v;
}

bool dependency_details::is_parent_or_child() const {
    return is_parent_or_child_;
}

void dependency_details::is_parent_or_child(const bool v) {
    is_parent_or_child_ = v;
}

bool dependency_details::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void dependency_details::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

} } } }
