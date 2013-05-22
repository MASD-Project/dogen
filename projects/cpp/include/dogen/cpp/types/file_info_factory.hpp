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
#ifndef DOGEN_CPP_TYPES_FILE_INFO_FACTORY_HPP
#define DOGEN_CPP_TYPES_FILE_INFO_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <list>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/exception.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/cpp/types/locator.hpp"
#include "dogen/cpp/types/location_request.hpp"
#include "dogen//cpp/types/includer.hpp"
#include "dogen/cpp/types/transformer.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/cpp/types/enumeration_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/file_info.hpp"
#include "dogen/cpp/types/content_descriptor_factory.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Generates the various file info representations for a given
 * SML type.
 */
class file_info_factory {
public:
    file_info_factory() = delete;
    file_info_factory(const file_info_factory&) = default;
    ~file_info_factory() = default;
    file_info_factory& operator=(const file_info_factory&) = delete;

public:
    file_info_factory(const std::set<config::cpp_facet_types>& enabled_facets,
        const transformer& t, const locator& l, includer& i);

public:
    typedef boost::optional<const class_info> optional_class_info;

private:
    /**
     * @brief Transforms a relative path to a header file into a C++
     * header guard name.
     */
    std::string to_header_guard_name(const boost::filesystem::path& rp) const;

    /**
     * @brief Returns a location request for the given contents.
     */
    location_request
    location_request_factory(const content_descriptor& cd) const;

private:
    /**
     * @brief Performs the initial setup of the file info.
     */
    file_info create(const content_descriptor& cd);

    /**
     * @brief Manufacture the file info for the given enumeration info.
     */
    file_info create(const enumeration_info& e, const content_descriptor& cd);

public:
    /**
     * @brief Manufacture all the file infos for the given type.
     */
    std::list<file_info> create(const sml::enumeration& e);

    /**
     * @brief Manufacture all the file infos for the given exception.
     */
    std::list<file_info> create(const sml::exception& e);

    /**
     * @brief Manufacture all the file infos for the given package.
     */
    std::list<file_info> create(const sml::package& p);

    /**
     * @brief Manufacture all the file infos for the given model.
     *
     * Note that this method is very misleading - we are not
     * transforming the entire model, only the package aspect of a
     * model.
     *
     * @todo Create an attribute of type package in model.
     */
    std::list<file_info> create(const sml::model& m);

    /**
     * @brief Manufacture all the file infos for the given pod.
     */
    std::list<file_info> create(const sml::pod& p,
        const optional_class_info pci = optional_class_info(),
        const optional_class_info opci = optional_class_info());

    /**
     * @brief Manufacture file info for includer.
     */
    std::list<file_info> create_includer(
        const std::list<std::string>& external_package_path,
        const config::cpp_facet_types ft);

    /**
     * @brief Manufacture file info for registrar.
     */
    std::list<file_info> create_registrar(const sml::model& m) const;

private:
    const content_descriptor_factory descriptor_factory_;
    const transformer& transformer_;
    const locator& locator_;
    includer& includer_;
};

} }

#endif
