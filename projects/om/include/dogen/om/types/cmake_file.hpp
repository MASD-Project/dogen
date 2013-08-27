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
#ifndef DOGEN_OM_TYPES_CMAKE_FILE_HPP
#define DOGEN_OM_TYPES_CMAKE_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/cmake_file_fwd_ser.hpp"
#include "dogen/om/types/cmake_feature_fwd.hpp"
#include "dogen/om/types/text_file.hpp"

namespace dogen {
namespace om {

class cmake_file final : public dogen::om::text_file {
public:
    cmake_file() = default;
    cmake_file(const cmake_file&) = default;
    cmake_file(cmake_file&&) = default;

    virtual ~cmake_file() noexcept { }

public:
    cmake_file(
        const boost::filesystem::path& full_path,
        const boost::filesystem::path& relative_path,
        const dogen::om::preamble& preamble,
        const boost::optional<dogen::om::code_generation_marker>& marker,
        const dogen::om::licence& licence,
        const std::list<boost::shared_ptr<dogen::om::cmake_feature> >& features);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cmake_file& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cmake_file& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<boost::shared_ptr<dogen::om::cmake_feature> >& features() const;
    std::list<boost::shared_ptr<dogen::om::cmake_feature> >& features();
    void features(const std::list<boost::shared_ptr<dogen::om::cmake_feature> >& v);
    void features(const std::list<boost::shared_ptr<dogen::om::cmake_feature> >&& v);

public:
    bool operator==(const cmake_file& rhs) const;
    bool operator!=(const cmake_file& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::text_file& other) const override;

public:
    void swap(cmake_file& other) noexcept;
    cmake_file& operator=(cmake_file other);

private:
    std::list<boost::shared_ptr<dogen::om::cmake_feature> > features_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cmake_file& lhs,
    dogen::om::cmake_file& rhs) {
    lhs.swap(rhs);
}

}

#endif
