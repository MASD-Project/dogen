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
#ifndef DOGEN_ORG_TYPES_HELPERS_DOCUMENT_FACTORY_HPP
#define DOGEN_ORG_TYPES_HELPERS_DOCUMENT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <istream>
#include "dogen.org/types/entities/document.hpp"

namespace dogen::org::helpers {

/**
 * @brief Builds a org-mode document from a string.
 */
class document_factory final {
private:
    /**
     * @brief Retrieves the next line of the stream, if any is
     * available.
     *
     * Unlike standard getline, it preserves new lines.
     */
    static std::istream& getline(std::istream& is, std::string& s);

public:
    static entities::document make(const std::string& s);
};

}

#endif
