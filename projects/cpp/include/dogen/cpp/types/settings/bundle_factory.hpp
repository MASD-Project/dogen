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
#ifndef DOGEN_CPP_TYPES_SETTINGS_BUNDLE_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_BUNDLE_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings/bundle.hpp"
#include "dogen/cpp/types/settings/opaque_settings.hpp"
#include "dogen/cpp/types/settings/opaque_settings_factory_interface.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Produces a bundle of settings.
 */
class bundle_factory final {
public:
    bundle_factory(const dynamic::schema::object& root_object,
        const std::forward_list<
            boost::shared_ptr<const opaque_settings_factory_interface>
            >& opaque_settings_factories);

private:
    /**
     * @brief Creates the formatters' repository.
     */
    dogen::formatters::repository create_formatters_repository(
        const std::forward_list<boost::filesystem::path>& dirs) const;

private:
    /**
     * @brief Create the general settings.
     */
    dogen::formatters::general_settings
    create_general_settings(const dynamic::schema::object& o) const;

    /**
     * @brief Generates the opaque settings.
     */
    std::unordered_map<std::string, boost::shared_ptr<opaque_settings> >
    create_opaque_settings(const dynamic::schema::object& o) const;

public:
    /**
     * @brief Produces the settings bundle.
     */
    bundle make(const dynamic::schema::object& o) const;

private:
    const dynamic::schema::object& root_object_;
    const std::forward_list<
        boost::shared_ptr<const opaque_settings_factory_interface>
        >& opaque_settings_factories_;
    const dogen::formatters::repository formatters_repository_;
};

} } }

#endif
