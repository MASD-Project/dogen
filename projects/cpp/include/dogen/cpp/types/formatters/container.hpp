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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_CONTAINER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen/cpp/types/formatters/formatter_interface.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/enum_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/visitor_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/exception_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/odb_options_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/cmakelists_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/primitive_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/concept_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/registrar_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/includers_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class registrar;

/**
 * @brief Simple container for all formatter types.
 */
class container final {
private:
    friend class registrar;

public:
    /**
     * @brief Returns all available class formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::class_formatter_interface>
    >&
    class_formatters() const;

    /**
     * @brief Returns all available enum formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::enum_formatter_interface>
        >&
    enum_formatters() const;

    /**
     * @brief Returns all available enum formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::exception_formatter_interface>
        >&
    exception_formatters() const;

    /**
     * @brief Returns all available namespace formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::namespace_formatter_interface>
        >&
    namespace_formatters() const;

    /**
     * @brief Returns all available namespace formatters.
     */
     const std::forward_list<
         std::shared_ptr<formatters::visitor_formatter_interface>
         >&
     visitor_formatters() const;

    /**
     * @brief Returns all available forward declarations formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::forward_declarations_formatter_interface>
    >&
    forward_declarations_formatters() const;

    /**
     * @brief Returns all available odb options formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::odb_options_formatter_interface>
        >&
    odb_options_formatters() const;

    /**
     * @brief Returns all available CMakeLists formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::cmakelists_formatter_interface>
        >&
    cmakelists_formatters() const;

    /**
     * @brief Returns all available primitive formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::primitive_formatter_interface>
        >&
    primitive_formatters() const;

    /**
     * @brief Returns all available concept formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::concept_formatter_interface>
        >&
     concept_formatters() const;

    /**
     * @brief Returns all available registrar formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::registrar_formatter_interface>
        >&
    registrar_formatters() const;

    /**
     * @brief Returns all available includers formatters.
     */
    const std::forward_list<
        std::shared_ptr<formatters::includers_formatter_interface>
        >&
    includers_formatters() const;

public:
    /**
     * @brief Returns all available formatters.
     */
    const std::forward_list<std::shared_ptr<formatters::formatter_interface>>&
    all_formatters() const;

    /**
     * @brief Returns all internal formatters.
     */
    const std::forward_list<std::shared_ptr<formatters::formatter_interface>>&
        all_internal_formatters() const;

    /**
     * @brief Returns all internal formatters.
     */
    const std::forward_list<std::shared_ptr<formatters::formatter_interface>>&
        all_external_formatters() const;

private:
    std::forward_list<std::shared_ptr<formatters::class_formatter_interface>>
    class_formatters_;
    std::forward_list<std::shared_ptr<formatters::enum_formatter_interface>>
    enum_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::exception_formatter_interface>> exception_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::namespace_formatter_interface>> namespace_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::visitor_formatter_interface>> visitor_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::forward_declarations_formatter_interface> >
    forward_declarations_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::odb_options_formatter_interface> >
    odb_options_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::cmakelists_formatter_interface> >
    cmakelists_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::primitive_formatter_interface> >
    primitive_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::concept_formatter_interface> >
    concept_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::registrar_formatter_interface> >
    registrar_formatters_;
    std::forward_list<std::shared_ptr<
        formatters::includers_formatter_interface> >
    includers_formatters_;
    std::forward_list<std::shared_ptr<formatters::formatter_interface>>
        all_formatters_;
    std::forward_list<std::shared_ptr<formatters::formatter_interface>>
        all_internal_formatters_;
    std::forward_list<std::shared_ptr<formatters::formatter_interface>>
        all_external_formatters_;
};

} } }

#endif
