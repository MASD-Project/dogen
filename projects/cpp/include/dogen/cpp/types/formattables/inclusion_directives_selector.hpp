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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_SELECTOR_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Provides a set of canned queries over path derivatives data.
 */
class inclusion_directives_selector {
public:
    explicit inclusion_directives_selector(
        const inclusion_directives_repository& rp);

private:
    /**
     * @brief Returns the inclusion directives settings for a given qname.
     *
     * @pre qname must exist in inclusion directives settings
     * collection.
     */
    const settings::inclusion_directives_settings&
    inclusion_directives_for_qname(const sml::qname& qn) const;

    /**
     * @brief Returns the inclusion directive settings for a given
     * formatter name.
     *
     * @pre formatter name must exist in collection.
     */
    const settings::inclusion_directive_settings&
    inclusion_directives_for_formatter(
        const settings::inclusion_directives_settings& ids,
        const std::string& formatter_name) const;

public:
    /**
     * @brief Returns the inclusion directive for a given qname and
     * formatter name.
     *
     * @pre qname must exist in path derivatives collection.
     */
    boost::optional<std::string> select_inclusion_directive(
        const sml::qname& qn, const std::string& formatter_name) const;

private:
    const inclusion_directives_repository& repository_;
};

} } }

#endif
