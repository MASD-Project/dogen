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
#include <ostream>
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/io/doxygen_command_io.hpp"
#include "dogen/om/io/text_file_io.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_file.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::om::doxygen_command>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::om::cpp_feature>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::om::cpp_feature>& lhs,
const boost::shared_ptr<dogen::om::cpp_feature>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace om {

cpp_file::cpp_file(
    const boost::filesystem::path& full_path,
    const boost::filesystem::path& relative_path,
    const dogen::om::preamble& preamble,
    const boost::optional<dogen::om::code_generation_marker>& marker,
    const dogen::om::licence& licence,
    const std::list<dogen::om::doxygen_command>& commands,
    const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features)
    : dogen::om::text_file(full_path,
      relative_path,
      preamble,
      marker,
      licence),
      commands_(commands),
      features_(features) { }

void cpp_file::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_file\"" << ", "
      << "\"__parent_0__\": ";
    text_file::to_stream(s);
    s << ", "
      << "\"commands\": " << commands_ << ", "
      << "\"features\": " << features_
      << " }";
}

void cpp_file::swap(cpp_file& other) noexcept {
    text_file::swap(other);

    using std::swap;
    swap(commands_, other.commands_);
    swap(features_, other.features_);
}

bool cpp_file::equals(const dogen::om::text_file& other) const {
    const cpp_file* const p(dynamic_cast<const cpp_file* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_file::operator==(const cpp_file& rhs) const {
    return text_file::compare(rhs) &&
        commands_ == rhs.commands_ &&
        features_ == rhs.features_;
}

cpp_file& cpp_file::operator=(cpp_file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::om::doxygen_command>& cpp_file::commands() const {
    return commands_;
}

std::list<dogen::om::doxygen_command>& cpp_file::commands() {
    return commands_;
}

void cpp_file::commands(const std::list<dogen::om::doxygen_command>& v) {
    commands_ = v;
}

void cpp_file::commands(const std::list<dogen::om::doxygen_command>&& v) {
    commands_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& cpp_file::features() const {
    return features_;
}

std::list<boost::shared_ptr<dogen::om::cpp_feature> >& cpp_file::features() {
    return features_;
}

void cpp_file::features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v) {
    features_ = v;
}

void cpp_file::features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >&& v) {
    features_ = std::move(v);
}

} }