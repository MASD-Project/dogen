/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_KNITTER_PROGRAM_OPTIONS_PARSER_HPP
#define DOGEN_KNITTER_PROGRAM_OPTIONS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <functional>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include "dogen/options/types/knitting_options.hpp"

namespace dogen {
namespace knitter {

/**
 * @brief Creates a optionsuration from a set of command line arguments
 * supplied by the user.
 */
class program_options_parser {
public:
    program_options_parser() = delete;
    program_options_parser& operator=(const program_options_parser&) = delete;
    program_options_parser(const program_options_parser&) = delete;

public:
    explicit program_options_parser(std::vector<std::string> arguments);
    program_options_parser(const int argc, const char* argv[]);
    program_options_parser(program_options_parser&& rhs);

private:
    typedef boost::program_options::options_description options_description;

    options_description general_options_factory() const;
    options_description modeling_options_factory() const;
    options_description output_options_factory() const;
    options_description cpp_options_factory() const;
    options_description options_factory() const;

private:
    typedef boost::program_options::variables_map variables_map;
    boost::optional<variables_map> variables_map_factory() const;

private:
    options::input_options
    transform_input_options(const variables_map& vm) const;
    options::cpp_options transform_cpp_options(const variables_map& vm) const;
    options::output_options
    transform_output_options(const variables_map& vm) const;

public:
    void help_function(std::function<void(std::string)> value);
    void version_function(std::function<void()> value);

public:
    boost::optional<options::knitting_options> parse();

private:
    const std::vector<std::string> arguments_;
    std::function<void(const std::string&)> help_function_;
    std::function<void()> version_function_;
};

} }

#endif
