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
#include "dogen/config/types/formatting_settings.hpp"

namespace dogen {
namespace config {

formatting_settings::formatting_settings()
    : disable_model_module_(static_cast<bool>(0)) { }

formatting_settings::formatting_settings(
    const dogen::config::cpp_settings& cpp,
    const dogen::config::annotation_settings& annotation,
    const bool disable_model_module)
    : cpp_(cpp),
      annotation_(annotation),
      disable_model_module_(disable_model_module) { }

void formatting_settings::swap(formatting_settings& other) noexcept {
    using std::swap;
    swap(cpp_, other.cpp_);
    swap(annotation_, other.annotation_);
    swap(disable_model_module_, other.disable_model_module_);
}

bool formatting_settings::operator==(const formatting_settings& rhs) const {
    return cpp_ == rhs.cpp_ &&
        annotation_ == rhs.annotation_ &&
        disable_model_module_ == rhs.disable_model_module_;
}

formatting_settings& formatting_settings::operator=(formatting_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::config::cpp_settings& formatting_settings::cpp() const {
    return cpp_;
}

dogen::config::cpp_settings& formatting_settings::cpp() {
    return cpp_;
}

void formatting_settings::cpp(const dogen::config::cpp_settings& v) {
    cpp_ = v;
}

void formatting_settings::cpp(const dogen::config::cpp_settings&& v) {
    cpp_ = std::move(v);
}

const dogen::config::annotation_settings& formatting_settings::annotation() const {
    return annotation_;
}

dogen::config::annotation_settings& formatting_settings::annotation() {
    return annotation_;
}

void formatting_settings::annotation(const dogen::config::annotation_settings& v) {
    annotation_ = v;
}

void formatting_settings::annotation(const dogen::config::annotation_settings&& v) {
    annotation_ = std::move(v);
}

bool formatting_settings::disable_model_module() const {
    return disable_model_module_;
}

void formatting_settings::disable_model_module(const bool v) {
    disable_model_module_ = v;
}

} }