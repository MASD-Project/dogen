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
#ifndef DOGEN_OM_TYPES_FORMATTER_FACTORY_HPP
#define DOGEN_OM_TYPES_FORMATTER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/om/types/type_formatter_interface.hpp"
#include "dogen/om/types/module_formatter_interface.hpp"
#include "dogen/om/types/concept_formatter_interface.hpp"

namespace dogen {
namespace om {

class formatter_factory {
public:
    formatter_factory() = delete;
    formatter_factory(const formatter_factory&) = delete;
    ~formatter_factory() = default;
    formatter_factory(formatter_factory&&) = delete;
    formatter_factory& operator=(const formatter_factory&) = delete;

public:
    /**
     * @brief Initialise factory.
     *
     * @param project_directory Top-level directory for the project
     * @param cpp_source_directory Directory under which the C++
     * source files will be placed.
     * @param cpp_include_directory Directory under which the include
     * files will be placed.
     */
    formatter_factory(const boost::filesystem::path& project_directory,
        const boost::filesystem::path& cpp_source_directory,
        const boost::filesystem::path& cpp_include_directory);

public:
    /**
     * @brief Returns instances of all the available type formatters.
     */
    std::list<boost::shared_ptr<type_formatter_interface> >
    build_type_formatters() const;

    /**
     * @brief Returns instances of all the available module formatters.
     */
    std::list<boost::shared_ptr<module_formatter_interface> >
    build_module_formatters() const;

    /**
     * @brief Returns instances of all the available concept formatters.
     */
    std::list<boost::shared_ptr<concept_formatter_interface> >
    build_concept_formatters() const;

private:
    const boost::filesystem::path project_directory_;
    const boost::filesystem::path cpp_source_directory_;
    const boost::filesystem::path cpp_include_directory_;
};

} }

#endif
