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
#include "dogen/om/io/licence_io.hpp"
#include "dogen/om/io/preamble_io.hpp"
#include "dogen/om/types/text_file.hpp"

namespace dogen {
namespace om {

text_file::text_file(text_file&& rhs)
    : full_path_(std::move(rhs.full_path_)),
      relative_path_(std::move(rhs.relative_path_)),
      preamble_(std::move(rhs.preamble_)),
      licence_(std::move(rhs.licence_)) { }

text_file::text_file(
    const boost::filesystem::path& full_path,
    const boost::filesystem::path& relative_path,
    const dogen::om::preamble& preamble,
    const dogen::om::licence& licence)
    : full_path_(full_path),
      relative_path_(relative_path),
      preamble_(preamble),
      licence_(licence) { }

void text_file::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::text_file\"" << ", "
      << "\"full_path\": " << "\"" << full_path_.generic_string() << "\"" << ", "
      << "\"relative_path\": " << "\"" << relative_path_.generic_string() << "\"" << ", "
      << "\"preamble\": " << preamble_ << ", "
      << "\"licence\": " << licence_
      << " }";
}

void text_file::swap(text_file& other) noexcept {
    using std::swap;
    swap(full_path_, other.full_path_);
    swap(relative_path_, other.relative_path_);
    swap(preamble_, other.preamble_);
    swap(licence_, other.licence_);
}

bool text_file::compare(const text_file& rhs) const {
    return full_path_ == rhs.full_path_ &&
        relative_path_ == rhs.relative_path_ &&
        preamble_ == rhs.preamble_ &&
        licence_ == rhs.licence_;
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

const dogen::om::preamble& text_file::preamble() const {
    return preamble_;
}

dogen::om::preamble& text_file::preamble() {
    return preamble_;
}

void text_file::preamble(const dogen::om::preamble& v) {
    preamble_ = v;
}

void text_file::preamble(const dogen::om::preamble&& v) {
    preamble_ = std::move(v);
}

const dogen::om::licence& text_file::licence() const {
    return licence_;
}

dogen::om::licence& text_file::licence() {
    return licence_;
}

void text_file::licence(const dogen::om::licence& v) {
    licence_ = v;
}

void text_file::licence(const dogen::om::licence&& v) {
    licence_ = std::move(v);
}

} }