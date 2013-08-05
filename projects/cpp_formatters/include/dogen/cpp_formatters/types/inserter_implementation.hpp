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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_INSERTER_IMPLEMENTATION_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_INSERTER_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <unordered_set>
#include "dogen/cpp/types/nested_type_info.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp_formatters/types//indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"

namespace dogen {
namespace cpp_formatters {

class inserter_implementation {
public:
    inserter_implementation() = delete;
    inserter_implementation(const inserter_implementation&) = default;
    inserter_implementation(inserter_implementation&&) = default;
    inserter_implementation& operator=(const inserter_implementation&) = default;

public:
    inserter_implementation(std::ostream& stream, indenter& indenter,
        const bool is_inside_class);
    virtual ~inserter_implementation() noexcept {}

private:
    bool is_insertable(const cpp::nested_type_info& nti);

private:
    void tidy_up_string_method();
    void sequence_container_helper(const cpp::nested_type_info& nti);
    void associative_container_helper(const cpp::nested_type_info& nti);
    void smart_pointer_helper(const cpp::nested_type_info& nti);
    void optional_helper(const cpp::nested_type_info& nti);
    void pair_helper(const cpp::nested_type_info& nti);
    void variant_helper(const cpp::nested_type_info& nti);
    void recursive_helper_method_creator(const cpp::nested_type_info& nti,
        std::unordered_set<std::string>& types_done);

public:
    void format_helper_methods(const cpp::class_info& ci);
    void format_inserter_implementation(const cpp::class_info& ci);

protected:
    const bool is_inside_class_;
    std::ostream& stream_;
    indenter& indenter_;
    utility utility_;
};

} }

#endif
