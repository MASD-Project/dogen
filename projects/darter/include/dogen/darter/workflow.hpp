/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2014 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_DARTER_WORKFLOW_HPP
#define DOGEN_DARTER_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/darting_options.hpp"

namespace dogen {
namespace darter {

/**
 * @brief Encapsulates the entire darter tool workflow.
 */
class workflow {
public:
    workflow();

private:
    /**
     * @brief Sets up the model name from the options.
     */
    void initialise_model_name(const dogen::options::darting_options& o);

private:
    /**
     * @brief Given the main arguments, generates the darting options.
     */
    boost::optional<dogen::options::darting_options>
    generate_darting_options(const int argc, const char* argv[]) const;

    /**
     * @brief Performs the initialisation of logging system.
     */
    void initialise_logging(const dogen::options::darting_options& o);

    /**
     * @brief Executes the workflow for the given the application
     * options.
     */
    void dart(const dogen::options::darting_options& o) const;

private:
     /**
      * @brief Exception reporting code that is common amongst methods.
      */
     void report_exception_common() const;

    /**
     * @brief Reports the exception to the appropriate outputs.
     */
    void report_exception(const std::exception& e) const;

    /**
     * @brief Reports an unknown exception to the appropriate outputs.
     */
    void report_exception() const;

public:
    /**
     * @brief Executes the entire darter workflow.
     *
     * @return false if the workflow failed for whatever reason, true
     * otherwise.
     */
    int execute(const int argc, const char* argv[]);

private:
    bool can_log_;
    std::string model_name_;
    boost::filesystem::path log_path_;
};

} }

#endif
