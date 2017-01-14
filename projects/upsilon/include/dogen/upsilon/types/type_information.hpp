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
#ifndef DOGEN_UPSILON_TYPES_TYPE_INFORMATION_HPP
#define DOGEN_UPSILON_TYPES_TYPE_INFORMATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/upsilon/types/type_information_entry.hpp"
#include "dogen/upsilon/serialization/type_information_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class type_information final {
public:
    type_information() = default;
    type_information(const type_information&) = default;
    ~type_information() = default;

public:
    type_information(type_information&& rhs);

public:
    type_information(
        const std::vector<dogen::upsilon::type_information_entry>& entries,
        const boost::filesystem::path& file_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::type_information& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::type_information& v, unsigned int version);

public:
    const std::vector<dogen::upsilon::type_information_entry>& entries() const;
    std::vector<dogen::upsilon::type_information_entry>& entries();
    void entries(const std::vector<dogen::upsilon::type_information_entry>& v);
    void entries(const std::vector<dogen::upsilon::type_information_entry>&& v);

    const boost::filesystem::path& file_name() const;
    boost::filesystem::path& file_name();
    void file_name(const boost::filesystem::path& v);
    void file_name(const boost::filesystem::path&& v);

public:
    bool operator==(const type_information& rhs) const;
    bool operator!=(const type_information& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_information& other) noexcept;
    type_information& operator=(type_information other);

private:
    std::vector<dogen::upsilon::type_information_entry> entries_;
    boost::filesystem::path file_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::type_information& lhs,
    dogen::upsilon::type_information& rhs) {
    lhs.swap(rhs);
}

}

#endif
