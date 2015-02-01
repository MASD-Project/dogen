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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_DOMAIN_CLASS_IMPLEMENTATION_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_DOMAIN_CLASS_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cpp_formatters/types/class_implementation.hpp"

namespace dogen {
namespace cpp_formatters {

class domain_class_implementation : public class_implementation {
public:
    domain_class_implementation() = delete;
    domain_class_implementation(
        const domain_class_implementation&) = default;
    domain_class_implementation(
        domain_class_implementation&&) = default;
    domain_class_implementation&
    operator=(const domain_class_implementation&) = default;

private:
    void hand_crafted_constructors(const cpp::formattables::class_info& ci);

public:
    domain_class_implementation(std::ostream& stream,
        bool disable_complete_constructor, bool disable_io);
    virtual ~domain_class_implementation() noexcept {}

public:
    virtual void format(const cpp::formattables::class_info& ci) override;

private:
    const bool disable_complete_constructor_;
    const bool disable_io_;
};

} }

#endif
