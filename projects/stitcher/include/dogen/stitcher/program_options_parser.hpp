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
#ifndef DOGEN_STITCHER_PROGRAM_OPTIONS_PARSER_HPP
#define DOGEN_STITCHER_PROGRAM_OPTIONS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <functional>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include "dogen/options/types/stitching_options.hpp"

namespace dogen {
namespace stitcher {

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
    program_options_parser(program_options_parser&& rhs)
    : arguments_(std::move(rhs.arguments_)),
      help_function_(std::move(rhs.help_function_)),
      version_function_(std::move(rhs.version_function_)),
      current_path_(std::move(rhs.current_path_)) { }

    explicit program_options_parser(std::vector<std::string> arguments);
    program_options_parser(const int argc, const char* argv[]);

private:
    void throw_missing_target() const;

private:
    typedef boost::program_options::options_description options_description;
    options_description general_options_factory() const;
    options_description input_options_factory() const;
    options_description output_options_factory() const;
    options_description options_factory() const;

private:
    typedef boost::program_options::variables_map variables_map;
    boost::optional<variables_map> variables_map_factory() const;

    options::stitching_options transform_options(const variables_map& vm) const;

public:
    void help_function(std::function<void(std::string)> value);
    void version_function(std::function<void()> value);


public:
    boost::optional<options::stitching_options> parse();

private:
    const std::vector<std::string> arguments_;
    std::function<void(const std::string&)> help_function_;
    std::function<void()> version_function_;
    const boost::filesystem::path current_path_;
};

} }

#endif
