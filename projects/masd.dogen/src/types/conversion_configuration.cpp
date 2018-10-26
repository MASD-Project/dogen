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
#include "masd.dogen/types/conversion_configuration.hpp"

namespace masd::dogen {

conversion_configuration::conversion_configuration(conversion_configuration&& rhs)
    : output_directory_(std::move(rhs.output_directory_)),
      destination_type_(std::move(rhs.destination_type_)),
      destination_file_name_(std::move(rhs.destination_file_name_)) { }

conversion_configuration::conversion_configuration(
    const boost::filesystem::path& output_directory,
    const std::string& destination_type,
    const std::string& destination_file_name)
    : output_directory_(output_directory),
      destination_type_(destination_type),
      destination_file_name_(destination_file_name) { }

void conversion_configuration::swap(conversion_configuration& other) noexcept {
    using std::swap;
    swap(output_directory_, other.output_directory_);
    swap(destination_type_, other.destination_type_);
    swap(destination_file_name_, other.destination_file_name_);
}

bool conversion_configuration::operator==(const conversion_configuration& rhs) const {
    return output_directory_ == rhs.output_directory_ &&
        destination_type_ == rhs.destination_type_ &&
        destination_file_name_ == rhs.destination_file_name_;
}

conversion_configuration& conversion_configuration::operator=(conversion_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& conversion_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& conversion_configuration::output_directory() {
    return output_directory_;
}

conversion_configuration& conversion_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

conversion_configuration& conversion_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

const std::string& conversion_configuration::destination_type() const {
    return destination_type_;
}

std::string& conversion_configuration::destination_type() {
    return destination_type_;
}

conversion_configuration& conversion_configuration::destination_type(const std::string& v) {
    destination_type_ = v;
    return *this;
}

conversion_configuration& conversion_configuration::destination_type(const std::string&& v) {
    destination_type_ = std::move(v);
    return *this;
}

const std::string& conversion_configuration::destination_file_name() const {
    return destination_file_name_;
}

std::string& conversion_configuration::destination_file_name() {
    return destination_file_name_;
}

conversion_configuration& conversion_configuration::destination_file_name(const std::string& v) {
    destination_file_name_ = v;
    return *this;
}

conversion_configuration& conversion_configuration::destination_file_name(const std::string&& v) {
    destination_file_name_ = std::move(v);
    return *this;
}

}
