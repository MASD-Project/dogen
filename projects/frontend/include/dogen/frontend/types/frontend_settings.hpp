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
#ifndef DOGEN_FRONTEND_TYPES_FRONTEND_SETTINGS_HPP
#define DOGEN_FRONTEND_TYPES_FRONTEND_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/frontend/serialization/frontend_settings_fwd_ser.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Settings that control the reading abilities of the frontend.
 */
class frontend_settings final {
public:
    frontend_settings(const frontend_settings&) = default;
    ~frontend_settings() = default;

public:
    frontend_settings();

public:
    frontend_settings(frontend_settings&& rhs);

public:
    frontend_settings(
        const bool save_pre_processed_input,
        const boost::filesystem::path& pre_processed_input_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const frontend_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, frontend_settings& v, unsigned int version);

public:
    /**
     * @brief If true, the frontend will try to save the original input after
     * initial parsing.
     *
     * Note that this option only makes sense if the frontend is
     * transforming a format into SML. It is ignored in cases where
     * we are reading an SML representation.
     */
    /**@{*/
    bool save_pre_processed_input() const;
    void save_pre_processed_input(const bool v);
    /**@}*/

    /**
     * @brief Full path to use for the frontend's pre-processed input.
     */
    /**@{*/
    const boost::filesystem::path& pre_processed_input_path() const;
    boost::filesystem::path& pre_processed_input_path();
    void pre_processed_input_path(const boost::filesystem::path& v);
    void pre_processed_input_path(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const frontend_settings& rhs) const;
    bool operator!=(const frontend_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(frontend_settings& other) noexcept;
    frontend_settings& operator=(frontend_settings other);

private:
    bool save_pre_processed_input_;
    boost::filesystem::path pre_processed_input_path_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::frontend::frontend_settings& lhs,
    dogen::frontend::frontend_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
