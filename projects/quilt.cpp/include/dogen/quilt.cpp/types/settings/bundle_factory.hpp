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
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/quilt.cpp/types/settings/bundle.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings_builder.hpp"


namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

/**
 * @brief Produces a bundle of settings.
 */
class bundle_factory final {
public:
    bundle_factory(const dynamic::repository& rp,
        const dynamic::object& root_object,
        const dogen::formatters::general_settings_factory& gsf,
        const opaque_settings_builder& osb);

private:
    /**
     * @brief Create the general settings.
     */
    dogen::formatters::general_settings
    create_general_settings(const dynamic::object& o) const;

    /**
     * @brief Create the element settings.
     */
    element_settings create_element_settings(const dynamic::object& o) const;

    /**
     * @brief Generates the opaque settings.
     */
    std::unordered_map<std::string, boost::shared_ptr<opaque_settings> >
    create_opaque_settings(const dynamic::object& o) const;

public:
    /**
     * @brief Produces the settings bundle.
     */
    bundle make(const dynamic::object& o) const;

    /**
     * @brief Hack to produce registrar settings.
     */
    bundle make() const;

private:
    const dynamic::repository& dynamic_repository_;
    const dynamic::object& root_object_;
    const dogen::formatters::general_settings_factory&
    general_settings_factory_;
    const opaque_settings_builder& opaque_settings_builder_;
};

} } } }

#endif
