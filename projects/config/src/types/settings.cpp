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
#include "dogen/config/types/settings.hpp"

namespace dogen {
namespace config {

settings::settings()
    : verbose_(static_cast<bool>(0)) { }

settings::settings(
    const dogen::config::modeling_settings& modeling,
    const dogen::config::cpp_settings& cpp,
    const dogen::config::troubleshooting_settings& troubleshooting,
    const dogen::config::output_settings& output,
    const dogen::config::annotation_settings& annotation,
    const bool verbose)
    : modeling_(modeling),
      cpp_(cpp),
      troubleshooting_(troubleshooting),
      output_(output),
      annotation_(annotation),
      verbose_(verbose) { }

void settings::swap(settings& other) noexcept {
    using std::swap;
    swap(modeling_, other.modeling_);
    swap(cpp_, other.cpp_);
    swap(troubleshooting_, other.troubleshooting_);
    swap(output_, other.output_);
    swap(annotation_, other.annotation_);
    swap(verbose_, other.verbose_);
}

bool settings::operator==(const settings& rhs) const {
    return modeling_ == rhs.modeling_ &&
        cpp_ == rhs.cpp_ &&
        troubleshooting_ == rhs.troubleshooting_ &&
        output_ == rhs.output_ &&
        annotation_ == rhs.annotation_ &&
        verbose_ == rhs.verbose_;
}

settings& settings::operator=(settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::config::modeling_settings& settings::modeling() const {
    return modeling_;
}

dogen::config::modeling_settings& settings::modeling() {
    return modeling_;
}

void settings::modeling(const dogen::config::modeling_settings& v) {
    modeling_ = v;
}

void settings::modeling(const dogen::config::modeling_settings&& v) {
    modeling_ = std::move(v);
}

const dogen::config::cpp_settings& settings::cpp() const {
    return cpp_;
}

dogen::config::cpp_settings& settings::cpp() {
    return cpp_;
}

void settings::cpp(const dogen::config::cpp_settings& v) {
    cpp_ = v;
}

void settings::cpp(const dogen::config::cpp_settings&& v) {
    cpp_ = std::move(v);
}

const dogen::config::troubleshooting_settings& settings::troubleshooting() const {
    return troubleshooting_;
}

dogen::config::troubleshooting_settings& settings::troubleshooting() {
    return troubleshooting_;
}

void settings::troubleshooting(const dogen::config::troubleshooting_settings& v) {
    troubleshooting_ = v;
}

void settings::troubleshooting(const dogen::config::troubleshooting_settings&& v) {
    troubleshooting_ = std::move(v);
}

const dogen::config::output_settings& settings::output() const {
    return output_;
}

dogen::config::output_settings& settings::output() {
    return output_;
}

void settings::output(const dogen::config::output_settings& v) {
    output_ = v;
}

void settings::output(const dogen::config::output_settings&& v) {
    output_ = std::move(v);
}

const dogen::config::annotation_settings& settings::annotation() const {
    return annotation_;
}

dogen::config::annotation_settings& settings::annotation() {
    return annotation_;
}

void settings::annotation(const dogen::config::annotation_settings& v) {
    annotation_ = v;
}

void settings::annotation(const dogen::config::annotation_settings&& v) {
    annotation_ = std::move(v);
}

bool settings::verbose() const {
    return verbose_;
}

void settings::verbose(const bool v) {
    verbose_ = v;
}

} }