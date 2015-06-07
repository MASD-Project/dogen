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
#include "dogen/config/types/knitting_options.hpp"

namespace dogen {
namespace config {

knitting_options::knitting_options()
    : verbose_(static_cast<bool>(0)) { }

knitting_options::knitting_options(
    const bool verbose,
    const dogen::config::input_options& input,
    const dogen::config::troubleshooting_options& troubleshooting,
    const dogen::config::output_options& output,
    const dogen::config::cpp_options& cpp)
    : verbose_(verbose),
      input_(input),
      troubleshooting_(troubleshooting),
      output_(output),
      cpp_(cpp) { }

void knitting_options::swap(knitting_options& other) noexcept {
    using std::swap;
    swap(verbose_, other.verbose_);
    swap(input_, other.input_);
    swap(troubleshooting_, other.troubleshooting_);
    swap(output_, other.output_);
    swap(cpp_, other.cpp_);
}

bool knitting_options::operator==(const knitting_options& rhs) const {
    return verbose_ == rhs.verbose_ &&
        input_ == rhs.input_ &&
        troubleshooting_ == rhs.troubleshooting_ &&
        output_ == rhs.output_ &&
        cpp_ == rhs.cpp_;
}

knitting_options& knitting_options::operator=(knitting_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool knitting_options::verbose() const {
    return verbose_;
}

void knitting_options::verbose(const bool v) {
    verbose_ = v;
}

const dogen::config::input_options& knitting_options::input() const {
    return input_;
}

dogen::config::input_options& knitting_options::input() {
    return input_;
}

void knitting_options::input(const dogen::config::input_options& v) {
    input_ = v;
}

void knitting_options::input(const dogen::config::input_options&& v) {
    input_ = std::move(v);
}

const dogen::config::troubleshooting_options& knitting_options::troubleshooting() const {
    return troubleshooting_;
}

dogen::config::troubleshooting_options& knitting_options::troubleshooting() {
    return troubleshooting_;
}

void knitting_options::troubleshooting(const dogen::config::troubleshooting_options& v) {
    troubleshooting_ = v;
}

void knitting_options::troubleshooting(const dogen::config::troubleshooting_options&& v) {
    troubleshooting_ = std::move(v);
}

const dogen::config::output_options& knitting_options::output() const {
    return output_;
}

dogen::config::output_options& knitting_options::output() {
    return output_;
}

void knitting_options::output(const dogen::config::output_options& v) {
    output_ = v;
}

void knitting_options::output(const dogen::config::output_options&& v) {
    output_ = std::move(v);
}

const dogen::config::cpp_options& knitting_options::cpp() const {
    return cpp_;
}

dogen::config::cpp_options& knitting_options::cpp() {
    return cpp_;
}

void knitting_options::cpp(const dogen::config::cpp_options& v) {
    cpp_ = v;
}

void knitting_options::cpp(const dogen::config::cpp_options&& v) {
    cpp_ = std::move(v);
}

} }
