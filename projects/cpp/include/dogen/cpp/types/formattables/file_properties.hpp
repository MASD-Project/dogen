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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FILE_PROPERTIES_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FILE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/formattables/file_properties_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class file_properties final {
public:
    file_properties() = default;
    file_properties(const file_properties&) = default;
    ~file_properties() = default;

public:
    file_properties(file_properties&& rhs);

public:
    file_properties(
        const boost::filesystem::path& file_path,
        const boost::filesystem::path& include_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file_properties& v, unsigned int version);

public:
    /**
     * @brief Path to the file, indicating the location in the file system where it will be written.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Path to the file to be used for inclusion.
     */
    /**@{*/
    const boost::filesystem::path& include_path() const;
    boost::filesystem::path& include_path();
    void include_path(const boost::filesystem::path& v);
    void include_path(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const file_properties& rhs) const;
    bool operator!=(const file_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_properties& other) noexcept;
    file_properties& operator=(file_properties other);

private:
    boost::filesystem::path file_path_;
    boost::filesystem::path include_path_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::file_properties& lhs,
    dogen::cpp::formattables::file_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
