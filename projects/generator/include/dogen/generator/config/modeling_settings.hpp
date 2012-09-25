/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_CONFIG_MODELING_SETTINGS_HPP
#define DOGEN_GENERATOR_CONFIG_MODELING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace config {

class modeling_settings {
public:
    modeling_settings(const modeling_settings&) = default;
    ~modeling_settings() = default;
    modeling_settings& operator=(const modeling_settings&) = default;

public:
    modeling_settings() : verbose_(false), disable_model_package_(false) { }

    modeling_settings(modeling_settings&& rhs)
    : verbose_(std::move(rhs.verbose_)),
      target_(std::move(rhs.target_)),
      external_package_path_(std::move(rhs.external_package_path_)),
      references_(std::move(rhs.references_)),
      disable_model_package_(std::move(rhs.disable_model_package_)) { }

public:
    /**
     * @brief Path to the Dia diagram that contains the model to
     * generate.
     */
    /**@{*/
    boost::filesystem::path target() const { return target_; }
    modeling_settings& target(boost::filesystem::path value) {
        target_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief external packages which contain the model to generate,
     * delimited by "::".
     */
    /**@{*/
    std::string external_package_path() const { return external_package_path_; }
    modeling_settings& external_package_path(std::string value) {
        external_package_path_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief All external models in which this model depends.
     */
    /**@{*/
    std::vector<boost::filesystem::path> references() const {
        return references_;
    }
    modeling_settings& references(std::vector<boost::filesystem::path> value) {
        references_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Print additional diagnostic information to standard output.
     */
    /**@{*/
    bool verbose() const { return verbose_; }
    modeling_settings& verbose(bool value) {
        verbose_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Do not generate a top-level package with the model
     * name.
     */
    /**@{*/
    bool disable_model_package() const { return disable_model_package_; }
    modeling_settings& disable_model_package(bool value) {
        disable_model_package_ = value;
        return *this;
    }
    /**@*/

private:
    bool verbose_;
    boost::filesystem::path target_;
    std::string external_package_path_;
    std::vector<boost::filesystem::path> references_;
    bool disable_model_package_;
};

std::ostream& operator<<(std::ostream& stream, modeling_settings value);

} } }

#endif
