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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_ARTEFACT_FORMATTER_INTERFACE_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_ARTEFACT_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

class artefact_formatter_interface {
public:
    artefact_formatter_interface() = default;
    artefact_formatter_interface(const artefact_formatter_interface&) = default;
    artefact_formatter_interface(artefact_formatter_interface&&) = default;
    artefact_formatter_interface& operator=(const artefact_formatter_interface&) = default;

    virtual ~artefact_formatter_interface() noexcept = 0;

protected:
    bool compare(const artefact_formatter_interface& rhs) const;
public:
    virtual bool equals(const artefact_formatter_interface& other) const = 0;

protected:
    void swap(artefact_formatter_interface& other) noexcept;

};

inline artefact_formatter_interface::~artefact_formatter_interface() noexcept { }

inline bool operator==(const artefact_formatter_interface& lhs, const artefact_formatter_interface& rhs) {
    return lhs.equals(rhs);
}

} } } }

#endif
