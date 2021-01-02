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
#ifndef DOGEN_ORCHESTRATION_TESTS_MODEL_GENERATOR_HPP
#define DOGEN_ORCHESTRATION_TESTS_MODEL_GENERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/artefact.hpp"

namespace dogen::orchestration::tests {

/**
 * @brief Generates a model and performs a canned set of associated
 * checks.
 */
class model_generator {
private:
    /**
     * @brief Prints a limited number of lines from content. Used to
     * ensure we don't spam the build logs.
     */
    static void print_lines(const std::string& content,
        const unsigned int total, std::ostream& os);

    static std::list<boost::shared_ptr<physical::entities::artefact>>
    gather_artefacts(const dogen::physical::entities::model& m);

public:
    static dogen::physical::entities::model
    apply_physical_model_production(const boost::filesystem::path& target,
        const std::vector<boost::filesystem::path>& reference_directories,
        const boost::filesystem::path& output_dir,
        const bool enable_tracing_locally = false,
        const bool enable_reporting_locally = false,
        const bool enable_diffing_locally = false);

    static dogen::physical::entities::model
    apply_physical_model_production(const boost::filesystem::path& target,
        const boost::filesystem::path& output_dir,
        const bool enable_tracing_locally = false,
        const bool enable_reporting_locally = false,
        const bool enable_diffing_locally = false);

    static std::string apply_artefact_to_artefact_chain(
        const boost::filesystem::path& src,
        const bool enable_tracing_locally = false,
        const bool enable_reporting_locally = false,
        const bool enable_diffing_locally = false);

public:

    /**
     * @brief Checks to see if the model contains any artefacts which are
     * different from the files in the filesystem.
     *
     * @note We're using std::cout here by design as we always want the
     * output to show up in CDash.
     */
    static bool check_for_differences(const boost::filesystem::path& output_dir,
        const dogen::physical::entities::model& m);

    /**
     * @brief Performs a set of checks for the delete extra scenario.
     */
    static bool check_for_delete_extra(
        const boost::filesystem::path& output_dir,
        const dogen::physical::entities::model& m);

    /**
     * @brief Performs a set of checks for the ignore extra scenario.
     */
    static bool check_for_ignore_extra(
        const boost::filesystem::path& output_dir,
        const dogen::physical::entities::model& m);

    /**
     * @brief Performs a set of checks for the force write scenario.
     */
    static bool check_for_force_write(const boost::filesystem::path& output_dir,
        const dogen::physical::entities::model& m);

    /**
     * @brief Performs a set of checks for the model out of sync scenario.
     */
    static bool check_out_of_sync(const boost::filesystem::path& output_dir,
        const dogen::physical::entities::model& m);
};

}

#endif
