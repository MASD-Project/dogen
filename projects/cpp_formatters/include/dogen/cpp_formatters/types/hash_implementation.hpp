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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_HASH_IMPLEMENTATION_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_HASH_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/formattables/file_info.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/nested_type_info.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/file_formatter.hpp"

namespace dogen {
namespace cpp_formatters {

class hash_implementation : public file_formatter {
public:
    hash_implementation() = delete;
    hash_implementation(const hash_implementation&) = default;
    hash_implementation(hash_implementation&&) = default;
    hash_implementation& operator=(const hash_implementation&) = default;

public:
    explicit hash_implementation(std::ostream& stream);
    virtual ~hash_implementation() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    bool is_hashable(const cpp::formattables::nested_type_info& nti);

private:
    void path_helper(const cpp::formattables::nested_type_info& nti);
    void pair_helper(const cpp::formattables::nested_type_info& nti);
    void optional_helper(const cpp::formattables::nested_type_info& nti);
    void variant_helper(const cpp::formattables::nested_type_info& nti);
    void sequence_container_helper(
        const cpp::formattables::nested_type_info& nti);
    void associative_container_helper(
        const cpp::formattables::nested_type_info& nti);
    void smart_pointer_helper(const cpp::formattables::nested_type_info& nti);
    void date_helper(const cpp::formattables::nested_type_info& nti);
    void ptime_helper(const cpp::formattables::nested_type_info& nti);
    void time_duration_helper(const cpp::formattables::nested_type_info& nti);
    void ptree_helper(const cpp::formattables::nested_type_info& nti);
    void recursive_helper_method_creator(
        const cpp::formattables::nested_type_info& nti,
        std::unordered_set<std::string>& types_done);
    void create_helper_methods(const cpp::formattables::class_info& ci);

private:
    void combine_function(const cpp::formattables::class_info& ci);
    void hasher_hash_method(const cpp::formattables::class_info& ci);

private:
    void format_class(const cpp::formattables::file_info& f);
    void format_enumeration(const cpp::formattables::file_info& f);

public:
    virtual void format(const cpp::formattables::file_info& f) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};


} }

#endif
