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
#include "dogen/tack/types/preprocessing_settings.hpp"

namespace dogen {
namespace tack {

preprocessing_settings::preprocessing_settings(preprocessing_settings&& rhs)
    : directory_(std::move(rhs.directory_)),
      extension_(std::move(rhs.extension_)) { }

preprocessing_settings::preprocessing_settings(
    const boost::filesystem::path& directory,
    const std::string& extension)
    : directory_(directory),
      extension_(extension) { }

void preprocessing_settings::swap(preprocessing_settings& other) noexcept {
    using std::swap;
    swap(directory_, other.directory_);
    swap(extension_, other.extension_);
}

bool preprocessing_settings::operator==(const preprocessing_settings& rhs) const {
    return directory_ == rhs.directory_ &&
        extension_ == rhs.extension_;
}

preprocessing_settings& preprocessing_settings::operator=(preprocessing_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& preprocessing_settings::directory() const {
    return directory_;
}

boost::filesystem::path& preprocessing_settings::directory() {
    return directory_;
}

void preprocessing_settings::directory(const boost::filesystem::path& v) {
    directory_ = v;
}

void preprocessing_settings::directory(const boost::filesystem::path&& v) {
    directory_ = std::move(v);
}

const std::string& preprocessing_settings::extension() const {
    return extension_;
}

std::string& preprocessing_settings::extension() {
    return extension_;
}

void preprocessing_settings::extension(const std::string& v) {
    extension_ = v;
}

void preprocessing_settings::extension(const std::string&& v) {
    extension_ = std::move(v);
}

} }
