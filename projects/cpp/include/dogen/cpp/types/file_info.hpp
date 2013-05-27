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
#ifndef DOGEN_CPP_TYPES_FILE_INFO_HPP
#define DOGEN_CPP_TYPES_FILE_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
#include <list>
#include <string>
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/cpp/serialization/file_info_fwd_ser.hpp"
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/sml/types/category_types.hpp"
#include "dogen/sml/types/meta_types.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a C++ header or implementation file.
 */
class file_info final {
public:
    file_info(const file_info&) = default;
    ~file_info() = default;

public:
    file_info();

public:
    file_info(file_info&& rhs);

public:
    file_info(
        const dogen::config::cpp_facet_types& facet_type,
        const dogen::cpp::file_types& file_type,
        const dogen::cpp::aspect_types& aspect_type,
        const dogen::sml::category_types& category_type,
        const dogen::sml::meta_types& meta_type,
        const boost::optional<dogen::cpp::class_info>& class_info,
        const boost::optional<dogen::cpp::enum_info>& enum_info,
        const boost::optional<dogen::cpp::exception_info>& exception_info,
        const boost::optional<dogen::cpp::registrar_info>& registrar_info,
        const std::string& header_guard,
        const std::list<std::string>& system_includes,
        const std::list<std::string>& user_includes,
        const boost::filesystem::path& file_path,
        const boost::optional<dogen::cpp::namespace_info>& namespace_info,
        const boost::optional<dogen::cpp::visitor_info>& visitor_info,
        const boost::filesystem::path& relative_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file_info& v, unsigned int version);

public:
    /**
     * @brief Facet that this file represents.
     */
    /**@{*/
    dogen::config::cpp_facet_types facet_type() const;
    void facet_type(const dogen::config::cpp_facet_types& v);
    /**@}*/

    /**
     * @brief Type of the file.
     */
    /**@{*/
    dogen::cpp::file_types file_type() const;
    void file_type(const dogen::cpp::file_types& v);
    /**@}*/

    /**
     * @brief Aspect that this file represents.
     */
    /**@{*/
    dogen::cpp::aspect_types aspect_type() const;
    void aspect_type(const dogen::cpp::aspect_types& v);
    /**@}*/

    /**
     * @brief Category of the contained pod.
     */
    /**@{*/
    dogen::sml::category_types category_type() const;
    void category_type(const dogen::sml::category_types& v);
    /**@}*/

    /**
     * @brief Meta type of the contained type.
     */
    /**@{*/
    dogen::sml::meta_types meta_type() const;
    void meta_type(const dogen::sml::meta_types& v);
    /**@}*/

    /**
     * @brief If non-empty, the file contains a class.
     */
    /**@{*/
    const boost::optional<dogen::cpp::class_info>& class_info() const;
    boost::optional<dogen::cpp::class_info>& class_info();
    void class_info(const boost::optional<dogen::cpp::class_info>& v);
    void class_info(const boost::optional<dogen::cpp::class_info>&& v);
    /**@}*/

    /**
     * @brief If non-empty, the file contains an enum.
     */
    /**@{*/
    const boost::optional<dogen::cpp::enum_info>& enum_info() const;
    boost::optional<dogen::cpp::enum_info>& enum_info();
    void enum_info(const boost::optional<dogen::cpp::enum_info>& v);
    void enum_info(const boost::optional<dogen::cpp::enum_info>&& v);
    /**@}*/

    /**
     * @brief If non-empty, the file contains an exception.
     */
    /**@{*/
    const boost::optional<dogen::cpp::exception_info>& exception_info() const;
    boost::optional<dogen::cpp::exception_info>& exception_info();
    void exception_info(const boost::optional<dogen::cpp::exception_info>& v);
    void exception_info(const boost::optional<dogen::cpp::exception_info>&& v);
    /**@}*/

    /**
     * @brief If non-empty, the file contains a registrar.
     */
    /**@{*/
    const boost::optional<dogen::cpp::registrar_info>& registrar_info() const;
    boost::optional<dogen::cpp::registrar_info>& registrar_info();
    void registrar_info(const boost::optional<dogen::cpp::registrar_info>& v);
    void registrar_info(const boost::optional<dogen::cpp::registrar_info>&& v);
    /**@}*/

    /**
     * @brief If file type is header, name to use for header guards.
     */
    /**@{*/
    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);
    /**@}*/

    /**
     * @brief List of files to include using angle brackets.
     */
    /**@{*/
    const std::list<std::string>& system_includes() const;
    std::list<std::string>& system_includes();
    void system_includes(const std::list<std::string>& v);
    void system_includes(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief List of files to include using quotes.
     */
    /**@{*/
    const std::list<std::string>& user_includes() const;
    std::list<std::string>& user_includes();
    void user_includes(const std::list<std::string>& v);
    void user_includes(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Path to the file.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Namespaces in which to include the type.
     */
    /**@{*/
    const boost::optional<dogen::cpp::namespace_info>& namespace_info() const;
    boost::optional<dogen::cpp::namespace_info>& namespace_info();
    void namespace_info(const boost::optional<dogen::cpp::namespace_info>& v);
    void namespace_info(const boost::optional<dogen::cpp::namespace_info>&& v);
    /**@}*/

    /**
     * @brief If non-empty, file includes a visitor.
     */
    /**@{*/
    const boost::optional<dogen::cpp::visitor_info>& visitor_info() const;
    boost::optional<dogen::cpp::visitor_info>& visitor_info();
    void visitor_info(const boost::optional<dogen::cpp::visitor_info>& v);
    void visitor_info(const boost::optional<dogen::cpp::visitor_info>&& v);
    /**@}*/

    /**
     * @brief Relative path to file.
     */
    /**@{*/
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const file_info& rhs) const;
    bool operator!=(const file_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_info& other) noexcept;
    file_info& operator=(file_info other);

private:
    dogen::config::cpp_facet_types facet_type_;
    dogen::cpp::file_types file_type_;
    dogen::cpp::aspect_types aspect_type_;
    dogen::sml::category_types category_type_;
    dogen::sml::meta_types meta_type_;
    boost::optional<dogen::cpp::class_info> class_info_;
    boost::optional<dogen::cpp::enum_info> enum_info_;
    boost::optional<dogen::cpp::exception_info> exception_info_;
    boost::optional<dogen::cpp::registrar_info> registrar_info_;
    std::string header_guard_;
    std::list<std::string> system_includes_;
    std::list<std::string> user_includes_;
    boost::filesystem::path file_path_;
    boost::optional<dogen::cpp::namespace_info> namespace_info_;
    boost::optional<dogen::cpp::visitor_info> visitor_info_;
    boost::filesystem::path relative_path_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::file_info& lhs,
    dogen::cpp::file_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
