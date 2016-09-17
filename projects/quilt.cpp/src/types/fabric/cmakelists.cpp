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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

cmakelists::cmakelists()
    : odb_enabled_(static_cast<bool>(0)) { }

cmakelists::cmakelists(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const std::string& original_model_name,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const bool is_element_extension,
    const std::string& model_name,
    const std::string& product_name,
    const bool odb_enabled,
    const std::string& odb_folder)
    : dogen::yarn::element(
      documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      original_model_name,
      contained_by,
      in_global_module,
      is_element_extension),
      model_name_(model_name),
      product_name_(product_name),
      odb_enabled_(odb_enabled),
      odb_folder_(odb_folder) { }

void cmakelists::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void cmakelists::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}


void cmakelists::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::cmakelists\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"model_name\": " << "\"" << tidy_up_string(model_name_) << "\"" << ", "
      << "\"product_name\": " << "\"" << tidy_up_string(product_name_) << "\"" << ", "
      << "\"odb_enabled\": " << odb_enabled_ << ", "
      << "\"odb_folder\": " << "\"" << tidy_up_string(odb_folder_) << "\""
      << " }";
}

void cmakelists::swap(cmakelists& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(model_name_, other.model_name_);
    swap(product_name_, other.product_name_);
    swap(odb_enabled_, other.odb_enabled_);
    swap(odb_folder_, other.odb_folder_);
}

bool cmakelists::equals(const dogen::yarn::element& other) const {
    const cmakelists* const p(dynamic_cast<const cmakelists* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cmakelists::operator==(const cmakelists& rhs) const {
    return element::compare(rhs) &&
        model_name_ == rhs.model_name_ &&
        product_name_ == rhs.product_name_ &&
        odb_enabled_ == rhs.odb_enabled_ &&
        odb_folder_ == rhs.odb_folder_;
}

cmakelists& cmakelists::operator=(cmakelists other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cmakelists::model_name() const {
    return model_name_;
}

std::string& cmakelists::model_name() {
    return model_name_;
}

void cmakelists::model_name(const std::string& v) {
    model_name_ = v;
}

void cmakelists::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::string& cmakelists::product_name() const {
    return product_name_;
}

std::string& cmakelists::product_name() {
    return product_name_;
}

void cmakelists::product_name(const std::string& v) {
    product_name_ = v;
}

void cmakelists::product_name(const std::string&& v) {
    product_name_ = std::move(v);
}

bool cmakelists::odb_enabled() const {
    return odb_enabled_;
}

void cmakelists::odb_enabled(const bool v) {
    odb_enabled_ = v;
}

const std::string& cmakelists::odb_folder() const {
    return odb_folder_;
}

std::string& cmakelists::odb_folder() {
    return odb_folder_;
}

void cmakelists::odb_folder(const std::string& v) {
    odb_folder_ = v;
}

void cmakelists::odb_folder(const std::string&& v) {
    odb_folder_ = std::move(v);
}

} } } }
