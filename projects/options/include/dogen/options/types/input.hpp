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
#ifndef DOGEN_OPTIONS_TYPES_INPUT_HPP
#define DOGEN_OPTIONS_TYPES_INPUT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/options/serialization/input_fwd_ser.hpp"

namespace dogen {
namespace options {

/**
 * @brief Reference to a model to load.
 */
class input final {
public:
    input() = default;
    input(const input&) = default;
    ~input() = default;

public:
    input(input&& rhs);

public:
    input(
        const boost::filesystem::path& path,
        const std::string& external_modules);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::options::input& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::options::input& v, unsigned int version);

public:
    /**
     * @brief Path to the model we're referring to.
     */
    /**@{*/
    const boost::filesystem::path& path() const;
    boost::filesystem::path& path();
    void path(const boost::filesystem::path& v);
    void path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief External modules that include this model.
     */
    /**@{*/
    const std::string& external_modules() const;
    std::string& external_modules();
    void external_modules(const std::string& v);
    void external_modules(const std::string&& v);
    /**@}*/

public:
    bool operator==(const input& rhs) const;
    bool operator!=(const input& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(input& other) noexcept;
    input& operator=(input other);

private:
    boost::filesystem::path path_;
    std::string external_modules_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::options::input& lhs,
    dogen::options::input& rhs) {
    lhs.swap(rhs);
}

}

#endif
