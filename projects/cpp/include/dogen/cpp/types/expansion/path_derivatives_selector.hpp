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
#ifndef DOGEN_CPP_TYPES_EXPANSION_PATH_DERIVATIVES_SELECTOR_HPP
#define DOGEN_CPP_TYPES_EXPANSION_PATH_DERIVATIVES_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/cpp/types/expansion/path_derivatives.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

/**
 * @brief Provides a set of canned queries over path derivatives data.
 */
class path_derivatives_selector {
public:
    path_derivatives_selector(const std::unordered_map<
            sml::qname,
            std::unordered_map<std::string, expansion::path_derivatives> >& pd);

private:
    /**
     * @brief Returns the path derivatives for a given formatter name.
     *
     * @pre Formatter name must exist in path derivatives collection.
     */
    const expansion::path_derivatives&
    path_derivatives_for_formatter_name(
        const std::unordered_map<std::string, expansion::path_derivatives>&
        pd, const std::string& formatter_name) const;

    /**
     * @brief Returns the path derivatives for a given qname.
     *
     * @pre qname must exist in path derivatives collection.
     */
    const std::unordered_map<std::string, expansion::path_derivatives>&
    path_derivatives_for_qname(const sml::qname& qn) const;

public:
    /**
     * @brief Returns the inclusion directive for a given qname and
     * formatter name.
     *
     * @pre qname and formatter names must exist in path derivatives
     * collection.
     */
    std::string select_inclusion_directive(const sml::qname& qn,
        const std::string& formatter_name) const;

private:
    const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, expansion::path_derivatives> >&
    path_derivatives_;
};

} } }

#endif
