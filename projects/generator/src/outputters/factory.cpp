/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
        outputter::ptr o(new file_outputter(
                settings_.verbose(),
                settings_.delete_extra_files()));
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
