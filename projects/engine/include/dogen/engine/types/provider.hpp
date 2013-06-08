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
#ifndef DOGEN_DIA_TO_SML_TYPES_PROVIDER_HPP
#define DOGEN_DIA_TO_SML_TYPES_PROVIDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/filesystem/path.hpp>
#include "dogen/dia/types/diagram.hpp"
#include "dogen/config/types/settings.hpp"
#include "dogen/engine/types/persister.hpp"
#include "dogen/engine/types/provider_interface.hpp"

namespace dogen {
namespace engine {

class provider : public provider_interface {
public:
    provider() = delete;
    provider(const provider&) = delete;
    provider(provider&&) = default;
    virtual ~provider() noexcept;

public:
    explicit provider(const config::settings& settings);

private:
    /**
     * @brief Reads a Dia diagram from the filesystem.
     *
     * @param path location of the diagram to read.
     */
    dia::diagram hydrate_diagram(const boost::filesystem::path& path) const;

    /**
     * @brief Converts a Dia diagram to its SML representation.
     */
    sml::model to_sml(const dia::diagram& d,
        const std::string& model_name,
        const std::string& external_module_path,
        const bool is_target) const;

public:
    virtual sml::model provide(const boost::filesystem::path& p,
        const std::string& external_module_path,
        const bool is_target = false) override;

private:
    const config::settings settings_;
    const persister persister_;
};

} }

#endif
