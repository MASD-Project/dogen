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
#ifndef DOGEN_FRONTEND_TYPES_WORKFLOW_SETTINGS_HPP
#define DOGEN_FRONTEND_TYPES_WORKFLOW_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/frontend/serialization/workflow_settings_fwd_ser.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Settings that control the abilities of the workflow.
 */
class workflow_settings final {
public:
    workflow_settings(const workflow_settings&) = default;
    workflow_settings(workflow_settings&&) = default;
    ~workflow_settings() = default;

public:
    workflow_settings();

public:
    workflow_settings(
        const bool save_original_input,
        const std::string& original_input_extension,
        const bool save_intermediate_sml,
        const bool save_merged_sml,
        const std::string& sml_extension,
        const bool disable_model_module);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const workflow_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, workflow_settings& v, unsigned int version);

public:
    /**
     * @brief If true, the workflow will save the source's original input after parsing.
     */
    /**@{*/
    bool save_original_input() const;
    void save_original_input(const bool v);
    /**@}*/

    /**
     * @brief Extension to use for the source's original input.
     *
     * This determines the format of the file; if the extension is not supported,
     * an exception is thrown.
     */
    /**@{*/
    const std::string& original_input_extension() const;
    std::string& original_input_extension();
    void original_input_extension(const std::string& v);
    void original_input_extension(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the partial SML models are saved down.
     */
    /**@{*/
    bool save_intermediate_sml() const;
    void save_intermediate_sml(const bool v);
    /**@}*/

    /**
     * @brief If true, the merged SML model is saved down.
     */
    /**@{*/
    bool save_merged_sml() const;
    void save_merged_sml(const bool v);
    /**@}*/

    /**
     * @brief Extension to use for the SML files.
     */
    /**@{*/
    const std::string& sml_extension() const;
    std::string& sml_extension();
    void sml_extension(const std::string& v);
    void sml_extension(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the model module is not generated.
     */
    /**@{*/
    bool disable_model_module() const;
    void disable_model_module(const bool v);
    /**@}*/

public:
    bool operator==(const workflow_settings& rhs) const;
    bool operator!=(const workflow_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(workflow_settings& other) noexcept;
    workflow_settings& operator=(workflow_settings other);

private:
    bool save_original_input_;
    std::string original_input_extension_;
    bool save_intermediate_sml_;
    bool save_merged_sml_;
    std::string sml_extension_;
    bool disable_model_module_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::frontend::workflow_settings& lhs,
    dogen::frontend::workflow_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
