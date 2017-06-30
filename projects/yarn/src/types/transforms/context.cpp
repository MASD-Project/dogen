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
#include "dogen/yarn/types/transforms/context.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

context::context(
    const std::vector<boost::filesystem::path>& data_directories,
    const dogen::annotations::type_repository& type_repository,
    const dogen::options::knitting_options& options)
    : data_directories_(data_directories),
      type_repository_(type_repository),
      options_(options) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(data_directories_, other.data_directories_);
    swap(type_repository_, other.type_repository_);
    swap(options_, other.options_);
}

bool context::operator==(const context& rhs) const {
    return data_directories_ == rhs.data_directories_ &&
        type_repository_ == rhs.type_repository_ &&
        options_ == rhs.options_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

std::vector<boost::filesystem::path>& context::data_directories() {
    return data_directories_;
}

void context::data_directories(const std::vector<boost::filesystem::path>& v) {
    data_directories_ = v;
}

void context::data_directories(const std::vector<boost::filesystem::path>&& v) {
    data_directories_ = std::move(v);
}

const dogen::annotations::type_repository& context::type_repository() const {
    return type_repository_;
}

dogen::annotations::type_repository& context::type_repository() {
    return type_repository_;
}

void context::type_repository(const dogen::annotations::type_repository& v) {
    type_repository_ = v;
}

void context::type_repository(const dogen::annotations::type_repository&& v) {
    type_repository_ = std::move(v);
}

const dogen::options::knitting_options& context::options() const {
    return options_;
}

dogen::options::knitting_options& context::options() {
    return options_;
}

void context::options(const dogen::options::knitting_options& v) {
    options_ = v;
}

void context::options(const dogen::options::knitting_options&& v) {
    options_ = std::move(v);
}

} } }
