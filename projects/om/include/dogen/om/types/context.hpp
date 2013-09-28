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
#ifndef DOGEN_OM_TYPES_CONTEXT_HPP
#define DOGEN_OM_TYPES_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/sml/types/property_cache_interface.hpp"

namespace dogen {
namespace om {

/**
 * @brief Provides a context in which formatting operations occur.
 *
 * All parameters passed in to the context must have a lifetime
 * greater than (or equal to) the context itself as it keeps
 * references to them.
 */
class context {
public:
    context() = delete;
    context(const context&) = delete;
    context(context&&) = delete;
    context& operator=(const context&) = delete;
    ~context() noexcept = default;

public:
    context(std::ostream& s, const sml::property_cache_interface& pc,
        cpp_formatters::indenter& ind, cpp_formatters::utility& u);

public:
    /**
     * @brief Stream to which the formatted output will be sent.
     */
    std::ostream& stream();

    /**
     * @brief Cache that provides access to properties in SML objects.
     */
    const sml::property_cache_interface& property_cache() const;

    /**
     * @brief Indentation facilities.
     */
    cpp_formatters::indenter& indenter();

    /**
     * @brief Formatting utility methods.
     */
    cpp_formatters::utility& utility();

    /**
     * @brief If true, add a blank line at the start.
     */
    /**@{*/
    bool first_line_is_blank() const;
    void first_line_is_blank(bool value);
    /**@}*/

private:
    std::ostream& stream_;
    const sml::property_cache_interface& property_cache_;
    cpp_formatters::indenter& indenter_;
    cpp_formatters::utility& utility_;
    bool first_line_is_blank_;
};

} }

#endif
