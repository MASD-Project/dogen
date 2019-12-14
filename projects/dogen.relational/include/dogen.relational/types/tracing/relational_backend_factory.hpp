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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_RELATIONAL_BACKEND_FACTORY_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_RELATIONAL_BACKEND_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.tracing/types/backend_factory.hpp"

namespace dogen::relational::tracing {

class relational_backend_factory final :
        public dogen::tracing::backend_factory {
public:
    std::string id() const override;
    dogen::tracing_backend tracing_backend() const override;
    boost::shared_ptr<dogen::tracing::backend>
    make(const configuration& cfg, const std::string& version,
        const std::string& run_id, const std::string& logging_impact,
        const std::string& tracing_impact) const override;
};

}

#endif
