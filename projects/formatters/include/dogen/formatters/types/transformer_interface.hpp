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
#ifndef DOGEN_FORMATTERS_TYPES_TRANSFORMER_INTERFACE_FWD_HPP
#define DOGEN_FORMATTERS_TYPES_TRANSFORMER_INTERFACE_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen/sml/types/model_fwd.hpp"
#include "dogen/formatters/types/entity_fwd.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Base formatter for all SML model transformers.
 *
 * A transformer, in this context is responsible for converting an SML
 * model into formattable types.
 */
class transformer_interface {
public:
    transformer_interface() = default;
    transformer_interface(const transformer_interface&) = default;
    transformer_interface(transformer_interface&&) = default;

public:
    virtual ~transformer_interface() noexcept;

public:
    typedef std::list<boost::shared_ptr<const entity> > entities_type;

public:
    /**
     * @brief Transforms the SML model into entities.
     */
    virtual entities_type transform(const sml::model& m) const = 0;
};

} }

#endif
