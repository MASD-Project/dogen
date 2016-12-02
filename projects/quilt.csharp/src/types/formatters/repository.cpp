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
#include "dogen/quilt.csharp/types/formatters/repository.hpp"
#include "dogen/quilt.csharp/types/formatters/artefact_formatter_interface.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface>& lhs,
const std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

repository::repository(const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& stock_artefact_formatters_by_type_index)
    : stock_artefact_formatters_by_type_index_(stock_artefact_formatters_by_type_index) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(stock_artefact_formatters_by_type_index_, other.stock_artefact_formatters_by_type_index_);
}

bool repository::operator==(const repository& rhs) const {
    return stock_artefact_formatters_by_type_index_ == rhs.stock_artefact_formatters_by_type_index_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& repository::stock_artefact_formatters_by_type_index() const {
    return stock_artefact_formatters_by_type_index_;
}

std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& repository::stock_artefact_formatters_by_type_index() {
    return stock_artefact_formatters_by_type_index_;
}

void repository::stock_artefact_formatters_by_type_index(const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& v) {
    stock_artefact_formatters_by_type_index_ = v;
}

void repository::stock_artefact_formatters_by_type_index(const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >&& v) {
    stock_artefact_formatters_by_type_index_ = std::move(v);
}

} } } }
