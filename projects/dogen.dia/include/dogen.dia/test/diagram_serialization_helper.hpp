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
#ifndef DOGEN_DIA_TEST_DIAGRAM_SERIALIZATION_HELPER_HPP
#define DOGEN_DIA_TEST_DIAGRAM_SERIALIZATION_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <istream>
#include <boost/filesystem/path.hpp>
#include "dogen.dia/types/diagram.hpp"

namespace dogen::dia::test {

/**
 * @brief Test bed for the creation of serialisation helpers.
 *
 * The objective of the helpers is to hide boost serialisation
 * complexities and provide a one shot API to serialise / deserialise
 * objects.
 */
class diagram_serialization_helper {
public:
    /**
     * @brief Serialises the diagram into the stream using XML.
     */
    static void to_xml(std::ostream& s, const diagram& d);

    /**
     * @brief Reads a diagram from the stream using XML.
     */
    static diagram from_xml(std::istream& s);
};

}

#endif
