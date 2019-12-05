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
#ifndef DOGEN_TRACING_TYPES_BACKEND_REGISTRAR_HPP
#define DOGEN_TRACING_TYPES_BACKEND_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/types/tracing_backend.hpp"
#include "dogen.tracing/types/backend_fwd.hpp"

namespace dogen::tracing {


class backend_registrar final {
public:
    /**
     * @brief Registers a backend.
     */
    void register_backend(const boost::shared_ptr<backend> b);

    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

    /**
     * @brief Returns the requested backend, if one exists. Otherwise
     * throws.
     */
    const boost::shared_ptr<backend> obtain_backend(const tracing_backend tb);

private:
    std::unordered_map<dogen::tracing_backend,
                       boost::shared_ptr<backend>> backends_;
};

}

#endif
