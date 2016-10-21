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
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/quilt.cpp/types/formatters/repository.hpp"
#include "dogen/quilt.cpp/types/formatters/helper_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"

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

public:
    void register_formatter_helper(
        std::shared_ptr<helper_formatter_interface> fh);

public:
    /**
     * @brief Registers a file formatter.
     */
    void register_formatter(std::shared_ptr<artefact_formatter_interface> f);

public:
    /**
     * @brief Returns all available formatters.
     */
    const repository& formatter_repository() const;

    /**
     * @brief Returns the ownership hierarchy for all formatters.
     */
    const std::forward_list<annotations::archetype_location>&
    ownership_hierarchy() const;

    const std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::list<
                               std::shared_ptr<helper_formatter_interface>>>>&
    formatter_helpers() const;

private:
    repository formatter_repository_;
    std::forward_list<annotations::archetype_location> ownership_hierarchy_;
};

template<typename Formatter>
inline void register_formatter(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_formatter(f);
}

template<typename Formatter>
inline void register_formatter(registrar& rg, const std::string& facet_name) {
    const auto f(std::make_shared<Formatter>(facet_name));
    rg.register_formatter(f);
}

template<typename Formatter>
inline void register_formatter_helper(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_formatter_helper(f);
}

} } } }

#endif
