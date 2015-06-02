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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_IO_HELPER_METHOD_FORMATTER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_IO_HELPER_METHOD_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include <unordered_set>
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp/types/formattables/nested_type_info.hpp"
#include "dogen/cpp/types/formatters/nested_type_formatting_assistant.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace io {

/**
 * @brief Creates all the helper methods for the io facet.
 */
class helper_method_formatter {
public:
    explicit helper_method_formatter(
        const std::list<formattables::property_info>& properties);

private:
    /**
     * @brief Helper method for containers such as list and vector.
     */
    void sequence_container_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

    /**
     * @brief Helper method for containers such as maps and sets.
     */
    void associative_container_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

    /**
     * @brief Helper method for smart pointers such as boost and std
     * shared pointer.
     */
    void smart_pointer_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

    /**
     * @brief Helper method for containers such as boost and std
     * optional.
     */
    void optional_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

    /**
     * @brief Helper method for containers such as std::pair.
     */
    void pair_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

    /**
     * @brief Helper method for containers such as boost variant.
     */
    void variant_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

    /**
     * @brief Helper method for boost property tree.
     */
    void ptree_helper(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t) const;

private:
    /**
     * @brief Creates all the helper methods by recursing into the
     * nested type info.
     */
    void recursive_helper_method_creator(
        formatters::nested_type_formatting_assistant& fa,
        const formattables::nested_type_info& t,
        std::unordered_set<std::string>& types_done) const;

public:
    /**
     * @brief Formats all the helper methods into the supplied stream.
     */
    void format(std::ostream& s) const;

private:
    const std::list<formattables::property_info>& properties_;
};

} } } }

#endif
