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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/om/io/cpp_abstract_function_io.hpp"
#include "dogen/om/types/cpp_function.hpp"

namespace dogen {
namespace om {

cpp_function::cpp_function()
    : is_template_specialisation_(static_cast<bool>(0)),
      is_template_instantiation_(static_cast<bool>(0)) { }

cpp_function::cpp_function(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_representation_types& representation_type,
    const bool is_inline,
    const dogen::om::cpp_instance_typeref& return_type,
    const std::list<dogen::om::cpp_argument>& arguments,
    const bool is_friend,
    const bool is_template_specialisation,
    const bool is_template_instantiation)
    : dogen::om::cpp_abstract_function(name,
      commands,
      representation_type,
      is_inline,
      return_type,
      arguments,
      is_friend),
      is_template_specialisation_(is_template_specialisation),
      is_template_instantiation_(is_template_instantiation) { }

void cpp_function::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_function\"" << ", "
      << "\"__parent_0__\": ";
    cpp_abstract_function::to_stream(s);
    s << ", "
      << "\"is_template_specialisation\": " << is_template_specialisation_ << ", "
      << "\"is_template_instantiation\": " << is_template_instantiation_
      << " }";
}

void cpp_function::swap(cpp_function& other) noexcept {
    cpp_abstract_function::swap(other);

    using std::swap;
    swap(is_template_specialisation_, other.is_template_specialisation_);
    swap(is_template_instantiation_, other.is_template_instantiation_);
}

bool cpp_function::equals(const dogen::om::cpp_feature& other) const {
    const cpp_function* const p(dynamic_cast<const cpp_function* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_function::operator==(const cpp_function& rhs) const {
    return cpp_abstract_function::compare(rhs) &&
        is_template_specialisation_ == rhs.is_template_specialisation_ &&
        is_template_instantiation_ == rhs.is_template_instantiation_;
}

cpp_function& cpp_function::operator=(cpp_function other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_function::is_template_specialisation() const {
    return is_template_specialisation_;
}

void cpp_function::is_template_specialisation(const bool v) {
    is_template_specialisation_ = v;
}

bool cpp_function::is_template_instantiation() const {
    return is_template_instantiation_;
}

void cpp_function::is_template_instantiation(const bool v) {
    is_template_instantiation_ = v;
}

} }