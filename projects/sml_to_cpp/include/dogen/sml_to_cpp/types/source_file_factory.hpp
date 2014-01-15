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
#ifndef DOGEN_SML_TO_CPP_TYPES_SOURCE_FILE_FACTORY_HPP
#define DOGEN_SML_TO_CPP_TYPES_SOURCE_FILE_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/cpp/types/source_file.hpp"
#include "dogen/cpp/types/includes.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"

namespace dogen {
namespace sml_to_cpp {

/**
 * @brief Generates the various file info representations for a given
 * SML type.
 */
class source_file_factory {
public:
    source_file_factory() = delete;
    source_file_factory(const source_file_factory&) = default;
    ~source_file_factory() = default;
    source_file_factory& operator=(const source_file_factory&) = delete;

public:
    explicit source_file_factory(const locator& l);

private:
    /**
     * @brief Converts a relative path to a header file into a C++
     * header guard name.
     */
    std::string to_header_guard_name(const boost::filesystem::path& rp) const;

private:
    /**
     * @brief Performs the initial setup of the file info.
     */
    cpp::source_file create(const cpp::content_descriptor& cd) const;

public:
    /**
     * @brief Manufacture the file info for the given enum info.
     */
    cpp::source_file create(const cpp::enum_info& ei,
        const cpp::content_descriptor& cd, const cpp::includes& inc) const;

    /**
     * @brief Manufacture all the file infos for the given exception.
     */
    cpp::source_file create(const cpp::exception_info& ei,
        const cpp::content_descriptor& cd, const cpp::includes& inc) const;

    /**
     * @brief Manufacture all the file infos for the given namespace.
     */
    cpp::source_file create(const cpp::namespace_info& ni,
        const cpp::content_descriptor& cd) const;

    /**
     * @brief Manufacture all the file infos for the given class.
     */
    cpp::source_file create(const cpp::class_info& ci,
        const cpp::content_descriptor& cd, const cpp::includes& inc) const;

    /**
     * @brief Manufacture file info for includer.
     */
    cpp::source_file create_includer(const cpp::content_descriptor& cd,
        const cpp::includes& inc) const;

    /**
     * @brief Manufacture file info for registrar.
     */
    cpp::source_file create_registrar(const cpp::registrar_info& ri,
        const cpp::content_descriptor& cd, const cpp::includes& inc) const;

    /**
     * @brief Manufacture file info for visitor.
     */
    cpp::source_file create_visitor(const cpp::visitor_info& vi,
        const cpp::content_descriptor& cd, const cpp::includes& inc) const;

private:
    const locator& locator_;
};

} }

#endif
