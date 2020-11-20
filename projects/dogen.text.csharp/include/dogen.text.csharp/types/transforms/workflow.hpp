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
#ifndef DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_WORKFLOW_HPP
#define DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.text/types/entities/model.hpp"
#include "dogen.text.csharp/types/transforms/registrar.hpp"

namespace dogen::text::csharp::transforms {

class workflow final {
public:
    workflow();

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static csharp::transforms::registrar& registrar();

private:
    boost::shared_ptr<physical::entities::artefact>
    get_artefact(const physical::entities::region& region,
        const identification::entities::physical_meta_id& archetype) const;

public:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        const text::entities::model& m) const;

private:
    static std::shared_ptr<csharp::transforms::registrar> registrar_;
};

}

#endif
