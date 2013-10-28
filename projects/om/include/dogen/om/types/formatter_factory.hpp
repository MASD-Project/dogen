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
#ifndef DOGEN_OM_TYPES_FORMATTER_FACTORY_HPP
#define DOGEN_OM_TYPES_FORMATTER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen/om/types/type_formatter_interface.hpp"
#include "dogen/om/types/module_formatter_interface.hpp"
#include "dogen/om/types/concept_formatter_interface.hpp"

namespace dogen {
namespace om {

class formatter_factory {
public:
    formatter_factory() = delete;
    formatter_factory(const formatter_factory&) = delete;
    ~formatter_factory() = delete;
    formatter_factory(formatter_factory&&) = delete;
    formatter_factory& operator=(const formatter_factory&) = delete;

public:
    /**
     * @brief Returns instances of all the available type formatters.
     */
    static std::list<boost::shared_ptr<type_formatter_interface> >
    build_type_formatters();

    /**
     * @brief Returns instances of all the available module formatters.
     */
    static std::list<boost::shared_ptr<module_formatter_interface> >
    build_module_formatters();

    /**
     * @brief Returns instances of all the available concept formatters.
     */
    static std::list<boost::shared_ptr<concept_formatter_interface> >
    build_concept_formatters();
};

} }

#endif
