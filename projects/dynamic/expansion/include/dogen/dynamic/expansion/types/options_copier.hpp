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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_OPTIONS_COPIER_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_OPTIONS_COPIER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/config/types/cpp_options.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

class options_copier final : public expander_interface {
public:
    /**
     * @brief Name property for other expanders that need to declare
     * it as a dependency.
     */
    static std::string static_name();

public:
    options_copier();
    ~options_copier() noexcept;

private:
    /**
     * @brief Creates a field in the dynamic object with the supplied
     * name and value.
     */
    /**@{*/
    void make_field(const std::string& n, const bool v,
        schema::object& o) const;
    void make_field(const std::string& n, const std::string& v,
        schema::object& o) const;
    /**@}*/

public:
    std::string name() const override;

    const std::forward_list<std::string>& dependencies() const override;

    void setup(const expansion_context& ec) override;

    void expand(const sml::qname& qn, const schema::scope_types& st,
        schema::object& o) const override;

private:
    const schema::field_instance_factory factory_;

    config::cpp_options options_;
};

} } }

#endif
