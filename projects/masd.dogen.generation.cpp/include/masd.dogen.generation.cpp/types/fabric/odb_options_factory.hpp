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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_ODB_OPTIONS_FACTORY_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_ODB_OPTIONS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation.cpp/types/fabric/object_odb_options.hpp"

namespace masd::dogen::generation::cpp::fabric {

class odb_options_factory final {
private:
    boost::shared_ptr<coding::meta_model::element>
    make(const coding::meta_model::name& n,
        const coding::meta_model::origin_types& ot,
        const variability::meta_model::configuration cfg) const;

public:
    std::list<boost::shared_ptr<coding::meta_model::element>>
    make(const generation::meta_model::model& m) const;
};

}

#endif
