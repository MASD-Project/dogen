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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_ELEMENT_FORMATTER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_ELEMENT_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include "dogen/formatters/types/file.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/context_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class element_formatter final {
public:
    element_formatter(const context_factory& f, const container& c);

private:
    std::forward_list<dogen::formatters::file> format(
        const std::forward_list<std::shared_ptr<file_formatter_interface>>&
        formatters, const yarn::element& e) const;

public:
    std::forward_list<dogen::formatters::file>
    format(const yarn::element& e) const;

private:
    const context_factory factory_;
    const container& container_;
};

} } } }

#endif
