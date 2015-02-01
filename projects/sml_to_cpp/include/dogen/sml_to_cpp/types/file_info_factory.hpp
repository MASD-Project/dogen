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
#ifndef DOGEN_SML_TO_CPP_TYPES_FILE_INFO_FACTORY_HPP
#define DOGEN_SML_TO_CPP_TYPES_FILE_INFO_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/formattables/content_descriptor.hpp"
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/types/formattables/exception_info.hpp"
#include "dogen/cpp/types/formattables/namespace_info.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/registrar_info.hpp"
#include "dogen/cpp/types/formattables/visitor_info.hpp"
#include "dogen/cpp/types/formattables/file_info.hpp"
#include "dogen/cpp/types/formattables/includes.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"

namespace dogen {
namespace sml_to_cpp {

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
    explicit file_info_factory(const locator& l);

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
    cpp::formattables::file_info
    create(const cpp::formattables::content_descriptor& cd) const;

public:
    /**
     * @brief Manufacture the file info for the given enum info.
     */
    cpp::formattables::file_info
    create(boost::shared_ptr<cpp::formattables::enum_info> ei,
        const cpp::formattables::content_descriptor& cd,
        const cpp::formattables::includes& inc) const;

    /**
     * @brief Manufacture all the file infos for the given exception.
     */
    cpp::formattables::file_info
    create(boost::shared_ptr<cpp::formattables::exception_info> ei,
        const cpp::formattables::content_descriptor& cd,
        const cpp::formattables::includes& inc) const;

    /**
     * @brief Manufacture all the file infos for the given namespace.
     */
    cpp::formattables::file_info
    create(boost::shared_ptr<cpp::formattables::namespace_info> ni,
        const cpp::formattables::content_descriptor& cd) const;

    /**
     * @brief Manufacture all the file infos for the given class.
     */
    cpp::formattables::file_info
    create(boost::shared_ptr<cpp::formattables::class_info> ci,
        const cpp::formattables::content_descriptor& cd,
        const cpp::formattables::includes& inc) const;

    /**
     * @brief Manufacture file info for includer.
     */
    cpp::formattables::file_info
    create_includer(const cpp::formattables::content_descriptor& cd,
        const cpp::formattables::includes& inc) const;

    /**
     * @brief Manufacture file info for registrar.
     */
    cpp::formattables::file_info
    create_registrar(boost::shared_ptr<cpp::formattables::registrar_info> ri,
        const cpp::formattables::content_descriptor& cd,
        const cpp::formattables::includes& inc) const;

    /**
     * @brief Manufacture file info for visitor.
     */
    cpp::formattables::file_info
    create_visitor(boost::shared_ptr<cpp::formattables::visitor_info> vi,
        const cpp::formattables::content_descriptor& cd,
        const cpp::formattables::includes& inc) const;

private:
    const locator& locator_;
};

} }

#endif
