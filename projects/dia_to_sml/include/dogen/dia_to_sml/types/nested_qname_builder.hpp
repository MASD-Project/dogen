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
#ifndef DOGEN_DIA_TO_SML_TYPES_NESTED_QUALIFIED_NAME_BUILDER_HPP
#define DOGEN_DIA_TO_SML_TYPES_NESTED_QUALIFIED_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/shared_ptr.hpp>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/dia_to_sml/types/node.hpp"

namespace dogen {
namespace dia_to_sml {

class nested_qname_builder {
public:
    nested_qname_builder() = delete;
    nested_qname_builder(
        const nested_qname_builder&) = delete;
    ~nested_qname_builder() = default;
    nested_qname_builder(nested_qname_builder&&) = delete;
    nested_qname_builder& operator=(const nested_qname_builder&) = delete;

public:
    nested_qname_builder(
        const std::unordered_set<std::string>& modules,
        const std::list<std::string>& external_module_path,
        const std::string& model_name);

private:
    void finish_current_node();
    void build_node(sml::nested_qname& qn, boost::shared_ptr<node> node);

public:
    void add_name(const std::string& n);
    void add_primitive(const std::string& n);
    void start_children();
    void next_child();
    void end_children();
    sml::nested_qname build();

private:
    const std::unordered_set<std::string> modules_;
    const std::list<std::string> external_module_path_;
    const std::string model_name_;
    std::list<std::string> names_;
    boost::shared_ptr<node> root_;
    boost::shared_ptr<node> current_;
};

} }

#endif
