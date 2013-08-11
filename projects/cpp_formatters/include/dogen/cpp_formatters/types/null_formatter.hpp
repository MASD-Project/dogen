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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_NULL_FORMATTER_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_NULL_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/cpp/types/source_file.hpp"
#include "dogen/cpp_formatters/types/file_formatter.hpp"

namespace dogen {
namespace cpp_formatters {

class null_formatter : public file_formatter {
public:
    null_formatter() = default;
    null_formatter(const null_formatter&) = default;
    null_formatter(null_formatter&&) = default;
    null_formatter& operator=(const null_formatter&) = default;

public:
    virtual ~null_formatter() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

public:
    virtual void format(const cpp::source_file& f) override;
};

} }

#endif
