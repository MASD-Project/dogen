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
#include "dogen/options/types/knitting_options.hpp"

namespace dogen {
namespace options {

knitting_options::knitting_options()
    : verbose_(static_cast<bool>(0)) { }

knitting_options::knitting_options(
    const bool verbose,
    const dogen::options::input_options& input,
    const dogen::options::output_options& output,
    const dogen::options::cpp_options& cpp)
    : verbose_(verbose),
      input_(input),
      output_(output),
      cpp_(cpp) { }

void knitting_options::swap(knitting_options& other) noexcept {
    using std::swap;
    swap(verbose_, other.verbose_);
    swap(input_, other.input_);
    swap(output_, other.output_);
    swap(cpp_, other.cpp_);
}

bool knitting_options::operator==(const knitting_options& rhs) const {
    return verbose_ == rhs.verbose_ &&
        input_ == rhs.input_ &&
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

const dogen::options::input_options& knitting_options::input() const {
    return input_;
}

dogen::options::input_options& knitting_options::input() {
    return input_;
}

void knitting_options::input(const dogen::options::input_options& v) {
    input_ = v;
}

void knitting_options::input(const dogen::options::input_options&& v) {
    input_ = std::move(v);
}

const dogen::options::output_options& knitting_options::output() const {
    return output_;
}

dogen::options::output_options& knitting_options::output() {
    return output_;
}

void knitting_options::output(const dogen::options::output_options& v) {
    output_ = v;
}

void knitting_options::output(const dogen::options::output_options&& v) {
    output_ = std::move(v);
}

const dogen::options::cpp_options& knitting_options::cpp() const {
    return cpp_;
}

dogen::options::cpp_options& knitting_options::cpp() {
    return cpp_;
}

void knitting_options::cpp(const dogen::options::cpp_options& v) {
    cpp_ = v;
}

void knitting_options::cpp(const dogen::options::cpp_options&& v) {
    cpp_ = std::move(v);
}

} }
