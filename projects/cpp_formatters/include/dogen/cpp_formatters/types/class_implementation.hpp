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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_CLASS_IMPLEMENTATION_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_CLASS_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
types/#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"

namespace dogen {
namespace cpp_formatters {

class class_implementation {
public:
    class_implementation() = default;
    class_implementation(const class_implementation&) = default;
    ~class_implementation() = default;
    class_implementation(class_implementation&&) = default;
    class_implementation&
    operator=(const class_implementation&) = default;

public:
    explicit class_implementation(std::ostream& stream);

private:
    void non_object_getters_and_setters(const std::string class_name,
        const cpp::formattables::property_info& pi);
    void object_getters_and_setters(const std::string class_name,
        const cpp::formattables::property_info& pi);

protected:
    void default_constructor(const cpp::formattables::class_info& ci);
    void move_constructor(const cpp::formattables::class_info& ci);
    void complete_constructor(const cpp::formattables::class_info& ci);
    void to_stream(const cpp::formattables::class_info& ci);
    void swap(const cpp::formattables::class_info& ci);
    void equals_method(const cpp::formattables::class_info& ci);
    void equals_operator(const cpp::formattables::class_info& ci);
    void assignment_operator(const cpp::formattables::class_info& ci);
    void getters_and_setters(const cpp::formattables::class_info& ci);

public:
    virtual void format(const cpp::formattables::class_info& ci) = 0;

protected:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};

} }

#endif
