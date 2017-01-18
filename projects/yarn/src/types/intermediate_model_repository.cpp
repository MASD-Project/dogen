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
#include "dogen/yarn/types/intermediate_model_repository.hpp"

namespace dogen {
namespace yarn {

intermediate_model_repository::intermediate_model_repository(const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& by_language)
    : by_language_(by_language) { }

void intermediate_model_repository::swap(intermediate_model_repository& other) noexcept {
    using std::swap;
    swap(by_language_, other.by_language_);
}

bool intermediate_model_repository::operator==(const intermediate_model_repository& rhs) const {
    return by_language_ == rhs.by_language_;
}

intermediate_model_repository& intermediate_model_repository::operator=(intermediate_model_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& intermediate_model_repository::by_language() const {
    return by_language_;
}

std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& intermediate_model_repository::by_language() {
    return by_language_;
}

void intermediate_model_repository::by_language(const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >& v) {
    by_language_ = v;
}

void intermediate_model_repository::by_language(const std::unordered_map<dogen::yarn::languages, std::list<dogen::yarn::intermediate_model> >&& v) {
    by_language_ = std::move(v);
}

} }
