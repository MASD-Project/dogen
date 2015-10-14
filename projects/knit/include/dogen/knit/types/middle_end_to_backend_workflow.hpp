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
#ifndef DOGEN_KNIT_TYPES_MIDDLE_END_TO_BACKEND_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_MIDDLE_END_TO_BACKEND_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <ostream>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/file_writer_interface.hpp"
#include "dogen/tack/types/model.hpp"

namespace dogen {
namespace knit {

/**
 * @brief Executes the middle-end to backend workflow.
 */
class middle_end_to_backend_workflow {
public:
    middle_end_to_backend_workflow(const config::knitting_options& o,
        const dynamic::repository& rp,
        const bool perform_housekeeping);

private:
    /**
     * @brief Performs a housekeeping run for the supplied directories.
     */
    void perform_housekeeping_activity(
        const std::forward_list<formatters::file>& files,
        const std::forward_list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Obtains the file writers, according to configuration.
     */
    const std::forward_list<
        std::shared_ptr<dogen::formatters::file_writer_interface>
        >
    obtain_file_writers_activity() const;

    /**
     * @brief Outputs the pair file name and contents to its output
     * destination.
     */
    void write_files_activity(
        const std::forward_list<
            std::shared_ptr<dogen::formatters::file_writer_interface>
            >& writers,
        const std::forward_list<formatters::file>& files) const;

public:
    /**
     * @brief Executes the workflow.
     */
    void execute(const tack::model& m) const;

private:
    const config::knitting_options& knitting_options_;
    const dynamic::repository& repository_;
    const bool perform_housekeeping_;
};

} }

#endif
