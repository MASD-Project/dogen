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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FILE_PROPERTIES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FILE_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/file_properties.hpp"
#include "dogen/cpp/types/formattables/includes_factory_interface.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates all file properties for all types in a model.
 */
class file_properties_factory {
private:
    /**
     * @brief Creates a map of includes factories by formatter name.
     */
    std::unordered_map<std::string,
                       std::shared_ptr<formattables::includes_factory_interface>
                       >
    create_includes_factories(const formatters::container& c) const;

public:
    /**
     * @brief Create file properties.
     */
    std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, formattables::file_properties> >
        make(const settings::selector& s, const formatters::container& c,
            const std::unordered_map<
                sml::qname,
                std::unordered_map<std::string, boost::filesystem::path> >&
            file_names,
            const sml::model& m) const;
};

} } }

#endif
