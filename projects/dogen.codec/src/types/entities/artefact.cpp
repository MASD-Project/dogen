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
#include "dogen.codec/types/entities/artefact.hpp"

namespace dogen::codec::entities {

artefact::artefact(artefact&& rhs)
    : path_(std::move(rhs.path_)),
      codec_name_(std::move(rhs.codec_name_)),
      content_(std::move(rhs.content_)) { }

artefact::artefact(
    const boost::filesystem::path& path,
    const std::string& codec_name,
    const std::string& content)
    : path_(path),
      codec_name_(codec_name),
      content_(content) { }

void artefact::swap(artefact& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
    swap(codec_name_, other.codec_name_);
    swap(content_, other.content_);
}

bool artefact::operator==(const artefact& rhs) const {
    return path_ == rhs.path_ &&
        codec_name_ == rhs.codec_name_ &&
        content_ == rhs.content_;
}

artefact& artefact::operator=(artefact other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& artefact::path() const {
    return path_;
}

boost::filesystem::path& artefact::path() {
    return path_;
}

void artefact::path(const boost::filesystem::path& v) {
    path_ = v;
}

void artefact::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

const std::string& artefact::codec_name() const {
    return codec_name_;
}

std::string& artefact::codec_name() {
    return codec_name_;
}

void artefact::codec_name(const std::string& v) {
    codec_name_ = v;
}

void artefact::codec_name(const std::string&& v) {
    codec_name_ = std::move(v);
}

const std::string& artefact::content() const {
    return content_;
}

std::string& artefact::content() {
    return content_;
}

void artefact::content(const std::string& v) {
    content_ = v;
}

void artefact::content(const std::string&& v) {
    content_ = std::move(v);
}

}
