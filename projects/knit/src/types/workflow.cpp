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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/annotations/types/type_repository_factory.hpp"
#include "dogen/yarn/types/code_generator.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/workflow.hpp"

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.workflow"));

const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : options_(std::move(rhs.options_)) { }

workflow::
workflow(const yarn::transforms::options& o) : options_(o) {}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Starting.";

    try {
        /*
         * Generate all files.
         */
        yarn::code_generator::generate(options_);
    } catch(const dogen::formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(workflow_error(e.what()));
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Finished.";
}

} }
