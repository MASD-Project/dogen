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
#ifndef DOGEN_CONFIG_TYPES_KNITTING_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_KNITTING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/config/serialization/knitting_settings_fwd_ser.hpp"
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/config/types/input_settings.hpp"
#include "dogen/config/types/output_settings.hpp"
#include "dogen/config/types/troubleshooting_settings.hpp"

namespace dogen {
namespace config {

/**
 * @brief Settings related to the knit library.
 */
class knitting_settings final {
public:
    knitting_settings(const knitting_settings&) = default;
    knitting_settings(knitting_settings&&) = default;
    ~knitting_settings() = default;

public:
    knitting_settings();

public:
    knitting_settings(
        const bool verbose,
        const dogen::config::input_settings& input,
        const dogen::config::troubleshooting_settings& troubleshooting,
        const dogen::config::output_settings& output,
        const dogen::config::cpp_settings& cpp);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const knitting_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, knitting_settings& v, unsigned int version);

public:
    /**
     * @brief Provide additional diagnostic information in the log file.
     */
    /**@{*/
    bool verbose() const;
    void verbose(const bool v);
    /**@}*/

    /**
     * @brief All settings related to inputs.
     */
    /**@{*/
    const dogen::config::input_settings& input() const;
    dogen::config::input_settings& input();
    void input(const dogen::config::input_settings& v);
    void input(const dogen::config::input_settings&& v);
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
     * @brief All settings related to C++.
     */
    /**@{*/
    const dogen::config::cpp_settings& cpp() const;
    dogen::config::cpp_settings& cpp();
    void cpp(const dogen::config::cpp_settings& v);
    void cpp(const dogen::config::cpp_settings&& v);
    /**@}*/

public:
    bool operator==(const knitting_settings& rhs) const;
    bool operator!=(const knitting_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(knitting_settings& other) noexcept;
    knitting_settings& operator=(knitting_settings other);

private:
    bool verbose_;
    dogen::config::input_settings input_;
    dogen::config::troubleshooting_settings troubleshooting_;
    dogen::config::output_settings output_;
    dogen::config::cpp_settings cpp_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::knitting_settings& lhs,
    dogen::config::knitting_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
