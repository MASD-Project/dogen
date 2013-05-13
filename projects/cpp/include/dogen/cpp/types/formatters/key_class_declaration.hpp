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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_KEY_CLASS_DECLARATION_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_KEY_CLASS_DECLARATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/cpp/types/formatters/class_declaration.hpp"
#include "dogen/cpp/types/class_info.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class key_class_declaration : public class_declaration {
public:
    key_class_declaration() = delete;
    key_class_declaration(const key_class_declaration&) = default;
    key_class_declaration(key_class_declaration&&) = default;
    key_class_declaration&
    operator=(const key_class_declaration&) = default;

public:
    key_class_declaration(std::ostream& stream,
        const bool disable_complete_constructor,
        const bool disable_io, const bool disable_serialization);
    virtual ~key_class_declaration() noexcept {}

private:
    void hand_crafted_constructors(const class_info& ci);

public:
    virtual void format(const class_info& ci) override;

private:
    const bool disable_complete_constructor_;
    const bool disable_io_;
};

} } }

#endif
