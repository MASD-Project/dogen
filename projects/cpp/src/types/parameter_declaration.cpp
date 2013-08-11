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
#include "dogen/cpp/types/declarator.hpp"
#include "dogen/cpp/types/parameter_declaration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cpp::declarator>& lhs,
const boost::shared_ptr<dogen::cpp::declarator>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cpp {

parameter_declaration::parameter_declaration(
    const boost::shared_ptr<dogen::cpp::declarator>& declarator,
    const std::string& assignment_expression)
    : declarator_(declarator),
      assignment_expression_(assignment_expression) { }

void parameter_declaration::swap(parameter_declaration& other) noexcept {
    using std::swap;
    swap(declarator_, other.declarator_);
    swap(assignment_expression_, other.assignment_expression_);
}

bool parameter_declaration::operator==(const parameter_declaration& rhs) const {
    return declarator_ == rhs.declarator_ &&
        assignment_expression_ == rhs.assignment_expression_;
}

parameter_declaration& parameter_declaration::operator=(parameter_declaration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::cpp::declarator>& parameter_declaration::declarator() const {
    return declarator_;
}

boost::shared_ptr<dogen::cpp::declarator>& parameter_declaration::declarator() {
    return declarator_;
}

void parameter_declaration::declarator(const boost::shared_ptr<dogen::cpp::declarator>& v) {
    declarator_ = v;
}

void parameter_declaration::declarator(const boost::shared_ptr<dogen::cpp::declarator>&& v) {
    declarator_ = std::move(v);
}

const std::string& parameter_declaration::assignment_expression() const {
    return assignment_expression_;
}

std::string& parameter_declaration::assignment_expression() {
    return assignment_expression_;
}

void parameter_declaration::assignment_expression(const std::string& v) {
    assignment_expression_ = v;
}

void parameter_declaration::assignment_expression(const std::string&& v) {
    assignment_expression_ = std::move(v);
}

} }