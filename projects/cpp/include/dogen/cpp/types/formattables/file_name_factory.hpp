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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FILE_NAME_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FILE_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/object_types.hpp"
#include "dogen/cpp/types/settings/settings.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formatters/formatter_types.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates all relative file names for all types in model.
 */
class file_name_factory {
private:
    /**
     * @brief Given an SML object type, returns its corresponding
     * formatter type.
     */
    formatters::formatter_types
    formatter_type_for_object_type(const sml::object_types ot) const;

public:
    /**
     * @brief Generate file names.
     */
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, boost::filesystem::path>
        >
    build(const settings::settings& s, const formatters::container& c,
        const sml::model& m) const;
};

} } }

#endif
