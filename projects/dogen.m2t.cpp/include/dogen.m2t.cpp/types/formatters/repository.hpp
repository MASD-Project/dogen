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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTERS_REPOSITORY_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTERS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen.m2t.cpp/types/formatters/helper_formatter_interface_fwd.hpp"
#include "dogen.m2t.cpp/types/formatters/artefact_formatter_interface_fwd.hpp"

namespace dogen::m2t::cpp::formatters {

class registrar;

/**
 * @brief Repository for all formatters.
 */
class repository final {
private:
    friend class registrar;

private:
    /**
     * @brief Returns all available file formatters by type indx.
     */
    std::unordered_map<
        std::string,
        std::forward_list<std::shared_ptr<artefact_formatter_interface>>
    >&
    stock_artefact_formatters_by_meta_name();

    /**
     * @brief Returns all available file formatters by archetype name.
     */
    std::unordered_map<std::string,
                       std::shared_ptr<artefact_formatter_interface>>&
    stock_artefact_formatters_by_archetype();

    /**
     * @brief Returns all available file formatters.
     */
    std::forward_list<std::shared_ptr<artefact_formatter_interface>>&
    stock_artefact_formatters();

    /**
     * @brief Returns all available helpers.
     */
    std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::list<
                               std::shared_ptr<helper_formatter_interface>>>>&
    helper_formatters();

public:
    /**
     * @brief Returns all available file formatters by type indx.
     */
    const std::unordered_map<
    std::string,
    std::forward_list<std::shared_ptr<artefact_formatter_interface>>>&
    stock_artefact_formatters_by_meta_name() const;

    /**
     * @brief Returns all available file formatters by formatter name.
     */
    const std::unordered_map<std::string,
                             std::shared_ptr<artefact_formatter_interface>>&
    stock_artefact_formatters_by_archetype() const;

    /**
     * @brief Returns all available file formatters.
     */
    const std::forward_list<std::shared_ptr<artefact_formatter_interface>>&
    stock_artefact_formatters() const;

    /**
     * @brief Returns all available helpers.
     */
    const std::unordered_map<
    std::string,
    std::unordered_map<std::string,
                       std::list<
                           std::shared_ptr<helper_formatter_interface>>>>&
    helper_formatters() const;

private:
    std::unordered_map<
        std::string,
        std::forward_list<std::shared_ptr<artefact_formatter_interface>>>
    stock_artefact_formatters_by_meta_name_;
    std::unordered_map<std::string,
                       std::shared_ptr<artefact_formatter_interface>>
    stock_artefact_formatters_by_archetype_;
    std::forward_list<std::shared_ptr<artefact_formatter_interface>>
    stock_artefact_formatters_;
    std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::list<
                               std::shared_ptr<helper_formatter_interface>>>>
    helper_formatters_;
};

}

#endif
