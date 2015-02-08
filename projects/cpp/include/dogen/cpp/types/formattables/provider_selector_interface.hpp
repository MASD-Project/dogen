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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PROVIDER_SELECTOR_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PROVIDER_SELECTOR_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include "dogen/sml/types/object_types.hpp"
#include "dogen/cpp/types/formattables/provider_interface.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Query interface for different types of providers.
 */
class provider_selector_interface {
public:
    provider_selector_interface() = default;
    provider_selector_interface(const provider_selector_interface&) = delete;
    provider_selector_interface(provider_selector_interface&&) = default;
    virtual ~provider_selector_interface() noexcept = 0;

public:
    /**
     * @brief Returns all the available providers for the supplied SML
     * object type.
     */
    virtual const std::forward_list<std::shared_ptr<provider_interface> >&
    select_providers_for_object(const sml::object_types ot) const = 0;
};

} } }

#endif
