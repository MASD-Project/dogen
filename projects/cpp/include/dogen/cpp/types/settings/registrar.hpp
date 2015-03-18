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
#ifndef DOGEN_CPP_TYPES_SETTINGS_REGISTRAR_HPP
#define DOGEN_CPP_TYPES_SETTINGS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include <boost/shared_ptr.hpp>
#include "dogen/cpp/types/settings/special_formatter_settings_factory_interface_fwd.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Manages factory registration.
 */
class registrar final {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers a special formatter settings factory.
     */
    void register_special_formatter_settings_factory(
        boost::shared_ptr<
            const special_formatter_settings_factory_interface
            > f);

    /**
     * @brief Returns all registered special formatter settings
     * factories.
     */
    const std::forward_list<
        boost::shared_ptr<const special_formatter_settings_factory_interface>
        >& special_formatter_settings_factories() const;

private:
    std::forward_list<
        boost::shared_ptr<const special_formatter_settings_factory_interface>
        > special_formatter_settings_factories_;
};

} } }

#endif
