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
#include "dogen/om/io/odb_option_io.hpp"
#include "dogen/om/io/text_file_io.hpp"
#include "dogen/om/types/odb_option.hpp"
#include "dogen/om/types/odb_options_file.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::om::odb_option>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<boost::shared_ptr<dogen::om::odb_option> >& v) {
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

inline bool operator==(const boost::shared_ptr<dogen::om::odb_option>& lhs,
const boost::shared_ptr<dogen::om::odb_option>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace om {

odb_options_file::odb_options_file(
    const boost::filesystem::path& full_path,
    const boost::filesystem::path& relative_path,
    const dogen::om::preamble& preamble,
    const boost::optional<dogen::om::code_generation_marker>& marker,
    const dogen::om::licence& licence,
    const std::list<boost::shared_ptr<dogen::om::odb_option> >& features)
    : dogen::om::text_file(full_path,
      relative_path,
      preamble,
      marker,
      licence),
      features_(features) { }

void odb_options_file::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::odb_options_file\"" << ", "
      << "\"__parent_0__\": ";
    text_file::to_stream(s);
    s << ", "
      << "\"features\": " << features_
      << " }";
}

void odb_options_file::swap(odb_options_file& other) noexcept {
    text_file::swap(other);

    using std::swap;
    swap(features_, other.features_);
}

bool odb_options_file::equals(const dogen::om::text_file& other) const {
    const odb_options_file* const p(dynamic_cast<const odb_options_file* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_options_file::operator==(const odb_options_file& rhs) const {
    return text_file::compare(rhs) &&
        features_ == rhs.features_;
}

odb_options_file& odb_options_file::operator=(odb_options_file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<boost::shared_ptr<dogen::om::odb_option> >& odb_options_file::features() const {
    return features_;
}

std::list<boost::shared_ptr<dogen::om::odb_option> >& odb_options_file::features() {
    return features_;
}

void odb_options_file::features(const std::list<boost::shared_ptr<dogen::om::odb_option> >& v) {
    features_ = v;
}

void odb_options_file::features(const std::list<boost::shared_ptr<dogen::om::odb_option> >&& v) {
    features_ = std::move(v);
}

} }