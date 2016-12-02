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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_REPOSITORY_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <algorithm>
#include <typeindex>
#include <forward_list>
#include <unordered_map>
#include "dogen/quilt.csharp/types/formatters/artefact_formatter_interface_fwd.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

class repository final {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() = default;

public:
    explicit repository(const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& stock_artefact_formatters_by_type_index);

public:
    const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& stock_artefact_formatters_by_type_index() const;
    std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& stock_artefact_formatters_by_type_index();
    void stock_artefact_formatters_by_type_index(const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >& v);
    void stock_artefact_formatters_by_type_index(const std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > >&& v);

public:
    bool operator==(const repository& rhs) const;
    bool operator!=(const repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(repository& other) noexcept;
    repository& operator=(repository other);

private:
    std::unordered_map<std::type_index, std::forward_list<std::shared_ptr<dogen::quilt::csharp::formatters::artefact_formatter_interface> > > stock_artefact_formatters_by_type_index_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::csharp::formatters::repository& lhs,
    dogen::quilt::csharp::formatters::repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
