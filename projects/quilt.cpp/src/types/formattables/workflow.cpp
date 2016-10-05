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
#include <memory>
#include <algorithm>
#include <forward_list>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/memory_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/quilt.cpp/io/annotations/streaming_annotations_io.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"
#include "dogen/quilt.cpp/types/formattables/model_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.workflow"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

workflow::path_annotations_type workflow::make_path_annotations(
    const dynamic::repository& drp, const dynamic::object& root_object,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating path annotations for root object.";
    annotations::path_annotations_factory f(drp, fc.file_formatters());
    const auto r(f.make(root_object));
    BOOST_LOG_SEV(lg, debug) << "Created path annotations for root object.";
    return r;
}

std::unordered_map<std::string, annotations::streaming_annotations>
workflow::make_streaming_annotations(const dynamic::repository& drp,
    const yarn::model& m) const {

    annotations::streaming_annotations_factory f(drp);
    std::unordered_map<std::string, annotations::streaming_annotations> r;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        const auto ss(f.make(e.extensions()));
        if (!ss)
            continue;

        r[e.name().id()] = *ss;
    }

    BOOST_LOG_SEV(lg, debug) << "Model-level streaming annotations: " << r;
    return r;
}

model workflow::make_model(const dynamic::repository& drp,
    const formatters::container& fc, const yarn::model& m) const {
    model r;
    transformer t;
    r.formattables(t.transform(fc, m));
    const auto sa(make_streaming_annotations(drp, m));
    r.streaming_annotations(sa);
    return r;
}

void workflow::expand_model(
    const std::forward_list<boost::filesystem::path>& data_directories,
    const dynamic::repository& drp, const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const path_annotations_type& pa, const formatters::container& fc,
    const locator& l, model& fm) const {
    model_expander ex;
    ex.expand(data_directories, drp, root_object, dcf, pa, fc, l, fm);
}

model workflow::execute(
    const std::forward_list<boost::filesystem::path>& data_directories,
    const options::cpp_options& opts, const dynamic::repository& drp,
    const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc, const yarn::model& m) const {

    auto r(make_model(drp, fc, m));

    const auto pa(make_path_annotations(drp, root_object, fc));
    const locator l(opts, m, pa);
    expand_model(data_directories, drp, root_object, dcf, pa, fc, l, r);

    return r;
}

} } } }
