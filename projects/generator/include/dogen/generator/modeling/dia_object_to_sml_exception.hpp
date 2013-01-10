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
#ifndef DOGEN_GENERATOR_MODELING_DIA_OBJECT_TO_SML_EXCEPTION_HPP
#define DOGEN_GENERATOR_MODELING_DIA_OBJECT_TO_SML_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include "dogen/dia/types/object.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/exception.hpp"
#include "dogen/sml/types/package.hpp"

namespace dogen {
namespace generator {
namespace modeling {

class dia_object_to_sml_exception {
public:
    dia_object_to_sml_exception() = delete;
    dia_object_to_sml_exception(const dia_object_to_sml_exception&) = default;
    ~dia_object_to_sml_exception() = default;
    dia_object_to_sml_exception(dia_object_to_sml_exception&&) = default;
    dia_object_to_sml_exception& operator=(const dia_object_to_sml_exception&) = default;

public:
    dia_object_to_sml_exception(const std::string& model_name,
        const std::list<std::string>& external_package_path,
        bool is_target, bool verbose);

private:
    sml::qname transform_qualified_name(const dia::attribute& a,
        sml::meta_types meta_type, const std::string& pkg_id) const;

    std::string transform_string_attribute(const dia::attribute& a) const;
    sml::exception transform_exception(const dia::object& o) const;

public:
    bool is_processable(const dia::object& o) const;
    void add_object(const dia::object& o);

    std::unordered_map<sml::qname, sml::exception>
    transform(std::unordered_map<std::string, sml::package> packages);

private:
    const std::string model_name_;
    const std::list<std::string> external_package_path_;
    const bool is_target_;
    const bool verbose_;
    std::list<dia::object> objects_;
    std::unordered_map<std::string, sml::package> packages_;
};

} } }

#endif
