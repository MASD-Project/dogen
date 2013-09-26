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
#ifndef DOGEN_SML_TYPES_OPAQUE_PARAMETER_CACHE_HPP
#define DOGEN_SML_TYPES_OPAQUE_PARAMETER_CACHE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/opaque_parameter_cache_interface.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Cache for all opaque parameters in a given model, per type.
 */
class opaque_parameter_cache : public opaque_parameter_cache_interface {
public:
    opaque_parameter_cache() = default;
    opaque_parameter_cache(const opaque_parameter_cache&) = default;
    opaque_parameter_cache(opaque_parameter_cache&&) = default;

public:
    virtual ~opaque_parameter_cache() noexcept { }

public:
    void populate(const model& m);

public:
    virtual std::string
    get(const qname& qn, const std::string& key) const override;

    virtual std::string
    get_with_default(const qname& qn, const std::string& key) const override;
};

} }

#endif
