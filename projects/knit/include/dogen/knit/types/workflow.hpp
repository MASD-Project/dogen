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
#ifndef DOGEN_KNIT_TYPES_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <functional>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/ownership_hierarchy_repository.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/descriptor.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/formatters/types/file_writer_interface.hpp"

namespace dogen {
namespace knit {

/**
 * @brief Main workflow of the Knit library. Responsible for
 * transforming a high-level representation of a domain into code, in
 * one or more programming languages.
 *
 * The model which one intends to transform is known as the @e target
 * model. The workflow starts by invoking the correct front-end to
 * read in the target model and all of its dependencies. There are two
 * types of dependencies:
 *
 * @li @e explicit: specified by the options passed in; these are
 * models created by the user and any models that they, in turn,
 * depend on.
 *
 * @li @e implicit: these are known as the @e system models. They are
 * added automatically. Examples are primitives, boost, std, etc.
 *
 * Collectively, all implicit and explicit models are referred to as
 * the @e input models. The input models read the front-end are
 * converted into the middle end representation - Yarn. They are then
 * merged it into a single, unified Yarn model, called the @e merged
 * model; all dependencies are resolved and validated.
 *
 * The workflow then instantiates all backends requested by the
 * options passed in. They use the merged model to generate source
 * code, and then outputted it to the desired destination.
 */
class workflow {
public:
    workflow() = delete;
    workflow& operator=(const workflow&) = default;
    workflow(const workflow&) = default;

public:
    typedef std::function<std::ostream& ()> output_fn;

public:
    workflow(workflow&& rhs);
    explicit workflow(const options::knitting_options& s);

public: // public section for testing purposes only
    /**
     * @brief Returns true if the housekeeping of generated files is
     * required, false otherwise.
     */
    bool housekeeping_required() const;

private:
    std::vector<boost::filesystem::path> obtain_data_dirs() const;

    /**
     * @brief Obtains the complete ownership hierarchy across all
     * backends.
     */
    annotations::ownership_hierarchy_repository
    obtain_ownership_hierarchy_repository() const;

    /**
     * @brief Sets up the annotations repository.
     */
    annotations::type_repository setup_annotations_repository(
        const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::ownership_hierarchy_repository& ohrp) const;

    /**
     * @brief Obtain the yarn model.
     */
    yarn::model
    obtain_yarn_model(const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::ownership_hierarchy_repository& ohrp,
        const annotations::type_repository& atrp) const;

    /**
     * @brief Performs a housekeeping run for the supplied directories.
     */
    void perform_housekeeping(
        const std::forward_list<formatters::file>& files,
        const std::forward_list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Obtains the file writer, according to configuration.
     */
    std::shared_ptr<dogen::formatters::file_writer_interface>
    obtain_file_writer() const;

    /**
     * @brief Outputs the pair file name and contents to its output
     * destination.
     */
    void write_files(
        std::shared_ptr<dogen::formatters::file_writer_interface> writer,
        const std::forward_list<formatters::file>& files) const;

public:
    /**
     * @brief Perform the entire code generation workflow.
     */
    void execute() const;

private:
    const options::knitting_options knitting_options_;
};

} }

#endif
