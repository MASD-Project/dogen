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
#ifndef DOGEN_FORMATTERS_TYPES_GENERAL_PROPERTY_SHEET_HPP
#define DOGEN_FORMATTERS_TYPES_GENERAL_PROPERTY_SHEET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/formatters/serialization/general_property_sheet_fwd_ser.hpp"
#include "dogen/formatters/types/code_generation_marker_property_sheet.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Set of properties associated with an entity.
 */
class general_property_sheet final {
public:
    general_property_sheet(const general_property_sheet&) = default;
    general_property_sheet(general_property_sheet&&) = default;
    ~general_property_sheet() = default;

public:
    general_property_sheet();

public:
    general_property_sheet(
        const bool enabled,
        const bool generate_preamble,
        const std::list<std::string>& copyright,
        const std::string& licence_name,
        const std::string& modeline_group_name,
        const dogen::formatters::code_generation_marker_property_sheet& code_generation_marker,
        const std::string& feature_directory_name,
        const bool enable_facet_directories,
        const std::string& facet_directory_name,
        const std::string& facet_postfix,
        const bool overwrite,
        const std::string& file_name,
        const std::string& file_postfix,
        const std::string& extension,
        const bool enable_unique_file_names);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const general_property_sheet& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, general_property_sheet& v, unsigned int version);

public:
    /**
     * @brief If set to false, the file will not be generated.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

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
     * @brief Name of the modeline group to use.
     *
     * Must match licences available in library.
     */
    /**@{*/
    const std::string& modeline_group_name() const;
    std::string& modeline_group_name();
    void modeline_group_name(const std::string& v);
    void modeline_group_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Properties related to the code generation marker.
     */
    /**@{*/
    const dogen::formatters::code_generation_marker_property_sheet& code_generation_marker() const;
    dogen::formatters::code_generation_marker_property_sheet& code_generation_marker();
    void code_generation_marker(const dogen::formatters::code_generation_marker_property_sheet& v);
    void code_generation_marker(const dogen::formatters::code_generation_marker_property_sheet&& v);
    /**@}*/

    /**
     * @brief Directory name used for the feature to which this file belongs.
     */
    /**@{*/
    const std::string& feature_directory_name() const;
    std::string& feature_directory_name();
    void feature_directory_name(const std::string& v);
    void feature_directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, files for each facet will be placed in a folder for the facet.
     */
    /**@{*/
    bool enable_facet_directories() const;
    void enable_facet_directories(const bool v);
    /**@}*/

    /**
     * @brief Directory name used for the facet to which this file belongs.
     */
    /**@{*/
    const std::string& facet_directory_name() const;
    std::string& facet_directory_name();
    void facet_directory_name(const std::string& v);
    void facet_directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Postfix for all file names in the facet to which this file belongs.
     */
    /**@{*/
    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);
    /**@}*/

    /**
     * @brief Should we overwrite a file with this name if one exists?
     */
    /**@{*/
    bool overwrite() const;
    void overwrite(const bool v);
    /**@}*/

    /**
     * @brief Name of the file, without any other component such as extension, etc.
     */
    /**@{*/
    const std::string& file_name() const;
    std::string& file_name();
    void file_name(const std::string& v);
    void file_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Postfix for all files of this type.
     */
    /**@{*/
    const std::string& file_postfix() const;
    std::string& file_postfix();
    void file_postfix(const std::string& v);
    void file_postfix(const std::string&& v);
    /**@}*/

    /**
     * @brief Extension for this file.
     */
    /**@{*/
    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, each file in each facet will have a name unique across all facets.
     *
     * This is achieved by using the facet's postfix.
     */
    /**@{*/
    bool enable_unique_file_names() const;
    void enable_unique_file_names(const bool v);
    /**@}*/

public:
    bool operator==(const general_property_sheet& rhs) const;
    bool operator!=(const general_property_sheet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(general_property_sheet& other) noexcept;
    general_property_sheet& operator=(general_property_sheet other);

private:
    bool enabled_;
    bool generate_preamble_;
    std::list<std::string> copyright_;
    std::string licence_name_;
    std::string modeline_group_name_;
    dogen::formatters::code_generation_marker_property_sheet code_generation_marker_;
    std::string feature_directory_name_;
    bool enable_facet_directories_;
    std::string facet_directory_name_;
    std::string facet_postfix_;
    bool overwrite_;
    std::string file_name_;
    std::string file_postfix_;
    std::string extension_;
    bool enable_unique_file_names_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::general_property_sheet& lhs,
    dogen::formatters::general_property_sheet& rhs) {
    lhs.swap(rhs);
}

}

#endif
