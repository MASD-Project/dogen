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
#include "dogen/sml/types/pod.hpp"

namespace dogen {
namespace sml {

pod::pod()
    : generate_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      category_type_(static_cast<dogen::sml::category_types>(0)),
      pod_type_(static_cast<dogen::sml::pod_types>(0)),
      number_of_type_arguments_(static_cast<unsigned int>(0)) { }

pod::pod(pod&& rhs)
    : name_(std::move(rhs.name_)),
      properties_(std::move(rhs.properties_)),
      parent_name_(std::move(rhs.parent_name_)),
      original_parent_name_(std::move(rhs.original_parent_name_)),
      leaves_(std::move(rhs.leaves_)),
      generate_(std::move(rhs.generate_)),
      is_parent_(std::move(rhs.is_parent_)),
      category_type_(std::move(rhs.category_type_)),
      pod_type_(std::move(rhs.pod_type_)),
      documentation_(std::move(rhs.documentation_)),
      number_of_type_arguments_(std::move(rhs.number_of_type_arguments_)) { }

pod::pod(
    const dogen::sml::qualified_name& name,
    const std::vector<dogen::sml::property>& properties,
    const boost::optional<dogen::sml::qualified_name>& parent_name,
    const boost::optional<dogen::sml::qualified_name>& original_parent_name,
    const std::list<dogen::sml::qualified_name>& leaves,
    const bool generate,
    const bool is_parent,
    const dogen::sml::category_types& category_type,
    const dogen::sml::pod_types& pod_type,
    const std::string& documentation,
    const unsigned int number_of_type_arguments)
    : name_(name),
      properties_(properties),
      parent_name_(parent_name),
      original_parent_name_(original_parent_name),
      leaves_(leaves),
      generate_(generate),
      is_parent_(is_parent),
      category_type_(category_type),
      pod_type_(pod_type),
      documentation_(documentation),
      number_of_type_arguments_(number_of_type_arguments) { }

void pod::swap(pod& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(properties_, other.properties_);
    swap(parent_name_, other.parent_name_);
    swap(original_parent_name_, other.original_parent_name_);
    swap(leaves_, other.leaves_);
    swap(generate_, other.generate_);
    swap(is_parent_, other.is_parent_);
    swap(category_type_, other.category_type_);
    swap(pod_type_, other.pod_type_);
    swap(documentation_, other.documentation_);
    swap(number_of_type_arguments_, other.number_of_type_arguments_);
}

bool pod::operator==(const pod& rhs) const {
    return name_ == rhs.name_ &&
        properties_ == rhs.properties_ &&
        parent_name_ == rhs.parent_name_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        leaves_ == rhs.leaves_ &&
        generate_ == rhs.generate_ &&
        is_parent_ == rhs.is_parent_ &&
        category_type_ == rhs.category_type_ &&
        pod_type_ == rhs.pod_type_ &&
        documentation_ == rhs.documentation_ &&
        number_of_type_arguments_ == rhs.number_of_type_arguments_;
}

pod& pod::operator=(pod other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }