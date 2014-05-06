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
#ifndef DOGEN_CONFIG_TYPES_ANNOTATION_SETTINGS_HPP
#define DOGEN_CONFIG_TYPES_ANNOTATION_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/config/serialization/annotation_settings_fwd_ser.hpp"
#include "dogen/config/types/code_generation_marker_settings.hpp"

namespace dogen {
namespace config {

/**
 * @brief Set of properties associated with an entity.
 */
class annotation_settings final {
public:
    annotation_settings(const annotation_settings&) = default;
    annotation_settings(annotation_settings&&) = default;
    ~annotation_settings() = default;

public:
    annotation_settings();

public:
    annotation_settings(
        const bool generate_preamble,
        const std::list<std::string>& copyright,
        const std::string& licence_name,
        const std::list<std::string>& modeline_group_name,
        const dogen::config::code_generation_marker_settings& code_generation_marker);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const annotation_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, annotation_settings& v, unsigned int version);

public:
    /**
     * @brief If set to true, the preamble will be generated.
     *
     * The preamble is made up of a modeline, copyright information and licensing
     * details.
     */
    /**@{*/
    bool generate_preamble() const;
    void generate_preamble(const bool v);
    /**@}*/

    /**
     * @brief Key used to denote copyright holders.
     *
     * It is expected to be repeated in a model; order is kept as provided by user.
     */
    /**@{*/
    const std::list<std::string>& copyright() const;
    std::list<std::string>& copyright();
    void copyright(const std::list<std::string>& v);
    void copyright(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the legal licence to use.
     *
     * Must match licences available in library.
     */
    /**@{*/
    const std::string& licence_name() const;
    std::string& licence_name();
    void licence_name(const std::string& v);
    void licence_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the modeline groups to use.
     *
     * Must match licences available in library.
     */
    /**@{*/
    const std::list<std::string>& modeline_group_name() const;
    std::list<std::string>& modeline_group_name();
    void modeline_group_name(const std::list<std::string>& v);
    void modeline_group_name(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Settings related to the code generation marker.
     */
    /**@{*/
    const dogen::config::code_generation_marker_settings& code_generation_marker() const;
    dogen::config::code_generation_marker_settings& code_generation_marker();
    void code_generation_marker(const dogen::config::code_generation_marker_settings& v);
    void code_generation_marker(const dogen::config::code_generation_marker_settings&& v);
    /**@}*/

public:
    bool operator==(const annotation_settings& rhs) const;
    bool operator!=(const annotation_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(annotation_settings& other) noexcept;
    annotation_settings& operator=(annotation_settings other);

private:
    bool generate_preamble_;
    std::list<std::string> copyright_;
    std::string licence_name_;
    std::list<std::string> modeline_group_name_;
    dogen::config::code_generation_marker_settings code_generation_marker_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::annotation_settings& lhs,
    dogen::config::annotation_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
