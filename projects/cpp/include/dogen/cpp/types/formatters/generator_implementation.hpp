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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_GENERATOR_IMPLEMENTATION_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_GENERATOR_IMPLEMENTATION_HPP

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

class generator_implementation : public file_formatter {
public:
    generator_implementation() = delete;
    generator_implementation(const generator_implementation&) = default;
    generator_implementation(generator_implementation&&) = default;
    generator_implementation&
    operator=(const generator_implementation&) = default;

public:
    explicit generator_implementation(std::ostream& stream);
    virtual ~generator_implementation() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    void sequence_container_helper(
        const nested_type_view_model& vm, unsigned int quantity);
    void associative_container_helper(
        const nested_type_view_model& vm, unsigned int quantity);
    void smart_pointer_helper(const nested_type_view_model& vm);
    void optional_helper(const nested_type_view_model& vm);
    void pair_helper(const nested_type_view_model& vm);
    void variant_helper(const nested_type_view_model& vm);
    void filesystem_path_helper(const nested_type_view_model& vm);
    void date_helper(const nested_type_view_model& vm);
    void ptime_helper(const nested_type_view_model& vm);
    void time_duration_helper(const nested_type_view_model& vm);

    void composite_domain_type_helper(const std::string& identifiable_type_name,
        const std::string& type_name, bool as_pointer);
    void domain_type_helper(const std::string& identifiable_type_name,
        const std::string& type_name, bool as_pointer);
    void bool_helper();
    void string_helper();
    void char_like_helper(const std::string& identifiable_type_name,
        const std::string& type_name);
    void int_like_helper(const std::string& identifiable_type_name,
        const std::string& type_name);
    void recursive_helper_method_creator(const std::string& owner_name,
        const nested_type_view_model& vm,
        std::unordered_set<std::string>& types_done, bool as_pointer);
    void create_helper_methods(const class_view_model& vm);

private:
    void populate_method(const class_view_model& vm);
    void create_method(const class_view_model& vm);
    void create_method_ptr(const class_view_model& vm);
    void function_operator(const class_view_model& vm);
    void default_constructor(const class_view_model& vm);

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
