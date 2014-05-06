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
#ifndef DOGEN_CONFIG_TYPES_TROUBLESHOOTING_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_TROUBLESHOOTING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/config/serialization/troubleshooting_settings_fwd_ser.hpp"
#include "dogen/config/types/archive_types.hpp"

namespace dogen {
namespace config {

class troubleshooting_settings final {
public:
    troubleshooting_settings(const troubleshooting_settings&) = default;
    ~troubleshooting_settings() = default;

public:
    troubleshooting_settings();

public:
    troubleshooting_settings(troubleshooting_settings&& rhs);

public:
    troubleshooting_settings(
        const boost::filesystem::path& debug_dir,
        const dogen::config::archive_types& save_dia_model,
        const dogen::config::archive_types& save_sml_model,
        const bool stop_after_formatting,
        const bool stop_after_merging);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const troubleshooting_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, troubleshooting_settings& v, unsigned int version);

public:
    /**
     * @brief Directory for debug files.
     */
    /**@{*/
    const boost::filesystem::path& debug_dir() const;
    boost::filesystem::path& debug_dir();
    void debug_dir(const boost::filesystem::path& v);
    void debug_dir(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief If not invalid, serialise dia model to file using the
     * specified archive type.
     */
    /**@{*/
    dogen::config::archive_types save_dia_model() const;
    void save_dia_model(const dogen::config::archive_types& v);
    /**@}*/

    /**
     * @brief If not invalid, serialise sml model to file using the
     * specified archive type.
     */
    /**@{*/
    dogen::config::archive_types save_sml_model() const;
    void save_sml_model(const dogen::config::archive_types& v);
    /**@}*/

    /**
     * @brief Stop dogen after code generating into memory but before
     * writing to output.
     */
    /**@{*/
    bool stop_after_formatting() const;
    void stop_after_formatting(const bool v);
    /**@}*/

    /**
     * @brief Stop dogen after code generating into memory but before
     * writing to output.
     */
    /**@{*/
    bool stop_after_merging() const;
    void stop_after_merging(const bool v);
    /**@}*/

public:
    bool operator==(const troubleshooting_settings& rhs) const;
    bool operator!=(const troubleshooting_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(troubleshooting_settings& other) noexcept;
    troubleshooting_settings& operator=(troubleshooting_settings other);

private:
    boost::filesystem::path debug_dir_;
    dogen::config::archive_types save_dia_model_;
    dogen::config::archive_types save_sml_model_;
    bool stop_after_formatting_;
    bool stop_after_merging_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::troubleshooting_settings& lhs,
    dogen::config::troubleshooting_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
