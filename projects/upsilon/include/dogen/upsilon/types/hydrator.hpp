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
#ifndef DOGEN_UPSILON_TYPES_HYDRATOR_HPP
#define DOGEN_UPSILON_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/upsilon/types/model.hpp"
#include "dogen/upsilon/types/schema.hpp"
#include "dogen/upsilon/types/config.hpp"
#include "dogen/upsilon/types/type_information.hpp"

namespace dogen {
namespace upsilon {

class hydrator final {
public:
    config hydrate_config(boost::filesystem::path f);
    schema hydrate_schema(boost::filesystem::path f);
    type_information hydrate_type_information(boost::filesystem::path f);

public:
    model hydrate(boost::filesystem::path config_file);
};

} }

#endif
