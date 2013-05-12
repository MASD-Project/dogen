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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_HASH_IMPLEMENTATION_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_HASH_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/file_view_model.hpp"
#include "dogen/cpp/types/nested_type_view_model.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/utility.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

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
    bool is_hashable(const nested_type_view_model& vm);

private:
    void pair_helper(const nested_type_view_model& vm);
    void optional_helper(const nested_type_view_model& vm);
    void variant_helper(const nested_type_view_model& vm);
    void sequence_container_helper(const nested_type_view_model& vm);
    void associative_container_helper(const nested_type_view_model& vm);
    void smart_pointer_helper(const nested_type_view_model& vm);
    void ptime_helper(const nested_type_view_model& vm);
    void time_duration_helper(const nested_type_view_model& vm);
    void recursive_helper_method_creator(const nested_type_view_model& vm,
        std::unordered_set<std::string>& types_done);
    void create_helper_methods(const class_view_model& vm);

private:
    void combine_function(const class_view_model& vm);
    void hasher_hash_method(const class_view_model& vm);

private:
    void format_class(const file_view_model& vm);
    void format_enumeration(const file_view_model& vm);

public:
    virtual void format(const file_view_model& vm) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};


} } }

#endif
