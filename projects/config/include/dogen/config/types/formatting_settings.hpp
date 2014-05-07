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
#ifndef DOGEN_CONFIG_TYPES_FORMATTING_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_FORMATTING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/config/serialization/formatting_settings_fwd_ser.hpp"
#include "dogen/config/types/annotation_settings.hpp"
#include "dogen/config/types/cpp_settings.hpp"

namespace dogen {
namespace config {

/**
 * @brief Settings for the formatting libraries.
 */
class formatting_settings final {
public:
    formatting_settings(const formatting_settings&) = default;
    formatting_settings(formatting_settings&&) = default;
    ~formatting_settings() = default;

public:
    formatting_settings();

public:
    formatting_settings(
        const dogen::config::cpp_settings& cpp,
        const dogen::config::annotation_settings& annotation,
        const bool disable_model_module);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formatting_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formatting_settings& v, unsigned int version);

public:
    /**
     * @brief All settings related to C++.
     */
    /**@{*/
    const dogen::config::cpp_settings& cpp() const;
    dogen::config::cpp_settings& cpp();
    void cpp(const dogen::config::cpp_settings& v);
    void cpp(const dogen::config::cpp_settings&& v);
    /**@}*/

    /**
     * @brief All settings related to file annotations.
     */
    /**@{*/
    const dogen::config::annotation_settings& annotation() const;
    dogen::config::annotation_settings& annotation();
    void annotation(const dogen::config::annotation_settings& v);
    void annotation(const dogen::config::annotation_settings&& v);
    /**@}*/

    /**
     * @brief Do not generate a top-level module with the model name.
     */
    /**@{*/
    bool disable_model_module() const;
    void disable_model_module(const bool v);
    /**@}*/

public:
    bool operator==(const formatting_settings& rhs) const;
    bool operator!=(const formatting_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatting_settings& other) noexcept;
    formatting_settings& operator=(formatting_settings other);

private:
    dogen::config::cpp_settings cpp_;
    dogen::config::annotation_settings annotation_;
    bool disable_model_module_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::formatting_settings& lhs,
    dogen::config::formatting_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
