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
#include "dogen/cppim/types/feature.hpp"
#include "dogen/cppim/types/text_file.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::cppim::feature>& lhs,
const boost::shared_ptr<dogen::cppim::feature>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace cppim {

text_file::text_file(text_file&& rhs)
    : full_path_(std::move(rhs.full_path_)),
      relative_path_(std::move(rhs.relative_path_)),
      features_(std::move(rhs.features_)) { }

text_file::text_file(
    const boost::filesystem::path& full_path,
    const boost::filesystem::path& relative_path,
    const std::list<boost::shared_ptr<dogen::cppim::feature> >& features)
    : full_path_(full_path),
      relative_path_(relative_path),
      features_(features) { }

void text_file::swap(text_file& other) noexcept {
    using std::swap;
    swap(full_path_, other.full_path_);
    swap(relative_path_, other.relative_path_);
    swap(features_, other.features_);
}

bool text_file::operator==(const text_file& rhs) const {
    return full_path_ == rhs.full_path_ &&
        relative_path_ == rhs.relative_path_ &&
        features_ == rhs.features_;
}

text_file& text_file::operator=(text_file other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& text_file::full_path() const {
    return full_path_;
}

boost::filesystem::path& text_file::full_path() {
    return full_path_;
}

void text_file::full_path(const boost::filesystem::path& v) {
    full_path_ = v;
}

void text_file::full_path(const boost::filesystem::path&& v) {
    full_path_ = std::move(v);
}

const boost::filesystem::path& text_file::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& text_file::relative_path() {
    return relative_path_;
}

void text_file::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void text_file::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::cppim::feature> >& text_file::features() const {
    return features_;
}

std::list<boost::shared_ptr<dogen::cppim::feature> >& text_file::features() {
    return features_;
}

void text_file::features(const std::list<boost::shared_ptr<dogen::cppim::feature> >& v) {
    features_ = v;
}

void text_file::features(const std::list<boost::shared_ptr<dogen::cppim::feature> >&& v) {
    features_ = std::move(v);
}

} }