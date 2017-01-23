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
#include <boost/algorithm/string.hpp>
#include "dogen/upsilon/io/name_io.hpp"
#include "dogen/upsilon/types/type.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace upsilon {

type::type(
    const dogen::upsilon::name& name,
    const dogen::upsilon::name& extends,
    const std::string& comment,
    const std::vector<std::string>& tag_refs,
    const std::string& pof_id)
    : name_(name),
      extends_(extends),
      comment_(comment),
      tag_refs_(tag_refs),
      pof_id_(pof_id) { }

void type::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::upsilon::type\"" << ", "
      << "\"name\": " << name_ << ", "
      << "\"extends\": " << extends_ << ", "
      << "\"comment\": " << "\"" << tidy_up_string(comment_) << "\"" << ", "
      << "\"tag_refs\": " << tag_refs_ << ", "
      << "\"pof_id\": " << "\"" << tidy_up_string(pof_id_) << "\""
      << " }";
}

void type::swap(type& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(extends_, other.extends_);
    swap(comment_, other.comment_);
    swap(tag_refs_, other.tag_refs_);
    swap(pof_id_, other.pof_id_);
}

bool type::compare(const type& rhs) const {
    return name_ == rhs.name_ &&
        extends_ == rhs.extends_ &&
        comment_ == rhs.comment_ &&
        tag_refs_ == rhs.tag_refs_ &&
        pof_id_ == rhs.pof_id_;
}

const dogen::upsilon::name& type::name() const {
    return name_;
}

dogen::upsilon::name& type::name() {
    return name_;
}

void type::name(const dogen::upsilon::name& v) {
    name_ = v;
}

void type::name(const dogen::upsilon::name&& v) {
    name_ = std::move(v);
}

const dogen::upsilon::name& type::extends() const {
    return extends_;
}

dogen::upsilon::name& type::extends() {
    return extends_;
}

void type::extends(const dogen::upsilon::name& v) {
    extends_ = v;
}

void type::extends(const dogen::upsilon::name&& v) {
    extends_ = std::move(v);
}

const std::string& type::comment() const {
    return comment_;
}

std::string& type::comment() {
    return comment_;
}

void type::comment(const std::string& v) {
    comment_ = v;
}

void type::comment(const std::string&& v) {
    comment_ = std::move(v);
}

const std::vector<std::string>& type::tag_refs() const {
    return tag_refs_;
}

std::vector<std::string>& type::tag_refs() {
    return tag_refs_;
}

void type::tag_refs(const std::vector<std::string>& v) {
    tag_refs_ = v;
}

void type::tag_refs(const std::vector<std::string>&& v) {
    tag_refs_ = std::move(v);
}

const std::string& type::pof_id() const {
    return pof_id_;
}

std::string& type::pof_id() {
    return pof_id_;
}

void type::pof_id(const std::string& v) {
    pof_id_ = v;
}

void type::pof_id(const std::string&& v) {
    pof_id_ = std::move(v);
}

} }
