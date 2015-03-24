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
#include "dogen/dynamic/expansion/types/expansion_context.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

expansion_context::expansion_context(
    const dogen::sml::model& model,
    const dogen::dynamic::schema::repository& repository,
    const dogen::config::cpp_options& cpp_options)
    : model_(model),
      repository_(repository),
      cpp_options_(cpp_options) { }

void expansion_context::swap(expansion_context& other) noexcept {
    using std::swap;
    swap(model_, other.model_);
    swap(repository_, other.repository_);
    swap(cpp_options_, other.cpp_options_);
}

bool expansion_context::operator==(const expansion_context& rhs) const {
    return model_ == rhs.model_ &&
        repository_ == rhs.repository_ &&
        cpp_options_ == rhs.cpp_options_;
}

expansion_context& expansion_context::operator=(expansion_context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::model& expansion_context::model() const {
    return model_;
}

dogen::sml::model& expansion_context::model() {
    return model_;
}

void expansion_context::model(const dogen::sml::model& v) {
    model_ = v;
}

void expansion_context::model(const dogen::sml::model&& v) {
    model_ = std::move(v);
}

const dogen::dynamic::schema::repository& expansion_context::repository() const {
    return repository_;
}

dogen::dynamic::schema::repository& expansion_context::repository() {
    return repository_;
}

void expansion_context::repository(const dogen::dynamic::schema::repository& v) {
    repository_ = v;
}

void expansion_context::repository(const dogen::dynamic::schema::repository&& v) {
    repository_ = std::move(v);
}

const dogen::config::cpp_options& expansion_context::cpp_options() const {
    return cpp_options_;
}

dogen::config::cpp_options& expansion_context::cpp_options() {
    return cpp_options_;
}

void expansion_context::cpp_options(const dogen::config::cpp_options& v) {
    cpp_options_ = v;
}

void expansion_context::cpp_options(const dogen::config::cpp_options&& v) {
    cpp_options_ = std::move(v);
}

} } }