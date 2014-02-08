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
#ifndef DOGEN_FORMATTERS_TYPES_WORKFLOW_HPP
#define DOGEN_FORMATTERS_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/transformer_interface_fwd.hpp"
#include "dogen/formatters/types/file_formatter_interface_fwd.hpp"
#include "dogen/formatters/types/annotation_factory.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/entity_fwd.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Executes the formmatters workflow.
 *
 * This workflow is largely to generate all the entities that need
 * formatting via the transformer, and then to format them into files.
 *
 * During the transition phase we are supporting an intermediate form
 * of the workflow where the client supplies the entities.
 */
class workflow {
public:
    workflow() = default;
    workflow(const workflow&) = default;
    ~workflow() = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    typedef boost::shared_ptr<file_formatter_interface> file_formatter_type;
    typedef boost::shared_ptr<transformer_interface> transformer_type;
    typedef std::list<boost::filesystem::path> paths_type;

public:
    explicit workflow(const paths_type& data_files_directories);

public:
    /**
     * @brief Register the file formatter.
     *
     * @note This function is not MT safe.
     */
    static void register_interface(file_formatter_type ff);

    /**
     * @brief Register the transformer.
     *
     * @note This function is not MT safe.
     */
    static void register_interface(transformer_type t);

public:
    typedef std::list<boost::shared_ptr<entity> > entities_type;

public:
    /**
     * @brief Returns the repository.
     *
     * @note This method is public for testing purposes only.
     */
    static formatters::repository& repository();

public:
    /**
     * @brief Execute the workflow against the supplied entities.
     *
     * @deprecated This method is only available to enable the
     * transition into the new style-formatters.
     */
    std::list<file> execute(const entities_type& entities);

    /**
     * @brief Execute the workflow.
     */
    std::list<file> execute(const sml::model& m);

private:
    annotation_factory annotation_factory_;
};

} }

#endif
