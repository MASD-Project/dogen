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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/backend/types/workflow_error.hpp"
#include "dogen/backend/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("backend.workflow"));

std::string empty;
const std::string null_registrar("Registrar is null");
const std::string no_generatable_model_modules(
    "No generatable model modules found.");
const std::string multiple_generatable_model_modules(
    "More than one model module is generatable: ");

}
namespace dogen {
namespace backend {

std::shared_ptr<backend::registrar> workflow::registrar_;

workflow::workflow(const config::knitting_options& o,
    const dynamic::schema::repository& rp)
    : knitting_options_(o), repository_(rp) { }

backend::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<backend::registrar>();

    return *registrar_;
}

std::forward_list<formatters::file>
workflow::execute(const sml::model& m) const {
    std::forward_list<formatters::file> r;
    for(const auto b : registrar().backends()) {
        const auto n(b->name());
        BOOST_LOG_SEV(lg, debug) << "Generating files for: '" << n << "'";
        auto files(b->generate(knitting_options_, repository_, m));
        BOOST_LOG_SEV(lg, debug) << "Generated files for : '" << n
                                 << "'. Total files: "
                                 << std::distance(files.begin(), files.end());
        r.splice_after(r.before_begin(), files);
    }

    return r;
}

} }
