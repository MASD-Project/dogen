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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_PATH_INGREDIENTS_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_PATH_INGREDIENTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include "dogen/cpp/serialization/formatters/path_ingredients_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/inclusion_delimiter_types.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Ingredients required to build file and include paths.
 */
class path_ingredients final {
public:
    path_ingredients(const path_ingredients&) = default;
    ~path_ingredients() = default;

public:
    path_ingredients();

public:
    path_ingredients(path_ingredients&& rhs);

public:
    path_ingredients(
        const bool split_project,
        const dogen::cpp::formatters::file_types& file_type,
        const std::string& facet_directory,
        const std::string& extension,
        const std::string& facet_postfix,
        const std::string& formatter_postfix,
        const boost::filesystem::path& project_directory_path,
        const boost::filesystem::path& source_directory_path,
        const boost::filesystem::path& include_directory_path,
        const std::string& source_directory_name,
        const std::string& include_directory_name,
        const boost::filesystem::path& inclusion_path,
        const dogen::cpp::formattables::inclusion_delimiter_types& inclusion_delimiter_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const path_ingredients& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, path_ingredients& v, unsigned int version);

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

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

    const boost::filesystem::path& inclusion_path() const;
    boost::filesystem::path& inclusion_path();
    void inclusion_path(const boost::filesystem::path& v);
    void inclusion_path(const boost::filesystem::path&& v);

    dogen::cpp::formattables::inclusion_delimiter_types inclusion_delimiter_type() const;
    void inclusion_delimiter_type(const dogen::cpp::formattables::inclusion_delimiter_types& v);

public:
    bool operator==(const path_ingredients& rhs) const;
    bool operator!=(const path_ingredients& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_ingredients& other) noexcept;
    path_ingredients& operator=(path_ingredients other);

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
    std::string source_directory_name_;
    std::string include_directory_name_;
    boost::filesystem::path inclusion_path_;
    dogen::cpp::formattables::inclusion_delimiter_types inclusion_delimiter_type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formatters::path_ingredients& lhs,
    dogen::cpp::formatters::path_ingredients& rhs) {
    lhs.swap(rhs);
}

}

#endif
