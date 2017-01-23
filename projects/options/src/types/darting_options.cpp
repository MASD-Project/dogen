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
#include "dogen/options/types/darting_options.hpp"

namespace dogen {
namespace options {

darting_options::darting_options()
    : force_write_(static_cast<bool>(0)) { }

darting_options::darting_options(
    const std::string& log_level,
    const bool force_write,
    const std::string& product_name)
    : log_level_(log_level),
      force_write_(force_write),
      product_name_(product_name) { }

void darting_options::swap(darting_options& other) noexcept {
    using std::swap;
    swap(log_level_, other.log_level_);
    swap(force_write_, other.force_write_);
    swap(product_name_, other.product_name_);
}

bool darting_options::operator==(const darting_options& rhs) const {
    return log_level_ == rhs.log_level_ &&
        force_write_ == rhs.force_write_ &&
        product_name_ == rhs.product_name_;
}

darting_options& darting_options::operator=(darting_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& darting_options::log_level() const {
    return log_level_;
}

std::string& darting_options::log_level() {
    return log_level_;
}

void darting_options::log_level(const std::string& v) {
    log_level_ = v;
}

void darting_options::log_level(const std::string&& v) {
    log_level_ = std::move(v);
}

bool darting_options::force_write() const {
    return force_write_;
}

void darting_options::force_write(const bool v) {
    force_write_ = v;
}

const std::string& darting_options::product_name() const {
    return product_name_;
}

std::string& darting_options::product_name() {
    return product_name_;
}

void darting_options::product_name(const std::string& v) {
    product_name_ = v;
}

void darting_options::product_name(const std::string&& v) {
    product_name_ = std::move(v);
}

} }
