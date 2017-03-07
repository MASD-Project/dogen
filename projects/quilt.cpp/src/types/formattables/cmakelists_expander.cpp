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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/cmakelists_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.cmakelists_expander"));

const std::string missing_odb_options("Could not find the ODB Options element");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class odb_options_finder : public fabric::element_visitor {
public:
    using fabric::element_visitor::visit;
    void visit(const fabric::odb_options& oo);

public:
    yarn::name result() const;

private:
    boost::optional<yarn::name> result_;
};

void odb_options_finder::visit(const fabric::odb_options& oo) {
    result_ = oo.name();
}

yarn::name odb_options_finder::result() const {
    if (!result_) {
        BOOST_LOG_SEV(lg, error) << missing_odb_options;
        BOOST_THROW_EXCEPTION(expansion_error(missing_odb_options));
    }
    return *result_;
}

class cmakelists_updater : public fabric::element_visitor {
public:
    cmakelists_updater(const locator& l, const yarn::name& odb_options_name);

public:
    using fabric::element_visitor::visit;
    void visit(fabric::cmakelists& c);

private:
    const locator locator_;
    const yarn::name odb_options_name_;
};

cmakelists_updater::
cmakelists_updater(const locator& l, const yarn::name& odb_options_name)
    : locator_(l), odb_options_name_(odb_options_name) {}

void cmakelists_updater::visit(fabric::cmakelists& c) {
    c.include_directory_name(locator_.include_directory_name());

    const auto odb_fctn(dogen::quilt::cpp::formatters::odb::traits::facet());
    c.odb_include_directory_path(
        locator_.make_relative_include_path_for_facet(odb_fctn));
    c.odb_source_directory_path(
        locator_.make_relative_implementation_path_for_facet(odb_fctn));

    const auto oo_arch(
        dogen::quilt::cpp::formatters::odb::traits::odb_options_archetype());
    c.odb_options_file_path(
        locator_.make_relative_path_for_odb_options(
            odb_options_name_, oo_arch));

    c.odb_postfix(locator_.postfix_for_facet(odb_fctn));

    const auto types_fctn(
        dogen::quilt::cpp::formatters::types::traits::facet());
    c.types_include_directory_path(
        locator_.make_relative_include_path_for_facet(types_fctn));

    c.header_file_extension(locator_.header_file_extension());
    c.implementation_file_extension(locator_.implementation_file_extension());
}

void cmakelists_expander::expand(const locator& l, model& fm) const {
    odb_options_finder f;
    for (auto& pair : fm.formattables()) {
        auto& formattable(pair.second);

        /*
         * We only want to process the master segment; the extensions
         * can be ignored.
         */
        auto& segment(formattable.master_segment());
        if (segment->origin_type() != yarn::origin_types::target) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        const auto& e(*segment);
        e.accept(f);
    }

    cmakelists_updater cu(l, f.result());
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& segment(formattable.master_segment());
        if (segment->origin_type() != yarn::origin_types::target) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        auto& e(*segment);
        e.accept(cu);
    }
}

} } } }
