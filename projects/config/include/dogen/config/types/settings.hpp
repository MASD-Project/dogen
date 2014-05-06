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
#ifndef DOGEN_CONFIG_TYPES_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/config/serialization/settings_fwd_ser.hpp"
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/config/types/modeling_settings.hpp"
#include "dogen/config/types/output_settings.hpp"
#include "dogen/config/types/troubleshooting_settings.hpp"

namespace dogen {
namespace config {

class settings final {
public:
    settings(const settings&) = default;
    settings(settings&&) = default;
    ~settings() = default;

public:
    settings();

public:
    settings(
        const dogen::config::modeling_settings& modeling,
        const dogen::config::cpp_settings& cpp,
        const dogen::config::troubleshooting_settings& troubleshooting,
        const dogen::config::output_settings& output,
        const bool verbose);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, settings& v, unsigned int version);

public:
    /**
     * @brief All settings related to modeling.
     */
    /**@{*/
    const dogen::config::modeling_settings& modeling() const;
    dogen::config::modeling_settings& modeling();
    void modeling(const dogen::config::modeling_settings& v);
    void modeling(const dogen::config::modeling_settings&& v);
    /**@}*/

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
     * @brief All settings related to troubleshooting.
     */
    /**@{*/
    const dogen::config::troubleshooting_settings& troubleshooting() const;
    dogen::config::troubleshooting_settings& troubleshooting();
    void troubleshooting(const dogen::config::troubleshooting_settings& v);
    void troubleshooting(const dogen::config::troubleshooting_settings&& v);
    /**@}*/

    /**
     * @brief All settings related to outputting.
     */
    /**@{*/
    const dogen::config::output_settings& output() const;
    dogen::config::output_settings& output();
    void output(const dogen::config::output_settings& v);
    void output(const dogen::config::output_settings&& v);
    /**@}*/

    /**
     * @brief Provide additional diagnostic information in the log file.
     */
    /**@{*/
    bool verbose() const;
    void verbose(const bool v);
    /**@}*/

public:
    bool operator==(const settings& rhs) const;
    bool operator!=(const settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(settings& other) noexcept;
    settings& operator=(settings other);

private:
    dogen::config::modeling_settings modeling_;
    dogen::config::cpp_settings cpp_;
    dogen::config::troubleshooting_settings troubleshooting_;
    dogen::config::output_settings output_;
    bool verbose_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::settings& lhs,
    dogen::config::settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
