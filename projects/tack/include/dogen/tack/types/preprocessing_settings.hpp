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
#ifndef DOGEN_TACK_TYPES_PREPROCESSING_SETTINGS_HPP
#define DOGEN_TACK_TYPES_PREPROCESSING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/tack/serialization/preprocessing_settings_fwd_ser.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Settings that control the management of preprocessed input.
 *
 * If present, the importer will try to save the original input after
 * initial parsing.
 *
 * Note that this option only makes sense if the importer has
 * some form of pre-processed input. It is ignored otherwise.
 */
class preprocessing_settings final {
public:
    preprocessing_settings() = default;
    preprocessing_settings(const preprocessing_settings&) = default;
    ~preprocessing_settings() = default;

public:
    preprocessing_settings(preprocessing_settings&& rhs);

public:
    preprocessing_settings(
        const boost::filesystem::path& directory,
        const std::string& extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const preprocessing_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, preprocessing_settings& v, unsigned int version);

public:
    /**
     * @brief Directory in which to save the pre-processed input files.
     */
    /**@{*/
    const boost::filesystem::path& directory() const;
    boost::filesystem::path& directory();
    void directory(const boost::filesystem::path& v);
    void directory(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief File extension for the preprocessed input. It will determine the format
     * of the input, using boost serialization.
     */
    /**@{*/
    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);
    /**@}*/

public:
    bool operator==(const preprocessing_settings& rhs) const;
    bool operator!=(const preprocessing_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(preprocessing_settings& other) noexcept;
    preprocessing_settings& operator=(preprocessing_settings other);

private:
    boost::filesystem::path directory_;
    std::string extension_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::preprocessing_settings& lhs,
    dogen::tack::preprocessing_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
