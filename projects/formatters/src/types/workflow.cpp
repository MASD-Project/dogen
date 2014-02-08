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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/formatters/types/file_formatter_interface.hpp"
#include "dogen/formatters/types/transformer_interface.hpp"
#include "dogen/formatters/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("formatters.workflow"));

}

namespace dogen {
namespace formatters {

workflow::workflow(const paths_type& data_files_directories)
    : annotation_factory_(data_files_directories) {

    if (data_files_directories.empty())
        BOOST_LOG_SEV(lg, warn) << "No data files directory provided.";
    else
        BOOST_LOG_SEV(lg, debug) << "Data directories:"
                                 << data_files_directories;

    annotation_factory_.load_reference_data();
}

void workflow::register_interface(file_formatter_type ff) {
    repository().file_formatters().push_back(ff);
}

void workflow::register_interface(transformer_type t) {
    repository().transformers().push_back(t);
}

formatters::repository& workflow::repository() {
    static formatters::repository repository_;
    return repository_;
}

std::list<file> workflow::execute(const entities_type& entities) {
    std::list<file> r;
    for (const auto& e : entities) {
        for (const auto& f : repository().file_formatters()) {
            const auto of(f->format(*e));
            if (of)
                r.push_back(*of);
        }
    }
    return r;
}

std::list<file> workflow::execute(const sml::model& m) {
    std::list<file> r;

    if (repository().transformers().empty()) {
        BOOST_LOG_SEV(lg, warn) << "There are no SML transformers registered";
        return r;
    }

    for (const auto& t : repository().transformers()) {
        const auto& entities(t->transform(m, annotation_factory_));
        for (const auto& e : entities) {
            for (const auto& f : repository().file_formatters()) {
                const auto of(f->format(*e));
                if (of)
                    r.push_back(*of);
            }
        }
    }
    return r;
}


} }
