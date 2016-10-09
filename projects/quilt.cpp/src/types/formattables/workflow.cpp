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
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations_factory.hpp"
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

class module_id_collector : public yarn::element_visitor {
public:
    const std::unordered_set<std::string>& result() { return module_ids_; }

public:
    using yarn::element_visitor::visit;
    void visit(const yarn::module& m) override {
        module_ids_.insert(m.name().id());
    }

private:
    std::unordered_set<std::string> module_ids_;
};


std::unordered_set<std::string>
workflow::obtain_module_ids(const yarn::model& m) const {
    module_id_collector c;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(c);
    }
    return c.result();
}

workflow::path_annotations_type workflow::make_path_annotations(
    const dynamic::repository& drp, const dynamic::object& root_object,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating path annotations for root object.";
    annotations::path_annotations_factory f(drp, fc.file_formatters());
    const auto r(f.make(root_object));
    BOOST_LOG_SEV(lg, debug) << "Created path annotations for root object.";
    return r;
}

model workflow::
make_model(const formatters::container& fc, const yarn::model& m) const {
    model r;
    transformer t;
    r.formattables(t.transform(fc, m));
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

    auto r(make_model(fc, m));

    const auto pa(make_path_annotations(drp, root_object, fc));
    const auto module_ids(obtain_module_ids(m));
    const auto pdp(opts.project_directory_path());
    const locator l(pdp, drp, fc, root_object, m.name(), module_ids);
    expand_model(data_directories, drp, root_object, dcf, pa, fc, l, r);

    return r;
}

} } } }
