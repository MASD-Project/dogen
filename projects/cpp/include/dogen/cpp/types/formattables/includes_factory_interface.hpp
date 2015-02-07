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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUDES_FACTORY_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUDES_FACTORY_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/cpp/types/formattables/includes.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Builds the includes for a given type.
 */
class includes_factory_interface  {
public:
    typedef std::unordered_map<std::string, boost::filesystem::path>
    path_by_formatter_type;

public:
    includes_factory_interface() = default;
    includes_factory_interface(const includes_factory_interface &) = delete;
    includes_factory_interface(includes_factory_interface &&) = default;
    virtual ~includes_factory_interface () noexcept = 0;

public:
    /**
     * @brief Build the includes.
     *
     * @param m model to query for relationship information.
     * @param qn type for which to build the includes.
     * @param relative_file_names_by_formatter_by_qname relative paths
     * the system knows of, keyed by qualified name and formatter id.
     */
    virtual includes
    make(const sml::model& m, const sml::qname qn,
        const std::unordered_map<sml::qname, path_by_formatter_type>&
        relative_file_names_by_formatter_by_qname) const = 0;
};

} } }

#endif
