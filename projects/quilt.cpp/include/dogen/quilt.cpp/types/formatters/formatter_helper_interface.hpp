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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_FORMATTER_HELPER_INTERFACE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_FORMATTER_HELPER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant_fwd.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class formatter_helper_interface {
public:
    formatter_helper_interface() = default;
    formatter_helper_interface(const formatter_helper_interface&) = delete;
    formatter_helper_interface(formatter_helper_interface&&) = default;
    virtual ~formatter_helper_interface() noexcept = 0;

public:
    virtual std::string family() const = 0;
    virtual std::string owning_formatter() const = 0;
    virtual bool requires_explicit_call() const = 0;
    virtual std::string function_name() const = 0;
    virtual std::string helper_name() const = 0;
    virtual bool is_enabled(const assistant& a) const = 0;
    virtual void format(assistant& a, const yarn::name_tree& nt) const = 0;
};

} } } }

#endif
