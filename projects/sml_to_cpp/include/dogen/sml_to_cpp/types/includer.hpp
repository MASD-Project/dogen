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
#ifndef DOGEN_SML_TO_CPP_TYPES_INCLUDER_HPP
#define DOGEN_SML_TO_CPP_TYPES_INCLUDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <list>
#include <string>
#include <utility>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/content_types.hpp"
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/sml_to_cpp/types/boost_model_helper.hpp"
#include "dogen/sml_to_cpp/types/std_model_helper.hpp"
#include "dogen/sml_to_cpp/types/relationships.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"
#include "dogen/sml_to_cpp/types/inclusion_lists.hpp"

namespace dogen {
namespace sml_to_cpp {

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
class includer {
public:
    includer() = delete;
    includer(const includer&) = default;
    ~includer() = default;
    includer& operator=(const includer&) = delete;

public:
    includer(includer&& rhs);
    includer(const sml::model& model,
        const locator& locator,
        const config::cpp_settings& settings);

private:
    /**
     * @brief Returns the include path to the domain header.
     *
     * @param name Qualified name of the type for which we require the
     * domain header.
     */
    std::string domain_header_dependency(const sml::qname& name,
        const cpp::aspect_types at) const;

    /**
     * @brief Returns the include path to the header file, for the
     * given facet.
     */
    std::string header_dependency(const sml::qname& name,
        config::cpp_facet_types ft, const cpp::aspect_types at) const;

public:
    /**
     * @brief Register header file with dependency manager.
     *
     * You must ensure all domain headers are registered before you
     * query for aspects which require all header files such as the
     * includers.
     */
    void register_header(config::cpp_facet_types ft,
        const boost::filesystem::path& relative_path);

private:
    /**
     * @brief Remove duplicates from inclusion lists
     */
    void remove_duplicates(inclusion_lists& il) const;

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
    void append_implementation_dependencies(const relationships& rel,
        const cpp::content_descriptor& cd, inclusion_lists& il) const;

    /**
     * @brief Handles all dependencies to types in the boost
     * libraries.
     */
    void append_boost_dependencies(const relationships& rel,
        const cpp::content_descriptor& cd,
        inclusion_lists& il) const;

    /**
     * @brief Handles all dependencies to types in the standard
     * library.
     */
    void append_std_dependencies(const cpp::content_descriptor& cd,
        inclusion_lists& il) const;

    /**
     * @brief Appends to the inclusion lists dependencies brought
     * about by all the relationships of the type with other types.
     *
     * In this sense, by relationship we mean either
     * specialisation/generalisation or association - e.g. the parent
     * of the type and all types of all properties it may have.
     */
    void append_relationship_dependencies(const relationships& rel,
        const cpp::content_descriptor& cd, inclusion_lists& il) const;

    /**
     * @brief Appends to the inclusion lists dependencies related to
     * the type itself.
     *
     * For instance, this is the case of the implementation file
     * including the header file.
     */
    void append_self_dependencies(const cpp::content_descriptor& cd,
        inclusion_lists& il) const;

public:
    /**
     * @brief Returns the includes for a given includer.
     *
     * Includers are header files composed exclusively of includes for
     * all files in a given facet. This method returns that list of
     * includes.
     *
     * This method must be called after all objects have been
     * processed, as the list is built up from previous calls.
     *
     * @param ft Facet for which we want the inclusion lists.
     */
    inclusion_lists
    includes_for_includer_files(const cpp::content_descriptor& cd) const;

    /**
     * @brief Returns all the includes required for the given object.
     */
    inclusion_lists includes_for_object(const cpp::content_descriptor& cd,
        const relationships& rel) const;

    /**
     * @brief Returns all the includes required for the given
     * enumeration.
     */
    inclusion_lists
    includes_for_enumeration(const cpp::content_descriptor& cd) const;

    /**
     * @brief Returns all the includes required for the given
     * exception.
     */
    inclusion_lists
    includes_for_exception(const cpp::content_descriptor& cd) const;

    /**
     * @brief Returns all the includes required for the serialisation
     * registrar.
     */
    inclusion_lists
    includes_for_registrar(const cpp::content_descriptor& cd) const;

    /**
     * @brief Returns all the includes for a visitor based on qname.
     */
    inclusion_lists includes_for_visitor(const cpp::content_descriptor& cd,
        const relationships& rel) const;

private:
    const sml::model model_;
    const locator locator_;
    const config::cpp_settings settings_;
    const bool io_enabled_;
    const bool serialization_enabled_;
    const bool hash_enabled_;
    std::map<config::cpp_facet_types, std::list<std::string> >
    headers_for_facet_;
    const boost_model_helper boost_;
    const std_model_helper std_;
};

} }

#endif
