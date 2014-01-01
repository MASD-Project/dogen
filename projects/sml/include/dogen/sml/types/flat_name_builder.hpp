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
#ifndef DOGEN_SML_TYPES_FLAT_NAME_BUILDER_FWD_HPP
#define DOGEN_SML_TYPES_FLAT_NAME_BUILDER_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Builds string representations of names, according to the
 * grammar of a language such as C++.
 */
class flat_name_builder {
public:
    flat_name_builder() = default;
    flat_name_builder(const flat_name_builder&) = default;
    flat_name_builder(flat_name_builder&&) = default;
    ~flat_name_builder() noexcept = default;

private:
    /**
     * @brief Flattens all the SML namespace information stored in qname
     * into a list of strings with C++ namespaces.
     */
    std::list<std::string>
    to_namespace_list(const model& m, const sml::qname& qn) const;

public:
    /**
     * @brief Returns the file name for the given qualified name and facet.
     */
    std::string cpp_filename_for_qname(
        const boost::property_tree::ptree& meta_data,
        const bool is_header, const qname& qn,
        const std::string& facet_directory, const std::string& facet_postfix,
        const std::string& additional_postfix) const;

    /**
     * @brief Flat representation of the qualified name.
     */
    std::string cpp_qualified_name(const model& m, const sml::qname& qn) const;

    /**
     * @brief Returns a complete name representation of the nested
     * qualified name.
     */
    void cpp_complete_name(const model& m, const nested_qname& nqn,
        std::string& complete_name) const;
};

} }

#endif
