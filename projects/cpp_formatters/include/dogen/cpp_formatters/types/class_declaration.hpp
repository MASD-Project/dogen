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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_CLASS_DECLARATION_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_CLASS_DECLARATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/property_info.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"

namespace dogen {
namespace cpp_formatters {

class class_declaration {
public:
    class_declaration() = delete;
    class_declaration(const class_declaration&) = default;
    class_declaration(class_declaration&&) = default;
    class_declaration& operator=(const class_declaration&) = default;
    ~class_declaration() noexcept = default;

public:
    class_declaration(std::ostream& stream,
        const bool disable_serialization,
        const bool disable_complete_constructor,
        const bool disable_io);

private:
    void non_object_getters_and_setters(const std::string class_name,
        const cpp::property_info& pi);
    void object_getters_and_setters(const std::string class_name,
        const cpp::property_info& pi);

    void open_class(const cpp::class_info& ci);
    void close_class();

    void hand_crafted_constructors(const cpp::class_info& ci);
    void visitor_method(const cpp::class_info& ci);
    void compiler_generated_constuctors(const cpp::class_info& ci);
    void default_constructor(const cpp::class_info& ci);
    void move_constructor(const cpp::class_info& ci);
    void complete_constructor(const cpp::class_info& ci);
    void destructor(const cpp::class_info& ci);
    void friends(const cpp::class_info& ci);
    void getters_and_setters(const cpp::class_info& ci);
    void member_variables(const cpp::class_info& ci);
    void equality(const cpp::class_info& ci);
    void to_stream(const cpp::class_info& ci);
    void swap_and_assignment(const cpp::class_info& ci);

public:
    void format(const cpp::class_info& ci);

protected:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
    const bool disable_serialization_;
    const bool disable_complete_constructor_;
    const bool disable_io_;
};

} }

#endif
