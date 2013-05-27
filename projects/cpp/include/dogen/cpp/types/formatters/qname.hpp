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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_QNAME_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_QNAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/parent_info.hpp"
#include "dogen/cpp/types/enum_info.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class qname {
public:
    qname() = delete;
    qname(const qname&) = default;
    ~qname() = default;
    qname(qname&&) = default;
    qname& operator=(const qname&) = default;

public:
    explicit qname(std::ostream& stream);

public:
    void format(const class_info& ci);
    void format(const enum_info& ei);
    void format(const parent_info& pi);

private:
    std::ostream& stream_;
};

} } }

#endif
