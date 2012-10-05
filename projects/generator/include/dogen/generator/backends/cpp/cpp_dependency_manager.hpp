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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_CPP_DEPENDENCY_MANAGER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_CPP_DEPENDENCY_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <list>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/domain/pod.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief Responsible for computing all dependencies for a given
 * type.
 *
 * Dependencies in this sense are all include files required in order
 * to successfully compile the current file.
 */
class cpp_dependency_manager {
public:
    cpp_dependency_manager() = delete;
    cpp_dependency_manager(const cpp_dependency_manager&) = default;
    ~cpp_dependency_manager() = default;
    cpp_dependency_manager(cpp_dependency_manager&&) = default;
    cpp_dependency_manager& operator=(const cpp_dependency_manager&) = delete;

public:
    cpp_dependency_manager(sml::model model,
        cpp_location_manager location_manager, bool disable_keys,
        bool use_integrated_io, bool disable_io);

private:
    bool has_versioned_dependency(cpp_facet_types ft, cpp_file_types flt) const;

    cpp_location_request location_request_factory(cpp_facet_types ft,
        cpp_file_types flt, sml::qualified_name name) const;

    /**
     * @brief Returns the dependency to the unversioned key domain
     * header.
     */
    std::string unversioned_dependency() const;

    /**
     * @brief Returns the dependency to the versioned key header of
     * the given facet.
     */
    std::string
    versioned_dependency(cpp_facet_types ft, cpp_file_types flt) const;

    /**
     * @brief Returns the dependency to the domain header.
     */
    std::string
    domain_header_dependency(sml::qualified_name name) const;

    /**
     * @brief Returns the dependency to the header file.
     */
    std::string header_dependency(sml::qualified_name name,
        cpp_facet_types ft) const;

    std::list<std::string>
    user(sml::qualified_name name, cpp_facet_types ft,
        cpp_file_types flt, cpp_aspect_types at) const;

public:
    /**
     * @brief Register header file with dependency manager.
     *
     * You must ensure all domain headers are registered before you
     * query for aspects which require all header files such as the
     * includers.
     */
    void register_header(cpp_facet_types ft,
        boost::filesystem::path relative_path);

public:
    /**
     * @brief Returns all the system dependencies for the type.
     *
     * These are STL files, boost files, etc.
     *
     * If you choose the signature with @e pod, properties and parents
     * are taken into account when generating the list of
     * dependencies. These are ignored when you supply just @e name.
     */
    /**@{*/
    std::list<std::string> system(std::string name,
        cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at) const;
    std::list<std::string> system(sml::pod pod,
        cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at) const;
    /**@}*/

    /**
     * @brief Returns all user dependencies for the type.
     *
     * These are files on this domain model or other models that it
     * may depend on.
     *
     * If you choose the signature with @e pod, properties and parents
     * are taken into account when generating the list of
     * dependencies. These are ignored when you supply just @e name.
     */
    /**@{*/
    std::list<std::string> user(std::string name,
        cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at) const;
    std::list<std::string> user(sml::pod pod,
        cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at) const;
    /**@}*/

private:
    const sml::model model_;
    const cpp_location_manager location_manager_;
    std::map<cpp_facet_types, std::list<std::string> > headers_for_facet_;
    const bool disable_keys_;
    const bool use_integrated_io_;
    const bool disable_io_;
};

} } } }

#endif
