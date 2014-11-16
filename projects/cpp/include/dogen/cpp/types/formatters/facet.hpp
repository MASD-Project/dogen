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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FACET_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FACET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/cpp/types/settings_bundle.hpp"
#include "dogen/cpp/types/formatters/container.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Represents a dogen facet.
 */
class facet {
public:
    /**
     * @brief Facet Id.
     */
    /**@{*/
    std::string id() const;
    void id(const std::string& v);
    /**@}*/

    /**
     * @brief Bundle of settings for this facet.
     */
    /**@{*/
    settings_bundle bundle() const;
    void bundle(const settings_bundle& v);
    /**@}*/

    /**
     * @brief Formatter container for the facet.
     */
    const formatters::container& container() const;
    void container(const formatters::container& v);

private:
    std::string id_;
    settings_bundle bundle_;
    formatters::container container_;
};

} } }

#endif
