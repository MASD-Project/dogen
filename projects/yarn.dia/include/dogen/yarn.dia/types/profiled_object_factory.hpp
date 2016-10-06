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
#ifndef DOGEN_YARN_DIA_TYPES_PROFILED_OBJECT_FACTORY_HPP
#define DOGEN_YARN_DIA_TYPES_PROFILED_OBJECT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/dia/types/object_fwd.hpp"
#include "dogen/dia/types/diagram_fwd.hpp"
#include "dogen/yarn.dia/types/profile.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/profiled_object.hpp"


namespace dogen {
namespace yarn {
namespace dia {

class profiled_object_factory {
private:
    processed_object make_processed_object(const dogen::dia::object& o) const;
    profile make_profile(const processed_object& po) const;

public:
    std::list<profiled_object> make(const dogen::dia::diagram& d) const;
};

} } }

#endif
