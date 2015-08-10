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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_BUILDER_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/tack/types/object.hpp"
#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/cpp/types/formattables/enablement_repository.hpp"
#include "dogen/cpp/types/formattables/integrated_facets_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Helps in building the inclusion dependencies for a given
 * formatter.
 */
class inclusion_dependencies_builder {
public:
    // FIXME: temporary hack to handle special includes.
    struct special_includes {
        special_includes() :
            has_std_string(false), has_std_pair(false),
            has_variant(false), has_ptree(false), has_path(false),
            has_date(false), has_ptime(false),
            requires_stream_manipulators(false) {}

        bool has_std_string;
        bool has_std_pair;
        bool has_variant;
        bool has_ptree;
        bool has_path;
        bool has_date;
        bool has_ptime;
        bool requires_stream_manipulators;
    };

public:
    inclusion_dependencies_builder(
        const enablement_repository& erp,
        const settings::bundle_repository& brp,
        const inclusion_directives_repository& idrp,
        const integrated_facets_repository& ifrp);

private:
    /**
     * @brief Returns the inclusion directive for a given name and
     * formatter name.
     *
     * @pre name must exist in path derivatives collection.
     */
    boost::optional<std::string> get_inclusion_directive(
        const tack::name& n, const std::string& formatter_name) const;

public:
    /**
     * @brief Detects the presence of all the "special" includes.
     */
    special_includes make_special_includes(const tack::object& o) const;

    /**
     * @brief Returns true if the formatter is enabled.
     */
    bool is_enabled(const tack::name& n,
        const std::string& formatter_name) const;

    /**
     * @brief Returns true if the facet is integrated.
     */
    bool is_integrated(const std::string& formatter_name,
        const std::string& facet_name) const;

    /**
     * @brief Returns the aspect settings for the supplied name.
     *
     * @pre name must exist in the settings bundle repository.
     */
    settings::aspect_settings get_aspect_settings(const tack::name& n) const;

public:
    /**
     * @brief Adds the supplied inclusion directive.
     */
    void add(const std::string& inclusion_directive);

    /**
     * @brief Adds the inclusion directive for the supplied formatter
     * name and name.
     */
    void add(const tack::name& n, const std::string& formatter_name);

    /**
     * @brief Adds the inclusion directives for the supplied
     * formatter name, for each of the supplied names.
     */
    void add(const std::list<tack::name>& names,
        const std::string& formatter_name);

    /**
     * @brief Adds the inclusion directives for all names in the
     * relationships if any exist.
     */
    void add(const tack::object& o, const tack::relationship_types rt,
        const std::string& formatter_name);

public:
    /**
     * @brief Builds the inclusion dependencies. All additions must
     * have been performed already.
     */
    std::list<std::string> build();

private:
    const enablement_repository& enablement_repository_;
    const settings::bundle_repository& bundle_repository_;
    const inclusion_directives_repository& directives_repository_;
    const integrated_facets_repository& integrated_facets_repository_;
    std::list<std::string> inclusion_dependencies_;
};

} } }

#endif
