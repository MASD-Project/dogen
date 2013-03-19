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
#include "dogen/generator/outputters/stream_outputter.hpp"
#include "dogen/generator/outputters/file_outputter.hpp"
#include "dogen/generator/outputters/factory.hpp"
#include "dogen/utility/log/logger.hpp"

namespace {

dogen::utility::log::logger lg(
    dogen::utility::log::logger_factory("outputters::factory"));
}

namespace dogen {
namespace generator {
namespace outputters {

void factory::log_output_disabled(std::string name) const {
    using namespace utility::log;
    BOOST_LOG_SEV(lg, debug) << "Outputting to " << name
                             << " disabled, so ignoring it.";
}

factory::production_type factory::create() const {
    production_type r;

    if (settings_.output_to_file()) {
        outputter::ptr o(new file_outputter(settings_.force_write()));
        r.push_back(o);
    } else
        log_output_disabled(file_outputter::outputter_name());

    if (settings_.output_to_stdout()) {
        outputter::ptr o(new stream_outputter(stream_fn_()));
        r.push_back(o);
    } else
        log_output_disabled(stream_outputter::outputter_name());

    return r;
}

} } }
