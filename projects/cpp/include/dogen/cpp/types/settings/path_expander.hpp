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
#ifndef DOGEN_CPP_TYPES_SETTINGS_PATH_EXPANDER_HPP
#define DOGEN_CPP_TYPES_SETTINGS_PATH_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"
#include "dogen/cpp/types/settings/path_settings_factory_fwd.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Adds the file path fields to the dynamic object.
 */
class path_expander final : public dynamic::expansion::expander_interface {
public:
    /**
     * @brief Name property for other expanders that need to declare
     * it as a dependency.
     */
    static std::string static_name();

public:
    path_expander();
    ~path_expander() noexcept;

private:
    /**
     * @brief Builds an absolute path for the supplied qualified name.
     */
    boost::filesystem::path make_file_path(
        const path_settings& ps, const sml::qname& qn) const;

    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_include_path(
        const path_settings& ps, const sml::qname& qn) const;

public:
    std::string name() const override;

    const std::forward_list<std::string>& dependencies() const override;

    void setup(const dynamic::expansion::expansion_context& ec) override;

    void expand(const sml::qname& qn, const dynamic::schema::scope_types& st,
        dynamic::schema::object& o) const override;

private:
    std::shared_ptr<const path_settings_factory> factory_;
};

} } }

#endif
