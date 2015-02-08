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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_PROVIDER_SELECTOR_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_PROVIDER_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/provider_selector_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Implementation of the provider selector that uses a
 * formatter container to generate all of the providers.
 */
class provider_selector : public formattables::provider_selector_interface {
public:
    explicit provider_selector(const formatters::container& c);

private:
    std::forward_list<
        std::shared_ptr<formattables::provider_interface>
    > create_providers_for_regular_objects(const formatters::container& c) const;

public:
    const std::forward_list<
        std::shared_ptr<formattables::provider_interface>
    >&
    select_providers_for_object(const sml::object_types ot) const override;

private:
    const std::forward_list<
        std::shared_ptr<formattables::provider_interface>
    > regular_objects_;
    // FIXME
    const std::forward_list<std::shared_ptr<formattables::provider_interface>
    > empty;
};

} } }

#endif
