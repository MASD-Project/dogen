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
#include <boost/algorithm/string.hpp>
#include <ostream>
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/types/cpp_ifdef.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
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

cpp_ifdef::cpp_ifdef(
    const std::string& name,
    const std::string& condition,
    const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features)
    : dogen::om::cpp_feature(name),
      condition_(condition),
      features_(features) { }

void cpp_ifdef::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_ifdef\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"condition\": " << "\"" << tidy_up_string(condition_) << "\"" << ", "
      << "\"features\": " << features_
      << " }";
}

void cpp_ifdef::swap(cpp_ifdef& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(condition_, other.condition_);
    swap(features_, other.features_);
}

bool cpp_ifdef::equals(const dogen::om::cpp_feature& other) const {
    const cpp_ifdef* const p(dynamic_cast<const cpp_ifdef* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_ifdef::operator==(const cpp_ifdef& rhs) const {
    return cpp_feature::compare(rhs) &&
        condition_ == rhs.condition_ &&
        features_ == rhs.features_;
}

cpp_ifdef& cpp_ifdef::operator=(cpp_ifdef other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cpp_ifdef::condition() const {
    return condition_;
}

std::string& cpp_ifdef::condition() {
    return condition_;
}

void cpp_ifdef::condition(const std::string& v) {
    condition_ = v;
}

void cpp_ifdef::condition(const std::string&& v) {
    condition_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& cpp_ifdef::features() const {
    return features_;
}

std::list<boost::shared_ptr<dogen::om::cpp_feature> >& cpp_ifdef::features() {
    return features_;
}

void cpp_ifdef::features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v) {
    features_ = v;
}

void cpp_ifdef::features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >&& v) {
    features_ = std::move(v);
}

} }