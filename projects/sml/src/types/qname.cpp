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
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

qname::qname()
    : meta_type_(static_cast<dogen::sml::meta_types>(0)) { }

qname::qname(
    const std::string& model_name,
    const std::list<std::string>& external_package_path,
    const std::list<std::string>& package_path,
    const std::string& type_name,
    const dogen::sml::meta_types& meta_type)
    : model_name_(model_name),
      external_package_path_(external_package_path),
      package_path_(package_path),
      type_name_(type_name),
      meta_type_(meta_type) { }

void qname::swap(qname& other) noexcept {
    using std::swap;
    swap(model_name_, other.model_name_);
    swap(external_package_path_, other.external_package_path_);
    swap(package_path_, other.package_path_);
    swap(type_name_, other.type_name_);
    swap(meta_type_, other.meta_type_);
}

bool qname::operator==(const qname& rhs) const {
    return model_name_ == rhs.model_name_ &&
        external_package_path_ == rhs.external_package_path_ &&
        package_path_ == rhs.package_path_ &&
        type_name_ == rhs.type_name_ &&
        meta_type_ == rhs.meta_type_;
}

qname& qname::operator=(qname other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }