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
#ifndef DOGEN_CPP_TYPES_TRANSFORMER_HPP
#define DOGEN_CPP_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/cpp/types/enumeration_info.hpp"

namespace dogen {
namespace cpp {

class transformer {
public:
    transformer() = default;
    transformer(const transformer&) = default;
    ~transformer() = default;
    transformer& operator=(const transformer&) = delete;
    transformer(transformer&& rhs) = default;

private:
    /**
     * @brief Flattens all the SML namespace information stored in qname
     * into a list of strings with C++ namespaces.
     */
    std::list<std::string> transform(const dogen::sml::qname& qn) const;

    /**
     * @brief Transforms an SML enumerator to an enumerator info.
     */
    enumerator_info transform(const sml::enumerator& e) const;

public:
    /**
     * @brief Transforms a SML enumeration into an enumeration info.
     */
    enumeration_info transform(const sml::enumeration& e) const;
};

} }

#endif
