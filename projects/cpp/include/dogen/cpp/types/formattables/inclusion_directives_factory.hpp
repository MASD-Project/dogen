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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/tack/types/qname.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the inclusion directives for a given Tack entity.
 */
class inclusion_directives_factory {
public:
    inclusion_directives_factory(const dynamic::repository& srp,
        const formatters::container& fc,
        const path_derivatives_repository& pdrp);

private:
    /**
     * @brief Get the path derivatives for supplied qname.
     */
    std::unordered_map<std::string, formattables::path_derivatives>
    path_derivatives_for_qname(const tack::qname& qn) const;

    /**
     * @brief Get the path derivatives for supplied formatter name.
     */
    formattables::path_derivatives
    path_derivatives_for_formatter_name(
        const std::unordered_map<std::string,
                                 formattables::path_derivatives>& pd,
        const std::string& formatter_name) const;

    /**
     * @brief Validates the inclusion directive.
     */
    void validate_inclusion_directive(const std::string& id,
        const std::string& formatter_name,
        const std::string& type_name) const;

private:
    /**
     * @brief Create the inclusion directive settings.
     */
    settings::inclusion_directives_settings
    create_inclusion_directives_settings(
        const dynamic::object& o) const;

    /**
     * @brief Obtains the include directive, if it exists.
     */
    boost::optional<std::pair<std::string, std::string> >
    obtain_include_directive(const std::string& formatter_name,
        const std::string& type_name,
        const std::unordered_map<std::string,
                                 formattables::path_derivatives>& pd,
        const settings::inclusion_directive_settings& s) const;

public:
    /**
     * @brief Create the inclusion directives for a given Tack entity.
     */
    boost::optional<std::unordered_map<std::string, std::string> >
    make(const dynamic::object& o, const tack::qname& qn) const;

private:
    const dynamic::repository& dynamic_repository_;
    const formatters::container& container_;
    const path_derivatives_repository& path_repository_;
};

} } }

#endif
