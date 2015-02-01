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
#include "dogen/cpp/types/formattables/class_aspects.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class_aspects::class_aspects()
    : enable_complete_constructor_(static_cast<bool>(0)),
      generate_defaulted_functions_(static_cast<bool>(0)),
      generate_explicit_default_constructor_(static_cast<bool>(0)),
      generate_explicit_move_constructor_(static_cast<bool>(0)),
      generate_explicit_destructor_(static_cast<bool>(0)),
      destructor_is_pure_virtual_(static_cast<bool>(0)),
      generate_explicit_assignment_operator_(static_cast<bool>(0)),
      generate_complete_constructor_(static_cast<bool>(0)),
      generate_equality_(static_cast<bool>(0)) { }

class_aspects::class_aspects(
    const bool enable_complete_constructor,
    const bool generate_defaulted_functions,
    const bool generate_explicit_default_constructor,
    const bool generate_explicit_move_constructor,
    const bool generate_explicit_destructor,
    const bool destructor_is_pure_virtual,
    const bool generate_explicit_assignment_operator,
    const bool generate_complete_constructor,
    const bool generate_equality)
    : enable_complete_constructor_(enable_complete_constructor),
      generate_defaulted_functions_(generate_defaulted_functions),
      generate_explicit_default_constructor_(generate_explicit_default_constructor),
      generate_explicit_move_constructor_(generate_explicit_move_constructor),
      generate_explicit_destructor_(generate_explicit_destructor),
      destructor_is_pure_virtual_(destructor_is_pure_virtual),
      generate_explicit_assignment_operator_(generate_explicit_assignment_operator),
      generate_complete_constructor_(generate_complete_constructor),
      generate_equality_(generate_equality) { }

void class_aspects::swap(class_aspects& other) noexcept {
    using std::swap;
    swap(enable_complete_constructor_, other.enable_complete_constructor_);
    swap(generate_defaulted_functions_, other.generate_defaulted_functions_);
    swap(generate_explicit_default_constructor_, other.generate_explicit_default_constructor_);
    swap(generate_explicit_move_constructor_, other.generate_explicit_move_constructor_);
    swap(generate_explicit_destructor_, other.generate_explicit_destructor_);
    swap(destructor_is_pure_virtual_, other.destructor_is_pure_virtual_);
    swap(generate_explicit_assignment_operator_, other.generate_explicit_assignment_operator_);
    swap(generate_complete_constructor_, other.generate_complete_constructor_);
    swap(generate_equality_, other.generate_equality_);
}

bool class_aspects::operator==(const class_aspects& rhs) const {
    return enable_complete_constructor_ == rhs.enable_complete_constructor_ &&
        generate_defaulted_functions_ == rhs.generate_defaulted_functions_ &&
        generate_explicit_default_constructor_ == rhs.generate_explicit_default_constructor_ &&
        generate_explicit_move_constructor_ == rhs.generate_explicit_move_constructor_ &&
        generate_explicit_destructor_ == rhs.generate_explicit_destructor_ &&
        destructor_is_pure_virtual_ == rhs.destructor_is_pure_virtual_ &&
        generate_explicit_assignment_operator_ == rhs.generate_explicit_assignment_operator_ &&
        generate_complete_constructor_ == rhs.generate_complete_constructor_ &&
        generate_equality_ == rhs.generate_equality_;
}

class_aspects& class_aspects::operator=(class_aspects other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool class_aspects::enable_complete_constructor() const {
    return enable_complete_constructor_;
}

void class_aspects::enable_complete_constructor(const bool v) {
    enable_complete_constructor_ = v;
}

bool class_aspects::generate_defaulted_functions() const {
    return generate_defaulted_functions_;
}

void class_aspects::generate_defaulted_functions(const bool v) {
    generate_defaulted_functions_ = v;
}

bool class_aspects::generate_explicit_default_constructor() const {
    return generate_explicit_default_constructor_;
}

void class_aspects::generate_explicit_default_constructor(const bool v) {
    generate_explicit_default_constructor_ = v;
}

bool class_aspects::generate_explicit_move_constructor() const {
    return generate_explicit_move_constructor_;
}

void class_aspects::generate_explicit_move_constructor(const bool v) {
    generate_explicit_move_constructor_ = v;
}

bool class_aspects::generate_explicit_destructor() const {
    return generate_explicit_destructor_;
}

void class_aspects::generate_explicit_destructor(const bool v) {
    generate_explicit_destructor_ = v;
}

bool class_aspects::destructor_is_pure_virtual() const {
    return destructor_is_pure_virtual_;
}

void class_aspects::destructor_is_pure_virtual(const bool v) {
    destructor_is_pure_virtual_ = v;
}

bool class_aspects::generate_explicit_assignment_operator() const {
    return generate_explicit_assignment_operator_;
}

void class_aspects::generate_explicit_assignment_operator(const bool v) {
    generate_explicit_assignment_operator_ = v;
}

bool class_aspects::generate_complete_constructor() const {
    return generate_complete_constructor_;
}

void class_aspects::generate_complete_constructor(const bool v) {
    generate_complete_constructor_ = v;
}

bool class_aspects::generate_equality() const {
    return generate_equality_;
}

void class_aspects::generate_equality(const bool v) {
    generate_equality_ = v;
}

} } }