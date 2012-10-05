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
#ifndef DOGEN_GENERATOR_CONFIG_TROUBLESHOOTING_SETTINGS_HPP
#define DOGEN_GENERATOR_CONFIG_TROUBLESHOOTING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/utility/serialization/archive_types.hpp"

namespace dogen {
namespace generator {
namespace config {

class troubleshooting_settings {
public:
    troubleshooting_settings(const troubleshooting_settings&) = default;
    ~troubleshooting_settings() = default;
    troubleshooting_settings&
    operator=(const troubleshooting_settings&) = default;

public:
    typedef dogen::utility::serialization::archive_types archive_types;

    troubleshooting_settings() :
        verbose_(false),
        save_dia_model_(archive_types::invalid),
        save_sml_model_(archive_types::invalid),
        stop_after_formatting_(false),
        stop_after_merging_(false) { }

    troubleshooting_settings(troubleshooting_settings&& rhs)
    : verbose_(std::move(rhs.verbose_)),
      debug_dir_(std::move(rhs.debug_dir_)),
      save_dia_model_(std::move(rhs.save_dia_model_)),
      save_sml_model_(std::move(rhs.save_sml_model_)),
      stop_after_formatting_(std::move(rhs.stop_after_formatting_)),
      stop_after_merging_(std::move(rhs.stop_after_merging_)) { }

public:
    /**
     * @brief Print additional diagnostic information to standard output.
     */
    /**@{*/
    bool verbose() const { return verbose_; }
    troubleshooting_settings& verbose(bool value) {
        verbose_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Directory for debug files.
     */
    /**@{*/
    troubleshooting_settings& debug_dir(boost::filesystem::path value) {
        debug_dir_ = value;
        return *this;
    }
    boost::filesystem::path debug_dir() const { return debug_dir_; }
    /**@}*/

    /**
     * @brief If not invalid, serialise dia model to file using the
     * specified archive type.
     */
    troubleshooting_settings& save_dia_model(archive_types value) {
        save_dia_model_ = value;
        return *this;
    }
    archive_types save_dia_model() const { return save_dia_model_; }

    /**
     * @brief If not invalid, serialise sml model to file using the
     * specified archive type.
     */
    troubleshooting_settings& save_sml_model(archive_types value) {
        save_sml_model_ = value;
        return *this;
    }
    archive_types save_sml_model() const { return save_sml_model_; }

    /**
     * @brief Stop dogen after code generating into memory but before
     * writing to output.
     */
    /**@{*/
    bool stop_after_formatting() const { return stop_after_formatting_; }
    troubleshooting_settings& stop_after_formatting(bool value) {
        stop_after_formatting_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Stop dogen after code generating into memory but before
     * writing to output.
     */
    /**@{*/
    bool stop_after_merging() const { return stop_after_merging_; }
    troubleshooting_settings& stop_after_merging(bool value) {
        stop_after_merging_ = value;
        return *this;
    }
    /**@}*/

private:
    bool verbose_;
    boost::filesystem::path debug_dir_;
    archive_types save_dia_model_;
    archive_types save_sml_model_;
    bool stop_after_formatting_;
    bool stop_after_merging_;
};

std::ostream& operator<<(std::ostream& stream, troubleshooting_settings value);

} } }

#endif
