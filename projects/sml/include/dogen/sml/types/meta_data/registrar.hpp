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
#ifndef DOGEN_SML_TYPES_META_DATA_REGISTRAR_HPP
#define DOGEN_SML_TYPES_META_DATA_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "dogen/sml/types/meta_data/enricher_interface.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

/**
 * @brief Keeps track of all the available enrichers.
 */
class registrar {
public:
    /**
     * @brief Add the root enricher to the registrar.
     */
    void register_root_enricher(std::shared_ptr<enricher_interface> e);

    /**
     * @brief Add an ordinary enricher to the registrar.
     */
    void register_ordinary_enricher(std::shared_ptr<enricher_interface> e);

public:
    /**
     * @brief Returns the root enricher, if one was registered, or
     * null otherwise.
     */
    std::shared_ptr<enricher_interface> root_enricher();

    /**
     * @brief Returns all of the registered ordinary enrichers, or an
     * empty list if none were registered.
     */
    std::list<std::shared_ptr<enricher_interface>> ordinary_enrichers();

private:
    std::shared_ptr<enricher_interface> root_enricher_;
    std::list<std::shared_ptr<enricher_interface>> ordinary_enrichers_;
};

} } }

#endif
