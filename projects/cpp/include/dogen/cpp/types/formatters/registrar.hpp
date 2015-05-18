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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_REGISTRAR_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/enum_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Manages formatter registration.
 */
class registrar final {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

private:
    /**
     * @brief Perform common registration.
     */
    void common_registration(
        std::shared_ptr<formatters::formatter_interface> f);

public:
    /**
     * @brief Registers a class formatter.
     */
    void register_formatter(std::shared_ptr<class_formatter_interface> f);

    /**
     * @brief Registers an enum formatter.
     */
    void register_formatter(std::shared_ptr<enum_formatter_interface> f);

    /**
     * @brief Registers a forward declaration formatter.
     */
    void register_formatter(
        std::shared_ptr<forward_declarations_formatter_interface> f);

public:
    /**
     * @brief Returns all available formatters.
     */
    const container& formatter_container() const;

    /**
     * @brief Returns the ownership hierarchy for all formatters.
     */
    const std::forward_list<dynamic::ownership_hierarchy>&
        ownership_hierarchy() const;

private:
    container formatter_container_;
    std::forward_list<dynamic::ownership_hierarchy> ownership_hierarchy_;
};

} } }

#endif
