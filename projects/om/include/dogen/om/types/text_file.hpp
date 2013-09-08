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
#ifndef DOGEN_OM_TYPES_TEXT_FILE_HPP
#define DOGEN_OM_TYPES_TEXT_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
#include <iosfwd>
#include "dogen/om/serialization/text_file_fwd_ser.hpp"
#include "dogen/om/types/code_generation_marker.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/modeline.hpp"

namespace dogen {
namespace om {

/**
 * @brief Represents a text file.
 */
class text_file {
public:
    text_file() = default;
    text_file(const text_file&) = default;

    virtual ~text_file() noexcept = 0;

public:
    text_file(text_file&& rhs);

public:
    text_file(
        const boost::filesystem::path& full_path,
        const boost::filesystem::path& relative_path,
        const dogen::om::modeline& modeline,
        const boost::optional<dogen::om::code_generation_marker>& marker,
        const dogen::om::licence& licence);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const text_file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, text_file& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

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
     * @brief The editor variables for this file.
     */
    /**@{*/
    const dogen::om::modeline& modeline() const;
    dogen::om::modeline& modeline();
    void modeline(const dogen::om::modeline& v);
    void modeline(const dogen::om::modeline&& v);
    /**@}*/

    const boost::optional<dogen::om::code_generation_marker>& marker() const;
    boost::optional<dogen::om::code_generation_marker>& marker();
    void marker(const boost::optional<dogen::om::code_generation_marker>& v);
    void marker(const boost::optional<dogen::om::code_generation_marker>&& v);

    /**
     * @brief Licence for the content on the file.
     */
    /**@{*/
    const dogen::om::licence& licence() const;
    dogen::om::licence& licence();
    void licence(const dogen::om::licence& v);
    void licence(const dogen::om::licence&& v);
    /**@}*/

protected:
    bool compare(const text_file& rhs) const;
public:
    virtual bool equals(const text_file& other) const = 0;

protected:
    void swap(text_file& other) noexcept;

private:
    boost::filesystem::path full_path_;
    boost::filesystem::path relative_path_;
    dogen::om::modeline modeline_;
    boost::optional<dogen::om::code_generation_marker> marker_;
    dogen::om::licence licence_;
};

inline text_file::~text_file() noexcept { }

inline bool operator==(const text_file& lhs, const text_file& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
