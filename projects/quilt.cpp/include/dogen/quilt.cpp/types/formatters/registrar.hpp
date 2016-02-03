/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_REGISTRAR_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formatters/formatter_helper_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/enum_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/class_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/visitor_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/namespace_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/odb_options_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/cmakelists_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/registrar_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/forward_declarations_formatter_interface.hpp"

namespace dogen {
namespace quilt {
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
    void register_formatter_helper(
        std::shared_ptr<formatter_helper_interface> fh);

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
     * @brief Registers an exception formatter.
     */
    void register_formatter(std::shared_ptr<exception_formatter_interface> f);

    /**
     * @brief Registers a namespace formatter.
     */
    void register_formatter(std::shared_ptr<namespace_formatter_interface> f);

    /**
     * @brief Registers a visitor formatter.
     */
    void register_formatter(std::shared_ptr<visitor_formatter_interface> f);

    /**
     * @brief Registers a forward declaration formatter.
     */
    void register_formatter(
        std::shared_ptr<forward_declarations_formatter_interface> f);

    /**
     * @brief Registers a odb options formatter.
     */
    void register_formatter(
        std::shared_ptr<odb_options_formatter_interface> f);

    /**
     * @brief Registers a CMakeLists formatter.
     */
    void register_formatter(
        std::shared_ptr<cmakelists_formatter_interface> f);

    /**
     * @brief Registers a registrar formatter.
     */
    void register_formatter(
        std::shared_ptr<registrar_formatter_interface> f);

    /**
     * @brief Registers an includers formatter.
     */
    void register_formatter(
        std::shared_ptr<includers_formatter_interface> f);

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

    const std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::shared_ptr<formatter_helper_interface>>>&
    formatter_helpers() const;

private:
    container formatter_container_;
    std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::shared_ptr<formatter_helper_interface>>>
    formatter_helpers_;
    std::forward_list<dynamic::ownership_hierarchy> ownership_hierarchy_;
};

template<typename Formatter>
inline void initialise_formatter(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_formatter(f);
}

template<typename Formatter>
inline void initialise_formatter(registrar& rg, const std::string& facet_name) {
    const auto f(std::make_shared<Formatter>(facet_name));
    rg.register_formatter(f);
}

template<typename Formatter>
inline void initialise_formatter_helper(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_formatter_helper(f);
}

} } } }

#endif
