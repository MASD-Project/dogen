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
#ifndef DOGEN_OM_TYPES_RESULT_HPP
#define DOGEN_OM_TYPES_RESULT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/om/serialization/result_fwd_ser.hpp"
#include "dogen/om/types/formatted_file.hpp"

namespace dogen {
namespace om {

class result final {
public:
    result() = default;
    result(const result&) = default;
    result(result&&) = default;
    ~result() = default;

public:
    explicit result(const std::list<dogen::om::formatted_file>& files);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const result& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, result& v, unsigned int version);

public:
    const std::list<dogen::om::formatted_file>& files() const;
    std::list<dogen::om::formatted_file>& files();
    void files(const std::list<dogen::om::formatted_file>& v);
    void files(const std::list<dogen::om::formatted_file>&& v);

public:
    bool operator==(const result& rhs) const;
    bool operator!=(const result& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(result& other) noexcept;
    result& operator=(result other);

private:
    std::list<dogen::om::formatted_file> files_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::result& lhs,
    dogen::om::result& rhs) {
    lhs.swap(rhs);
}

}

#endif
