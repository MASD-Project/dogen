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
#ifndef DOGEN_TRACING_TYPES_BACKEND_FACTORY_HPP
#define DOGEN_TRACING_TYPES_BACKEND_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen/types/configuration.hpp"
#include "dogen/types/tracing_backend.hpp"
#include "dogen/types/tracing_configuration.hpp"
#include "dogen.tracing/types/backend.hpp"

namespace dogen::tracing {

class backend_factory {
public:
    virtual ~backend_factory() noexcept = 0;

public:
    /**
     * @brief Returns the identity of this backend.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Tracing backend supported by this backend.
     */
    virtual dogen::tracing_backend tracing_backend() const = 0;

public:
    /**
     * @brief Makes a new backend.
     */
    virtual boost::shared_ptr<backend>
    make(const configuration& cfg, const std::string& run_id) = 0;
};

inline backend_factory::~backend_factory() noexcept { }

}

#endif
