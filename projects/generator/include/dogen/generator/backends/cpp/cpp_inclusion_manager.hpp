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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_CPP_INCLUSION_MANAGER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_CPP_INCLUSION_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <list>
#include <string>
#include <utility>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/config/cpp_settings.hpp"
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
 * @brief Result of a request for includes.
 */
struct inclusion_lists {
    std::list<std::string> system;
    std::list<std::string> user;
};

/**
 * @brief Responsible for computing all the include dependencies for a
 * given type.
 *
 * The include dependencies we concern ourselves with are all files
 * required in order to successfully compile the current file. We make
 * the traditional distinction with regards to type of inclusion:
 *
 * @li @e System includes are those which are in the system include path and
 * are expected to be included using angle brackets;
 *
 * @li @e User includes are those which are in the user include path
 * and are expected to be included using double-quotes.
 *
 */
class cpp_inclusion_manager {
public:
    cpp_inclusion_manager() = delete;
    cpp_inclusion_manager(const cpp_inclusion_manager&) = default;
    ~cpp_inclusion_manager() = default;
    cpp_inclusion_manager& operator=(const cpp_inclusion_manager&) = delete;

public:
    cpp_inclusion_manager(cpp_inclusion_manager&& rhs)
    : model_(std::move(rhs.model_)),
      location_manager_(std::move(rhs.location_manager_)),
      settings_(std::move(rhs.settings_)),
      io_enabled_(std::move(rhs.io_enabled_)),
      headers_for_facet_(std::move(rhs.headers_for_facet_))  { }

    cpp_inclusion_manager(const sml::model& model,
        const cpp_location_manager& location_manager,
        const config::cpp_settings& settings);

private:
    cpp_location_request location_request_factory(cpp_facet_types ft,
        cpp_file_types flt, const sml::qualified_name& name) const;

    /**
     * @brief Returns the include path to the unversioned key domain
     * header.
     */
    std::string unversioned_dependency() const;

    /**
     * @brief Returns the include path to the versioned key header.
     *
     * @param ft Facet for which we require the versioned key header.
     */
    std::string versioned_dependency(cpp_facet_types ft) const;

    /**
     * @brief Returns the include path to the domain header.
     *
     * @param name Qualified name of the type for which we require the
     * domain header.
     */
    std::string
    domain_header_dependency(const sml::qualified_name& name) const;

    /**
     * @brief Returns the include path to the header file, for the
     * given facet.
     */
    std::string header_dependency(const sml::qualified_name& name,
        cpp_facet_types ft) const;

public:
    /**
     * @brief Register header file with dependency manager.
     *
     * You must ensure all domain headers are registered before you
     * query for aspects which require all header files such as the
     * includers.
     */
    void register_header(cpp_facet_types ft,
        const boost::filesystem::path& relative_path);

    /**
     * @brief Returns true if there is a type in the list of qualified
     * names which requires special formatting.
     *
     * The objective of this function is to determine if one is
     * required to use ios stream state saving or not. For types such
     * as bool, etc we are expected to change the state of the stream
     * so state saving is required.
     */
    bool requires_stream_manipulators(
        const std::list<dogen::sml::qualified_name>& names) const;

    /**
     * @brief Returns true if the pod is in a inheritance
     * relationship, as either the parent or the child.
     */
    bool is_parent_or_child(const dogen::sml::pod& p) const;

private:
    /**
     * @brief Flattens the given pod into a list containing all
     * qualified names it is related to, except itself.
     *
     * The qualified names list includes all types used by the
     * properties of the pod, as well as its parent, if any.
     */
    std::list<dogen::sml::qualified_name>
    pod_to_qualified_names(const sml::pod& pod) const;

    /**
     * @brief Appends to the inclusion lists all dependencies related
     * to versioning.
     */
    void append_versioning_dependencies(const cpp_facet_types ft,
        const cpp_file_types flt, cpp_aspect_types at,
        inclusion_lists& il, const bool is_parent_or_child = false) const;

    /**
     * @brief Appends to the inclusion lists all dependencies related
     * to the formatter implementation.
     *
     * The objective of this method is to pick up all header files
     * which are required due to the current source code
     * implementation we have in respective formatter. Formatters are
     * normally given by the pair facet, file type.
     *
     * Its not ideal to have to change the code in the formatter and
     * then the inclusion manager to get the generated models to
     * compile, but on the flip side, all inclusion related code is
     * kept in one place.
     */
    void append_implementation_dependencies(
        const cpp_facet_types ft, const cpp_file_types flt,
        inclusion_lists& il, const bool requires_stream_manipulators = false,
        const bool is_parent_or_child = false) const;

    /**
     * @brief
     */
    void append_std_dependencies(
        const cpp_facet_types ft, const cpp_file_types flt,
        const dogen::sml::qualified_name& qname,
        inclusion_lists& il) const;

    /**
     * @brief Appends to the inclusion lists dependencies brought
     * about by all the relationships of the type with other types.
     *
     * In this sense, by relationship we mean either
     * specialisation/generalisation or association - e.g. the parent
     * of the type and all types of all properties it may have.
     */
    void append_relationship_dependencies(
        const std::list<dogen::sml::qualified_name>& names,
        const cpp_facet_types ft, const cpp_file_types flt,
        inclusion_lists& il) const;

    /**
     * @brief Appends to the inclusion lists dependencies related to
     * the type itself.
     *
     * For instance, this is the case of the implementation file
     * including the header file.
     */
    void append_self_dependencies(dogen::sml::qualified_name name,
        const cpp_facet_types ft, const cpp_file_types flt,
        inclusion_lists& il) const;

public:
    /**
     * @brief Returns the includes for a given includer.
     *
     * Includers are header files composed exclusively of includes for
     * all files in a given facet. This method returns that list of
     * includes.
     *
     * This method must be called after all pods have been processed,
     * as the list is built up from previous calls.
     *
     * @param ft Facet for which we want the inclusion lists.
     */
    inclusion_lists includes_for_includer_files(cpp_facet_types ft) const;

    /**
     * @brief Returns the includes for version related types.
     *
     * Every model for which versioning has been enabled has a
     * versioned and unversioned key. This method returns the includes
     * that involve those files.
     */
    inclusion_lists includes_for_versioning(const std::string& name,
        cpp_facet_types ft, cpp_file_types flt, cpp_aspect_types at) const;

    /**
     * @brief Returns all the includes required for the given pod.
     */
    inclusion_lists includes_for_pod(const sml::pod& pod, cpp_facet_types ft,
        cpp_file_types flt, cpp_aspect_types at) const;

private:
    const sml::model model_;
    const cpp_location_manager location_manager_;
    const config::cpp_settings settings_;
    const bool io_enabled_;
    std::map<cpp_facet_types, std::list<std::string> > headers_for_facet_;
};

} } } }

#endif
