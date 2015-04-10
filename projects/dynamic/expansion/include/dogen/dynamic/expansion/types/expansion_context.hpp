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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_EXPANSION_CONTEXT_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_EXPANSION_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/sml/types/model.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/expansion/serialization/expansion_context_fwd_ser.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

class expansion_context final {
public:
    expansion_context() = default;
    expansion_context(const expansion_context&) = default;
    expansion_context(expansion_context&&) = default;
    ~expansion_context() = default;

public:
    expansion_context(
        const dogen::sml::model& model,
        const dogen::dynamic::schema::repository& repository,
        const dogen::config::cpp_options& cpp_options);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const expansion_context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, expansion_context& v, unsigned int version);

public:
    const dogen::sml::model& model() const;
    dogen::sml::model& model();
    void model(const dogen::sml::model& v);
    void model(const dogen::sml::model&& v);

    const dogen::dynamic::schema::repository& repository() const;
    dogen::dynamic::schema::repository& repository();
    void repository(const dogen::dynamic::schema::repository& v);
    void repository(const dogen::dynamic::schema::repository&& v);

    /**
     * @brief Command-line supplied options for the c++ model.
     *
     * Note: this is here as a bridge to the legacy approach.
     */
    /**@{*/
    const dogen::config::cpp_options& cpp_options() const;
    dogen::config::cpp_options& cpp_options();
    void cpp_options(const dogen::config::cpp_options& v);
    void cpp_options(const dogen::config::cpp_options&& v);
    /**@}*/

public:
    bool operator==(const expansion_context& rhs) const;
    bool operator!=(const expansion_context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(expansion_context& other) noexcept;
    expansion_context& operator=(expansion_context other);

private:
    dogen::sml::model model_;
    dogen::dynamic::schema::repository repository_;
    dogen::config::cpp_options cpp_options_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::dynamic::expansion::expansion_context& lhs,
    dogen::dynamic::expansion::expansion_context& rhs) {
    lhs.swap(rhs);
}

}

#endif
