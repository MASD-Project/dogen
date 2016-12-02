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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_REGISTRAR_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/quilt.csharp/types/formatters/repository.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

class registrar final {
public:
    registrar() = default;
    registrar(const registrar&) = default;
    registrar(registrar&&) = default;
    ~registrar() = default;

public:
    explicit registrar(const dogen::quilt::csharp::formatters::repository& formatter_repository_);

public:
    const dogen::quilt::csharp::formatters::repository& formatter_repository_() const;
    dogen::quilt::csharp::formatters::repository& formatter_repository_();
    void formatter_repository_(const dogen::quilt::csharp::formatters::repository& v);
    void formatter_repository_(const dogen::quilt::csharp::formatters::repository&& v);

public:
    bool operator==(const registrar& rhs) const;
    bool operator!=(const registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(registrar& other) noexcept;
    registrar& operator=(registrar other);

private:
    dogen::quilt::csharp::formatters::repository formatter_repository__;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::csharp::formatters::registrar& lhs,
    dogen::quilt::csharp::formatters::registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
