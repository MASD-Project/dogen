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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.text.csharp/types/transforms/visual_studio/visual_studio_factory.hpp"

namespace dogen::text::csharp::transforms::visual_studio {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.csharp.transforms.visual_studio"));

}

physical::entities::facet visual_studio_factory::make() {
    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");
    b.backend("csharp");
    b.facet("visual_studio");

    physical::entities::facet r;
    r.meta_name(b.build());

    return r;
}

}

