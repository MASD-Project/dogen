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
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp/types/locator.hpp"
#include "dogen/cpp/types/location_request.hpp"
#include "dogen//cpp/types/includer.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/cpp/types/enumeration_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/cpp/types/file_info.hpp"

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
    file_info_factory(const locator& l, includer& i);

private:
    /**
     * @brief Converts a relative path to a header file into a C++
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
    file_info create(const content_descriptor& cd) const;

public:
    /**
     * @brief Manufacture the file info for the given enumeration info.
     */
    std::list<file_info> create(const enumeration_info& ei,
        const std::list<content_descriptor>& cds) const;

    /**
     * @brief Manufacture all the file infos for the given exception.
     */
    std::list<file_info> create(const exception_info& ei,
        const std::list<content_descriptor>& cds) const;

    /**
     * @brief Manufacture all the file infos for the given package.
     */
    std::list<file_info> create(const namespace_info& ni,
        const std::list<content_descriptor>& cds) const;

    /**
     * @brief Manufacture all the file infos for the given pod.
     */
    // FIXME: hack until we update includer
    std::list<file_info> create(const sml::pod& p, const class_info& ci,
        const std::list<content_descriptor>& cds) const;

    /**
     * @brief Manufacture file info for includer.
     */
    std::list<file_info> create_includer(
        const std::list<content_descriptor>& cds) const;

    /**
     * @brief Manufacture file info for registrar.
     */
    std::list<file_info> create_registrar(const registrar_info& ri,
        const std::list<content_descriptor>& cds) const;

    /**
     * @brief Manufacture file info for visitor.
     */
    std::list<file_info> create_visitor(const visitor_info& vi,
        const std::list<content_descriptor>& cds) const;

private:
    const locator& locator_;
    const includer& includer_;
};

} }

#endif
