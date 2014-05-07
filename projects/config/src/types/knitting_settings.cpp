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
#include "dogen/config/types/knitting_settings.hpp"

namespace dogen {
namespace config {

knitting_settings::knitting_settings()
    : verbose_(static_cast<bool>(0)) { }

knitting_settings::knitting_settings(
    const bool verbose,
    const dogen::config::input_settings& input,
    const dogen::config::troubleshooting_settings& troubleshooting,
    const dogen::config::output_settings& output,
    const dogen::config::cpp_settings& cpp)
    : verbose_(verbose),
      input_(input),
      troubleshooting_(troubleshooting),
      output_(output),
      cpp_(cpp) { }

void knitting_settings::swap(knitting_settings& other) noexcept {
    using std::swap;
    swap(verbose_, other.verbose_);
    swap(input_, other.input_);
    swap(troubleshooting_, other.troubleshooting_);
    swap(output_, other.output_);
    swap(cpp_, other.cpp_);
}

bool knitting_settings::operator==(const knitting_settings& rhs) const {
    return verbose_ == rhs.verbose_ &&
        input_ == rhs.input_ &&
        troubleshooting_ == rhs.troubleshooting_ &&
        output_ == rhs.output_ &&
        cpp_ == rhs.cpp_;
}

knitting_settings& knitting_settings::operator=(knitting_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool knitting_settings::verbose() const {
    return verbose_;
}

void knitting_settings::verbose(const bool v) {
    verbose_ = v;
}

const dogen::config::input_settings& knitting_settings::input() const {
    return input_;
}

dogen::config::input_settings& knitting_settings::input() {
    return input_;
}

void knitting_settings::input(const dogen::config::input_settings& v) {
    input_ = v;
}

void knitting_settings::input(const dogen::config::input_settings&& v) {
    input_ = std::move(v);
}

const dogen::config::troubleshooting_settings& knitting_settings::troubleshooting() const {
    return troubleshooting_;
}

dogen::config::troubleshooting_settings& knitting_settings::troubleshooting() {
    return troubleshooting_;
}

void knitting_settings::troubleshooting(const dogen::config::troubleshooting_settings& v) {
    troubleshooting_ = v;
}

void knitting_settings::troubleshooting(const dogen::config::troubleshooting_settings&& v) {
    troubleshooting_ = std::move(v);
}

const dogen::config::output_settings& knitting_settings::output() const {
    return output_;
}

dogen::config::output_settings& knitting_settings::output() {
    return output_;
}

void knitting_settings::output(const dogen::config::output_settings& v) {
    output_ = v;
}

void knitting_settings::output(const dogen::config::output_settings&& v) {
    output_ = std::move(v);
}

const dogen::config::cpp_settings& knitting_settings::cpp() const {
    return cpp_;
}

dogen::config::cpp_settings& knitting_settings::cpp() {
    return cpp_;
}

void knitting_settings::cpp(const dogen::config::cpp_settings& v) {
    cpp_ = v;
}

void knitting_settings::cpp(const dogen::config::cpp_settings&& v) {
    cpp_ = std::move(v);
}

} }