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
#ifndef DOGEN_KNIT_TYPES_MIDDLE_END_TO_BACKEND_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_MIDDLE_END_TO_BACKEND_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <ostream>
#include <functional>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/file_writer_interface.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace knit {

/**
 * @brief Executes the middle-end to backend workflow.
 */
class middle_end_to_backend_workflow {
public:
    typedef std::function<std::ostream& ()> output_fn;

public:
    middle_end_to_backend_workflow(const config::knitting_options& o,
        const dynamic::schema::repository& rp,
        const output_fn& of);

public: // public section for testing purposes only
    /**
     * @brief Returns true if the housekeeping of generated files is
     * required, false otherwise.
     */
    bool housekeeping_required() const;

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
    void execute(const sml::model& m) const;

private:
    const config::knitting_options& knitting_options_;
    const dynamic::schema::repository& repository_;
    const output_fn output_;
};

} }

#endif
