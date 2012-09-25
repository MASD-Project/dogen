/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_CONFIG_SETTINGS_HPP
#define DOGEN_GENERATOR_CONFIG_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/config/cpp_settings.hpp"
#include "dogen/generator/config/sql_settings.hpp"
#include "dogen/generator/config/modeling_settings.hpp"
#include "dogen/generator/config/troubleshooting_settings.hpp"
#include "dogen/generator/config/output_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

class settings {
public:
    settings() = default;
    settings(const settings&) = default;
    ~settings() = default;
    settings& operator=(const settings&) = default;

public:
    settings(settings&& rhs)
    : modeling_(std::move(rhs.modeling_)),
      cpp_(rhs.cpp_),
      sql_(rhs.sql_),
      troubleshooting_(rhs.troubleshooting_),
      output_(std::move(rhs.output_)) { }

public:
    /**
     * @brief All settings related to modeling.
     */
    /**@{*/
    modeling_settings modeling() const { return modeling_; }
    settings& modeling(modeling_settings value) {
        modeling_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief All settings related to C++.
     */
    /**@{*/
    cpp_settings cpp() const { return cpp_; }
    settings& cpp(cpp_settings value) {
        cpp_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief All settings related to SQL.
     */
    /**@{*/
    sql_settings sql() const { return sql_; }
    settings& sql(sql_settings value) {
        sql_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief All settings related to troubleshooting.
     */
    /**@{*/
    troubleshooting_settings
    troubleshooting() const { return troubleshooting_; }
    settings& troubleshooting(troubleshooting_settings value) {
        troubleshooting_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief All settings related to outputting.
     */
    /**@{*/
    output_settings
    output() const { return output_; }
    settings& output(output_settings value) {
        output_ = value;
        return *this;
    }
    /**@}*/

private:
    modeling_settings modeling_;
    cpp_settings cpp_;
    sql_settings sql_;
    troubleshooting_settings troubleshooting_;
    output_settings output_;
};

std::ostream& operator<<(std::ostream& stream, settings value);

} } }

#endif
