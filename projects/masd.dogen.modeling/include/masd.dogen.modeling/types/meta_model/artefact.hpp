/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef MASD_DOGEN_MODELING_TYPES_META_MODEL_ARTEFACT_HPP
#define MASD_DOGEN_MODELING_TYPES_META_MODEL_ARTEFACT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace masd::dogen::modeling::meta_model {

/**
 * @brief Artefact in a text model.
 */
class artefact final {
public:
    artefact(const artefact&) = default;
    ~artefact() = default;

public:
    artefact();

public:
    artefact(artefact&& rhs);

public:
    artefact(
        const boost::filesystem::path& path,
        const std::string& content,
        const bool overwrite,
        const std::vector<boost::filesystem::path>& dependencies);

public:
    /**
     * @brief Absolute path to the file, indicating the location in the filesystem where it will be written.
     */
    /**@{*/
    const boost::filesystem::path& path() const;
    boost::filesystem::path& path();
    void path(const boost::filesystem::path& v);
    void path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Content of the file.
     */
    /**@{*/
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);
    /**@}*/

    /**
     * @brief Determines when to write the file.
     *
     * If true, the file will always be written to the filesystem; if false, the file will
     * only be written to the filesystem if it does not exist.
     */
    /**@{*/
    bool overwrite() const;
    void overwrite(const bool v);
    /**@}*/

    /**
     * @brief Files in the project directory that this file depends on, but which are not generated.
     */
    /**@{*/
    const std::vector<boost::filesystem::path>& dependencies() const;
    std::vector<boost::filesystem::path>& dependencies();
    void dependencies(const std::vector<boost::filesystem::path>& v);
    void dependencies(const std::vector<boost::filesystem::path>&& v);
    /**@}*/

public:
    bool operator==(const artefact& rhs) const;
    bool operator!=(const artefact& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact& other) noexcept;
    artefact& operator=(artefact other);

private:
    boost::filesystem::path path_;
    std::string content_;
    bool overwrite_;
    std::vector<boost::filesystem::path> dependencies_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::modeling::meta_model::artefact& lhs,
    masd::dogen::modeling::meta_model::artefact& rhs) {
    lhs.swap(rhs);
}

}

#endif
