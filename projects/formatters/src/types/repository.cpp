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
#include "dogen/formatters/types/repository.hpp"

namespace dogen {
namespace formatters {

void repository::clear() {
    file_formatters_.clear();
    transformers_.clear();
}

bool repository::empty() const {
    return file_formatters_.empty() && transformers_.empty();
}

const repository::file_formatters_type& repository::file_formatters() const {
    return file_formatters_;
}

repository::file_formatters_type& repository::file_formatters() {
    return file_formatters_;
}

void repository::file_formatters(const repository::file_formatters_type& v) {
    file_formatters_ = v;
}

void repository::file_formatters(const repository::file_formatters_type&& v) {
    file_formatters_ = std::move(v);
}

const repository::transformers_type& repository::transformers() const {
    return transformers_;
}

repository::transformers_type& repository::transformers() {
    return transformers_;
}

void repository::transformers(const repository::transformers_type& v) {
    transformers_ = v;
}

void repository::transformers(const repository::transformers_type&& v) {
    transformers_ = std::move(v);
}

} }
