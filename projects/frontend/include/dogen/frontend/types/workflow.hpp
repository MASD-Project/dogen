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
#ifndef DOGEN_FRONTEND_TYPES_WORKFLOW_HPP
#define DOGEN_FRONTEND_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/tack/types/model.hpp"
#include "dogen/config/types/archive_types.hpp"
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/frontend/types/frontend_registrar.hpp"
#include "dogen/frontend/types/frontend_interface.hpp"
#include "dogen/frontend/types/input_descriptor.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Manages the entire frontend workflow.
 */
class workflow {
public:
    workflow(const config::knitting_options& o, const dynamic::repository& rp);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static frontend::frontend_registrar& registrar();

private:
    /**
     * @brief Given an archive type and a model name, returns the
     * appropriate file extension.
     *
     * @param archive_type one of the supported boost archive types.
     */
    std::string extension(const config::archive_types at) const;

    /**
     * @brief Generates the frontend settings given the current
     * troubleshooting options and the path supplied.
     */
    frontend_settings
    create_frontend_settings(const boost::filesystem::path& p) const;

    /**
     * @brief Given the original file path, generates a new file path
     * for the archive in question.
     */
    boost::filesystem::path
    create_debug_file_path(const config::archive_types at,
        const boost::filesystem::path& original_path) const;

private:
    /**
     * @brief Given an input descriptor, creates the associated Tack
     * model.
     */
    tack::model create_model_activity(const input_descriptor& d) const;

    /**
     * @brief Checks the options chosen by the user to determine if
     * the Tack model should be persisted; if so, persists it.
     */
    void persist_model_activity(const boost::filesystem::path& p,
        const tack::model& m) const;

public:
    /**
     * @brief Process all of the inputs into models, using the
     * appropriate Tack frontends.
     */
    std::list<tack::model>
    execute(const std::list<input_descriptor>& descriptors);

private:
    static std::shared_ptr<frontend::frontend_registrar> registrar_;
    const config::knitting_options knitting_options_;
    const dynamic::repository& repository_;
    const dynamic::workflow dynamic_workflow_;
};

} }

#endif
