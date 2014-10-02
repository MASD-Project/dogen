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
#ifndef DOGEN_SML_TYPES_CONSUMER_INTERFACE_HPP
#define DOGEN_SML_TYPES_CONSUMER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/concept.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Consumes elements in a model.
 */
class consumer_interface {
public:
    consumer_interface() = default;
    consumer_interface(const consumer_interface&) = delete;
    consumer_interface(consumer_interface&&) = default;
    virtual ~consumer_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for this consumer, for logging
     * purposes.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Number of passes required by this consumer.
     */
    virtual unsigned int required_passes() const = 0;

    /**
     * @brief If true, always execute this consumer after all passes
     * for all consumers have been performed.
     */
    virtual bool consume_last() const = 0;

    /**
     * @brief Consume concept.
     */
    virtual void consume(const model& model, const unsigned int pass,
        const concept& target) = 0;

    /**
     * @brief Consume module.
     */
    virtual void consume(const model& model, const unsigned int pass,
        const module& target) = 0;

    /**
     * @brief Consume enumeration.
     */
    virtual void consume(const model& model, const unsigned int pass,
        const enumeration& target) = 0;

    /**
     * @brief Consume primitive.
     */
    virtual void consume(const model& model, const unsigned int pass,
        const primitive& target) = 0;

    /**
     * @brief Consume object.
     */
    virtual void consume(const model& model, const unsigned int pass,
        const object& target) = 0;
};

} }

#endif
