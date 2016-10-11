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
#ifndef DOGEN_ANNOTATIONS_TYPES_VALUE_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_VALUE_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/value.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Builds a value from raw data.
 */
class value_factory {
private:
    /**
     * @brief Converts s to integer.
     *
     * @pre s must be a valid integer.
     */
    int to_int(const std::string& s) const;

    /**
     * @brief Converts s to bool.
     *
     * @pre s must be a valid bool.
     */
    bool to_bool(const std::string& s) const;

public:
    /**
     * @brief Creates a stand alone text value.
     */
    boost::shared_ptr<value> make_text(const std::string& v) const;

    /**
     * @brief Creates a collection of text values.
     */
    boost::shared_ptr<value>
    make_text_collection(const std::list<std::string>& v) const;

    /**
     * @brief Creates a stand alone boolean value.
     */
    /**@{*/
    boost::shared_ptr<value> make_boolean(const std::string& v) const;
    boost::shared_ptr<value> make_boolean(const bool v) const;
    /**@}*/

    /**
     * @brief Creates a stand alone numeric value.
     */
    /**@{*/
    boost::shared_ptr<value> make_number(const std::string& v) const;
    boost::shared_ptr<value> make_number(const int v) const;
    /**@}*/
};

} }

#endif
