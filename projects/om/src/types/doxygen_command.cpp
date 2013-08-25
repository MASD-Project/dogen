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
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

doxygen_command::doxygen_command()
    : type_(static_cast<dogen::om::doxygen_command_types>(0)) { }

doxygen_command::doxygen_command(
    const dogen::om::doxygen_command_types& type,
    const std::string& argument)
    : type_(type),
      argument_(argument) { }

void doxygen_command::swap(doxygen_command& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
    swap(argument_, other.argument_);
}

bool doxygen_command::operator==(const doxygen_command& rhs) const {
    return type_ == rhs.type_ &&
        argument_ == rhs.argument_;
}

doxygen_command& doxygen_command::operator=(doxygen_command other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::om::doxygen_command_types doxygen_command::type() const {
    return type_;
}

void doxygen_command::type(const dogen::om::doxygen_command_types& v) {
    type_ = v;
}

const std::string& doxygen_command::argument() const {
    return argument_;
}

std::string& doxygen_command::argument() {
    return argument_;
}

void doxygen_command::argument(const std::string& v) {
    argument_ = v;
}

void doxygen_command::argument(const std::string&& v) {
    argument_ = std::move(v);
}

} }