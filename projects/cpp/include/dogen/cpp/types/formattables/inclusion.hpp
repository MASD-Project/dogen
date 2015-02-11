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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/formattables/inclusion_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/inclusion_delimiter_types.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief C++ inclusion.
 *
 * The include dependencies we concern ourselves with are all files
 * required in order to successfully compile the current file. We make
 * the traditional distinction with regards to type of inclusion:
 *
 * @li @e System includes are those which are in the system include path and
 * are expected to be included using angle brackets;
 *
 *  @li @e User includes are those which are in the user include path
 *  and are expected to be included using double-quotes.
 */
class inclusion final {
public:
    inclusion(const inclusion&) = default;
    ~inclusion() = default;

public:
    inclusion();

public:
    inclusion(inclusion&& rhs);

public:
    inclusion(
        const boost::filesystem::path& inclusion_path,
        const dogen::cpp::formattables::inclusion_delimiter_types& inclusion_delimiter_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inclusion& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inclusion& v, unsigned int version);

public:
    /**
     * @brief Path to use in inclusion statement.
     *
     * These are expected to use angle brackets and be on the system path.
     */
    /**@{*/
    const boost::filesystem::path& inclusion_path() const;
    boost::filesystem::path& inclusion_path();
    void inclusion_path(const boost::filesystem::path& v);
    void inclusion_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Type of delimiter to use for the inclusion statement.
     */
    /**@{*/
    dogen::cpp::formattables::inclusion_delimiter_types inclusion_delimiter_type() const;
    void inclusion_delimiter_type(const dogen::cpp::formattables::inclusion_delimiter_types& v);
    /**@}*/

public:
    bool operator==(const inclusion& rhs) const;
    bool operator!=(const inclusion& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion& other) noexcept;
    inclusion& operator=(inclusion other);

private:
    boost::filesystem::path inclusion_path_;
    dogen::cpp::formattables::inclusion_delimiter_types inclusion_delimiter_type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::inclusion& lhs,
    dogen::cpp::formattables::inclusion& rhs) {
    lhs.swap(rhs);
}

}

#endif
