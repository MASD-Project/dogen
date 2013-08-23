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
#ifndef DOGEN_CPPIM_TYPES_TEXT_FILE_HPP
#define DOGEN_CPPIM_TYPES_TEXT_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include "dogen/cppim/serialization/text_file_fwd_ser.hpp"
#include "dogen/cppim/types/feature_fwd.hpp"

namespace dogen {
namespace cppim {

/**
 * @brief Represents a text file.
 */
class text_file final {
public:
    text_file() = default;
    text_file(const text_file&) = default;
    ~text_file() = default;

public:
    text_file(text_file&& rhs);

public:
    text_file(
        const boost::filesystem::path& full_path,
        const boost::filesystem::path& relative_path,
        const std::list<boost::shared_ptr<dogen::cppim::feature> >& features);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const text_file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, text_file& v, unsigned int version);

public:
    /**
     * @brief Full path to the file, including file name.
     */
    /**@{*/
    const boost::filesystem::path& full_path() const;
    boost::filesystem::path& full_path();
    void full_path(const boost::filesystem::path& v);
    void full_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Relative path to file, including file name.
     */
    /**@{*/
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief All elements that make up the file, in order of appearence.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::cppim::feature> >& features() const;
    std::list<boost::shared_ptr<dogen::cppim::feature> >& features();
    void features(const std::list<boost::shared_ptr<dogen::cppim::feature> >& v);
    void features(const std::list<boost::shared_ptr<dogen::cppim::feature> >&& v);
    /**@}*/

public:
    bool operator==(const text_file& rhs) const;
    bool operator!=(const text_file& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_file& other) noexcept;
    text_file& operator=(text_file other);

private:
    boost::filesystem::path full_path_;
    boost::filesystem::path relative_path_;
    std::list<boost::shared_ptr<dogen::cppim::feature> > features_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cppim::text_file& lhs,
    dogen::cppim::text_file& rhs) {
    lhs.swap(rhs);
}

}

#endif
