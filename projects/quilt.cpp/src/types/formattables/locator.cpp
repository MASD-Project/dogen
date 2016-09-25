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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.locator"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string missing_path_annotations(
    "Could not find any path annotations for formatter: ");
const std::string empty_formatter_name("Empty formatter name was supplied.");
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

locator::locator(
    const options::cpp_options& opts, const yarn::model& m,
    const std::unordered_map<std::string, annotations::path_annotations>& ps)
    : model_name_(m.name()), path_annotations_(ps), module_ids_(module_ids(m)),
      project_path_(make_project_path(opts, m.name())) {}

std::unordered_set<std::string> locator::
module_ids(const yarn::model& m) const {
    module_id_collector c;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(c);
    }
    return c.result();
}

const annotations::path_annotations& locator::
path_annotations_for_formatter(const std::string& formatter_name) const {
    const auto i(path_annotations_.find(formatter_name));
    if (i == path_annotations_.end()) {
        BOOST_LOG_SEV(lg, error) << missing_path_annotations;
        BOOST_THROW_EXCEPTION(building_error(missing_path_annotations));
    }

    return i->second;
}

boost::filesystem::path locator::make_project_path(
    const options::cpp_options& opts,
    const yarn::name& model_name) const {

    boost::filesystem::path r;
    const auto& mmp(model_name.location().model_modules());
    r = opts.project_directory_path();
    r /= boost::algorithm::join(mmp, dot);
    return r;
}

boost::filesystem::path
locator::make_facet_path(const annotations::path_annotations& ps,
    const std::string& extension, const yarn::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Making facet path for: " << n.id();

    boost::filesystem::path r;

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    if (!ps.facet_directory().empty() && !ps.disable_facet_directories())
        r /= ps.facet_directory();

    /*
     * Add the module path of the modules internal to this model.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    /*
     * Modules other than the model module contribute their simple
     * names to the directories.
     */
    if (n != model_name_) {
        const auto i(module_ids_.find(n.id()));
        if (i != module_ids_.end())
            r /= n.simple();
    }

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << n.simple();

    if (!ps.formatter_postfix().empty())
        stream << underscore << ps.formatter_postfix();

    if (!ps.facet_postfix().empty())
        stream << underscore << ps.facet_postfix();

    stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done making the facet path. Result: " << r;
    return r;
}

boost::filesystem::path locator::make_inclusion_path(
    const annotations::path_annotations& ps,
    const std::string& extension,
    const yarn::name& n) const {

    boost::filesystem::path r;

    /*
     * Header files require both the external module path and the
     * model module path in the file name path.
     */
    for (const auto& m : n.location().external_modules())
        r /= m;

    const auto& mmp(n.location().model_modules());
    r /= boost::algorithm::join(mmp, dot);
    r /= make_facet_path(ps, extension, n);
    return r;
}

boost::filesystem::path locator::make_inclusion_path_for_cpp_header(
    const yarn::name& n, const std::string& formatter_name) const {
    const auto& ps(path_annotations_for_formatter(formatter_name));
    const auto extension(ps.header_file_extension());
    return make_inclusion_path(ps, extension, n);
}

boost::filesystem::path locator::make_full_path_for_cpp_header(
    const yarn::name& n, const std::string& formatter_name) const {

    auto r(project_path_);
    const auto& ps(path_annotations_for_formatter(formatter_name));
    r /= ps.include_directory_name();

    const auto extension(ps.header_file_extension());
    r /= make_inclusion_path_for_cpp_header(n, formatter_name);

    return r;
}

boost::filesystem::path locator::make_full_path_for_cpp_implementation(
    const yarn::name& n, const std::string& formatter_name) const {

    auto r(project_path_);
    const auto& ps(path_annotations_for_formatter(formatter_name));
    r /= ps.source_directory_name();

    const auto extension(ps.implementation_file_extension());
    const auto facet_path(make_facet_path(ps, extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_include_cmakelists(
    const yarn::name& n, const std::string& /*formatter_name*/) const {
    auto r(project_path_);
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_source_cmakelists(
    const yarn::name& n, const std::string& formatter_name) const {
    auto r(project_path_);
    const auto& ps(path_annotations_for_formatter(formatter_name));
    r /= ps.source_directory_name();
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_odb_options(
    const yarn::name& /*n*/, const std::string& formatter_name) const {
    auto r(project_path_);
    const auto& ps(path_annotations_for_formatter(formatter_name));
    r /= ps.source_directory_name();
    r /= "options.odb"; // FIXME: hack for filename
    return r;
}

} } } }
