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
#ifndef DOGEN_FRONTEND_TYPES_PROVIDER_SETTINGS_HPP
#define DOGEN_FRONTEND_TYPES_PROVIDER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/frontend/serialization/provider_settings_fwd_ser.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Settings that control the reading abilities of the provider.
 */
class provider_settings final {
public:
    provider_settings(const provider_settings&) = default;
    ~provider_settings() = default;

public:
    provider_settings();

public:
    provider_settings(provider_settings&& rhs);

public:
    provider_settings(
        const bool save_pre_processed_input,
        const boost::filesystem::path& pre_processed_input_path,
        const bool disable_model_module);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const provider_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, provider_settings& v, unsigned int version);

public:
    /**
     * @brief If true, the provider will try to save the original input after
     * initial parsing.
     *
     * Note that this option only makes sense if the provider is
     * transforming a format into SML. It is ignored in cases where
     * we are reading an SML representation.
     */
    /**@{*/
    bool save_pre_processed_input() const;
    void save_pre_processed_input(const bool v);
    /**@}*/

    /**
     * @brief Full path to use for the provider's pre-processed input.
     */
    /**@{*/
    const boost::filesystem::path& pre_processed_input_path() const;
    boost::filesystem::path& pre_processed_input_path();
    void pre_processed_input_path(const boost::filesystem::path& v);
    void pre_processed_input_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief If true, the model module is not generated.
     */
    /**@{*/
    bool disable_model_module() const;
    void disable_model_module(const bool v);
    /**@}*/

public:
    bool operator==(const provider_settings& rhs) const;
    bool operator!=(const provider_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(provider_settings& other) noexcept;
    provider_settings& operator=(provider_settings other);

private:
    bool save_pre_processed_input_;
    boost::filesystem::path pre_processed_input_path_;
    bool disable_model_module_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::frontend::provider_settings& lhs,
    dogen::frontend::provider_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
