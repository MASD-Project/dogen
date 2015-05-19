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
#ifndef DOGEN_CPP_TYPES_SETTINGS_PATH_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_PATH_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/serialization/settings/path_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class path_settings final {
public:
    path_settings(const path_settings&) = default;
    ~path_settings() = default;

public:
    path_settings();

public:
    path_settings(path_settings&& rhs);

public:
    path_settings(
        const bool split_project,
        const dogen::cpp::formatters::file_types& file_type,
        const std::string& facet_directory,
        const std::string& extension,
        const std::string& facet_postfix,
        const std::string& formatter_postfix,
        const boost::filesystem::path& project_directory_path,
        const boost::filesystem::path& source_directory_path,
        const boost::filesystem::path& include_directory_path,
        const std::string& include_directory_name,
        const std::string& source_directory_name,
        const bool disable_facet_directories);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const path_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, path_settings& v, unsigned int version);

public:
    bool split_project() const;
    void split_project(const bool v);

    dogen::cpp::formatters::file_types file_type() const;
    void file_type(const dogen::cpp::formatters::file_types& v);

    const std::string& facet_directory() const;
    std::string& facet_directory();
    void facet_directory(const std::string& v);
    void facet_directory(const std::string&& v);

    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);

    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);

    const std::string& formatter_postfix() const;
    std::string& formatter_postfix();
    void formatter_postfix(const std::string& v);
    void formatter_postfix(const std::string&& v);

    const boost::filesystem::path& project_directory_path() const;
    boost::filesystem::path& project_directory_path();
    void project_directory_path(const boost::filesystem::path& v);
    void project_directory_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& source_directory_path() const;
    boost::filesystem::path& source_directory_path();
    void source_directory_path(const boost::filesystem::path& v);
    void source_directory_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& include_directory_path() const;
    boost::filesystem::path& include_directory_path();
    void include_directory_path(const boost::filesystem::path& v);
    void include_directory_path(const boost::filesystem::path&& v);

    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    bool disable_facet_directories() const;
    void disable_facet_directories(const bool v);

public:
    bool operator==(const path_settings& rhs) const;
    bool operator!=(const path_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_settings& other) noexcept;
    path_settings& operator=(path_settings other);

private:
    bool split_project_;
    dogen::cpp::formatters::file_types file_type_;
    std::string facet_directory_;
    std::string extension_;
    std::string facet_postfix_;
    std::string formatter_postfix_;
    boost::filesystem::path project_directory_path_;
    boost::filesystem::path source_directory_path_;
    boost::filesystem::path include_directory_path_;
    std::string include_directory_name_;
    std::string source_directory_name_;
    bool disable_facet_directories_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::path_settings& lhs,
    dogen::cpp::settings::path_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
