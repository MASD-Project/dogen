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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_REPOSITORY_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/registrar.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the formatter properties repository.
 */
class formatter_properties_repository_factory {
private:
    /**
     * @brief Obtains the root object for the model.
     */
    dynamic::schema::object obtain_root_object(const sml::model& m) const;

    /**
     * @brief Initialises the registrar with all the providers sourced
     * from the formatters container.
     */
    void initialise_registrar(const formatters::container& c,
        registrar& rg) const;

private:
    /**
     * @brief Create the path derivatives repository.
     */
    path_derivatives_repository create_path_derivatives_repository(
        const config::cpp_options& opts, const dynamic::schema::repository& rp,
        const dynamic::schema::object& ro, const formatters::container& fc,
        const sml::model& m) const;

    /**
     * @brief Create the inclusion directives repository.
     */
    inclusion_directives_repository create_inclusion_directives_repository(
        const dynamic::schema::repository& srp,
        const formatters::container& fc,
        const path_derivatives_repository& pdrp,
        const sml::model& m) const;

    /**
     * @brief Create the inclusion dependencies repository.
     */
    inclusion_dependencies_repository create_inclusion_dependencies_repository(
        const dynamic::schema::repository& srp, const container& pc,
        const inclusion_directives_repository& idrp, const sml::model& m) const;

public:
    formatter_properties_repository make(
        const config::cpp_options& opts,
        const dynamic::schema::repository& srp,
        const formatters::container& fc,
        const sml::model& m) const;
};

} } }

#endif
