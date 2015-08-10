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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_NAME_BUILDER_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/types/nested_name.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Builds string representations of names, according to the
 * grammar of C++.
 */
class name_builder {
public:
    name_builder() = default;
    name_builder(const name_builder&) = default;
    name_builder(name_builder&&) = default;
    ~name_builder() noexcept = default;

public:
    /**
     * @brief Flattens all the Tack namespace information stored in
     * name into a list of strings with C++ namespaces.
     */
    std::list<std::string>
    namespace_list(const tack::model& m, const tack::name& n) const;

    /**
     * @brief Flat representation of the qualified name.
     */
    std::string qualified_name(const tack::model& m, const tack::name& n) const;

    /**
     * @brief Returns a complete name representation of the nested
     * qualified name.
     */
    void complete_name(const tack::model& m, const tack::nested_name& nn,
        std::string& complete_name) const;

    /**
     * @brief Returns a string representation of the name supplied
     * that can be used as a c++ identifier.
     */
    std::string identifiable_name(const std::string& n) const;
};

} } }

#endif
