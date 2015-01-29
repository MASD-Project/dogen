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
#ifndef DOGEN_DIA_TO_SML_TYPES_IDENTIFIER_PARSER_HPP
#define DOGEN_DIA_TO_SML_TYPES_IDENTIFIER_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen/sml/types/nested_qname.hpp"

namespace dogen {
namespace dia_to_sml {

class identifier_parser {
public:
    identifier_parser() = default;
    identifier_parser(const identifier_parser&) = default;
    ~identifier_parser() = default;
    identifier_parser(identifier_parser&&) = default;
    identifier_parser& operator=(const identifier_parser&) = default;

public:
    /**
     * @brief Initialises the parser.
     *
     * @param modules names of all the top-level modules in the
     * current model.
     * @param external_module_path modules external to the current
     * model
     * @param model_name name of the current model
     */
    identifier_parser(const std::unordered_set<std::string>& modules,
        const std::list<std::string>& external_module_path,
        const std::string model_name);

public:
    sml::nested_qname parse_qname(const std::string& n) const;
    static std::list<std::string> parse_scoped_name(const std::string& n);
    static std::list<std::string> parse_csv_string(const std::string& n);

private:
    const std::unordered_set<std::string> modules_;
    const std::list<std::string> external_module_path_;
    const std::string model_name_;
};

} }

#endif
