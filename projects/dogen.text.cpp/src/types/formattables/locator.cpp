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
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.text.cpp/types/formattables/location_error.hpp"
#include "dogen.text.cpp/types/transforms/model_to_text_transform.hpp"
#include "dogen.text.cpp/types/formattables/locator.hpp"

using dogen::identification::entities::physical_meta_id;

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.formattables.locator"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");
const physical_meta_id backend_id("masd.cpp");

const std::string missing_facet_configuration(
    "Could not find configuration for facet: ");
const std::string missing_archetype_configuration(
    "Could not find configuration for archetype: ");
const std::string missing_backend("Could not locate backend: ");
const std::string missing_archetype("Could not locate archetype: ");
const std::string missing_backend_directory(
    "Enable backend directory is on but backend directory is empty.");

}

namespace dogen::text::cpp::formattables {

using identification::entities::logical_name;

locator::locator(const physical::entities::model& pm)
    : physical_model_(pm),
      model_name_(pm.provenance().logical_name()),
      project_path_(make_project_path(
              pm.meta_model_properties().output_directory_path(), pm)),
      headers_project_path_(make_headers_path(project_path_, pm)),
      output_directory_path_(
          pm.meta_model_properties().output_directory_path()),
      templates_project_path_(make_templates_path(pm)),
      split_mode_(!pm.meta_model_properties().project_path_properties()
          .headers_output_directory().empty()) {
    BOOST_LOG_SEV(lg, trace) << "Output path: " << output_directory_path_;
}

boost::filesystem::path
locator::make_headers_path(const boost::filesystem::path& project_path,
    const physical::entities::model& pm) {
    /*
     * If the user did not supply a path for C++ headers, we simply
     * place them inside the project.
     */
    const auto& mmp(pm.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto hod(ppp.headers_output_directory());
    boost::filesystem::path r;
    if (hod.empty()) {
        r = project_path;
    } else {
        /*
         * If a path was supplied, it is relative to the output
         * directory. We need to compute the canonical path resulting
         * from that.
         */
        using boost::filesystem::canonical;
        r = canonical(hod, mmp.output_directory_path());
    }

    BOOST_LOG_SEV(lg, trace) << "Headers path: " << r;
    return r;
}

boost::filesystem::path locator::
make_templates_path(const physical::entities::model& pm) {
    const auto& mmp(pm.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto r(mmp.file_path() / ppp.templates_directory_name());
    BOOST_LOG_SEV(lg, trace) << "Templates path: " << r.generic_string();
    return r;
}


const physical::entities::facet_properties& locator::
facet_properties_for_facet(const std::string& facet) const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& fp(mmp.facet_properties());
    physical_meta_id id(facet);
    const auto i(fp.find(id));
    if (i == fp.end()) {
        BOOST_LOG_SEV(lg, error) << missing_facet_configuration;
        BOOST_THROW_EXCEPTION(location_error(missing_facet_configuration));
    }
    return i->second;
}

const physical::entities::archetype_properties& locator::
archetype_properties_for_archetype(const std::string& archetype) const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ap(mmp.archetype_properties());

    physical_meta_id id(archetype);
    const auto i(ap.find(id));
    if (i == ap.end()) {
        BOOST_LOG_SEV(lg, error) << missing_archetype_configuration
                                 << archetype;
        BOOST_THROW_EXCEPTION(
            location_error(missing_archetype_configuration + archetype));
    }
    return i->second;
}

std::string locator::header_file_extension() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    return ppp.header_file_extension();
}

std::string locator::implementation_file_extension() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    return ppp.implementation_file_extension();
}

std::string locator::postfix_for_facet(const std::string& facet) const {
    const auto fp(facet_properties_for_facet(facet));
    return fp.computed_postfix();
}

boost::filesystem::path
locator::make_project_path(const boost::filesystem::path output_directory_path,
    const physical::entities::model& pm) {
    boost::filesystem::path r(output_directory_path);
    const auto& mm(pm.provenance().logical_name().location().model_modules());
    r /= boost::algorithm::join(mm, dot);

    const auto& ppp(pm.meta_model_properties().project_path_properties());
    const auto ebd(ppp.enable_backend_directories());
    if (ebd) {
        const auto& bp(pm.meta_model_properties().backend_properties());
        const auto i(bp.find(backend_id));
        if (i == bp.end()) {
            BOOST_LOG_SEV(lg, error) << missing_backend << backend_id;
            BOOST_THROW_EXCEPTION(
                location_error(missing_backend + backend_id.value()));
        }

        const auto dn(i->second.computed_directory_name());
        if (dn.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_backend_directory;
            BOOST_THROW_EXCEPTION(location_error(missing_backend_directory));
        }
        r /= dn;
    }

    BOOST_LOG_SEV(lg, trace) << "Project path: " << r;
    return r;
}

boost::filesystem::path locator::make_facet_path(const std::string& archetype,
    const std::string& extension, const logical_name& n) const {
    BOOST_LOG_SEV(lg, trace) << "Making facet path for: "
                             << n.qualified().dot();

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());

    boost::filesystem::path r;
    const auto& ap(archetype_properties_for_archetype(archetype));
    if (!ap.facet_properties().computed_directory_name().empty() &&
        !ppp.disable_facet_directories())
        r /= ap.facet_properties().computed_directory_name();

    /*
     * Add the module path of all the modules that contain this name.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    /*
     * Modules other than the model module contribute their simple
     * names to the directories.
     */
    if (n != model_name_ && n.is_container())
            r /= n.simple();

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << n.simple();

    if (!ap.computed_postfix().empty())
        stream << underscore << ap.computed_postfix();

    if (!ap.facet_properties().computed_postfix().empty())
        stream << underscore << ap.facet_properties().computed_postfix();

    if (!extension.empty())
        stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, trace) << "Done making the facet path. Result: " << r;
    return r;
}

boost::filesystem::path
locator::make_facet_path_temp(const std::string& archetype,
    const std::string& file_name, const logical_name& n) const {
    BOOST_LOG_SEV(lg, trace) << "Making facet path for: "
                             << n.qualified().dot();

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    boost::filesystem::path r;
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());

    const auto& ap(archetype_properties_for_archetype(archetype));
    if (!ap.facet_properties().computed_directory_name().empty() &&
        !ppp.disable_facet_directories())
        r /= ap.facet_properties().computed_directory_name();

    /*
     * Add the module path of all the modules that contain this name.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    /*
     * Modules other than the model module contribute their simple
     * names to the directories.
     */
    if (n != model_name_ && n.is_container())
        r /= n.simple();

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << file_name;
    r /= stream.str();

    BOOST_LOG_SEV(lg, trace) << "Done making the facet path. Result: " << r;
    return r;
}

boost::filesystem::path
locator::make_inclusion_path_prefix(const logical_name& n) const {
    /*
     * Header files require both the external module path and the
     * model module path in the file name path.
     */
    boost::filesystem::path r;
    for (const auto& m : n.location().external_modules())
        r /= m;

    const auto& mm(n.location().model_modules());
    r /= boost::algorithm::join(mm, dot);

    BOOST_LOG_SEV(lg, trace) << "Inclusion path prefix: " << r;
    return r;
}

boost::filesystem::path
locator::make_inclusion_path(const std::string& archetype,
    const std::string& extension, const logical_name& n) const {
    boost::filesystem::path r(make_inclusion_path_prefix(n));
    r /= make_facet_path(archetype, extension, n);

    BOOST_LOG_SEV(lg, trace) << "Inclusion path: " << r;
    return r;
}

boost::filesystem::path locator::project_path() const {
    return project_path_;
}

boost::filesystem::path locator::headers_project_path() const {
    return headers_project_path_;
}

boost::filesystem::path locator::templates_project_path() const {
    return templates_project_path_;
}

boost::filesystem::path locator::headers_model_path() const {
    auto r(headers_project_path_);
    r /= make_inclusion_path_prefix(model_name_);
    return r;
}

std::string locator::include_directory_name() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    return ppp.include_directory_name();
}

std::string locator::source_directory_name() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    return ppp.source_directory_name();
}

std::string locator::tests_directory_name() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    return ppp.tests_directory_name();
}

std::string locator::templates_directory_name() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    return ppp.templates_directory_name();
}

boost::filesystem::path locator::
make_relative_include_path(bool for_include_statement) const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());

    /*
     * If the path is being made for an include statement, we must not
     * include the top-level include directory.
     */
    boost::filesystem::path r;
    if (!for_include_statement)
        r /= ppp.include_directory_name();

    r /= make_inclusion_path_prefix(model_name_);

    BOOST_LOG_SEV(lg, trace) << "Relative include path: " << r;
    return r;
}

boost::filesystem::path
locator::make_relative_include_path_for_facet(const std::string& facet,
    bool for_include_statement) const {
    auto r(make_relative_include_path(for_include_statement));
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto& fp(facet_properties_for_facet(facet));
    if (!fp.computed_directory_name().empty() &&
        !ppp.disable_facet_directories())
        r /= fp.computed_directory_name();

    BOOST_LOG_SEV(lg, trace) << "Relative include path for facet: " << r;
    return r;
}

boost::filesystem::path
locator::make_inclusion_path_for_cpp_header(const logical_name& n,
    const std::string& archetype) const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto extension(ppp.header_file_extension());

    const auto r(make_inclusion_path(archetype, extension, n));
    BOOST_LOG_SEV(lg, trace) << "Include path for C++ header: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_to_include_directory() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    auto r(headers_project_path_);

    /*
     * If we are in split mode, we do not want to add a top-level
     * include directory; the user is expected to have already set up
     * its own directory structure.
     */
    if (!split_mode_)
        r /= ppp.include_directory_name();

    BOOST_LOG_SEV(lg, trace) << "Full path to include dir: " << r;
    return r;
}

boost::filesystem::path
locator::make_full_path_to_implementation_directory() const {
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    auto r(project_path_);
    r /= ppp.source_directory_name();

    BOOST_LOG_SEV(lg, trace) << "Full path to implementation dir: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_to_include_facet_directory(
    const std::string& facet) const {

    auto r(make_full_path_to_include_directory());
    const auto for_include_statement(true);
    r /= make_relative_include_path_for_facet(facet, for_include_statement);

    BOOST_LOG_SEV(lg, trace) << "Full path to include facet dir: " << r;
    return r;
}

boost::filesystem::path
locator::make_full_path_for_cpp_header(const logical_name& n,
    const std::string& archetype) const {
    auto r(make_full_path_to_include_directory());
    r /= make_inclusion_path_for_cpp_header(n, archetype);

    BOOST_LOG_SEV(lg, trace) << "Full path to C++ header: " << r;
    return r;
}

boost::filesystem::path locator::make_relative_implementation_path_for_facet(
    const std::string& facet) const {

    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    boost::filesystem::path r(ppp.source_directory_name());

    const auto fp(facet_properties_for_facet(facet));
    if (!fp.computed_directory_name().empty() &&
        !ppp.disable_facet_directories())
        r /= fp.computed_directory_name();

    BOOST_LOG_SEV(lg, trace) << "Relative implementation path: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_for_templates(
    const logical_name& n, const std::string& archetype) const {
    auto r(project_path_);

    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());

    const auto extension(ppp.templates_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    BOOST_LOG_SEV(lg, trace) << "Full path templates: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_for_tests_cpp_implementation(
    const logical_name& n, const std::string& archetype) const {
    auto r(project_path_);

    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());

    const auto extension(ppp.implementation_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    BOOST_LOG_SEV(lg, trace) << "Full path tests c++ implementation: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_for_tests_cpp_main(
    const logical_name& n, const std::string& archetype) const {

    auto r(project_path_);
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto extension(ppp.implementation_file_extension());
    const auto facet_path(make_facet_path_temp(archetype,
            "main." + extension, n));
    r /= facet_path;

    BOOST_LOG_SEV(lg, trace) << "Full path tests c++ tests main: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_for_cpp_implementation(
    const logical_name& n, const std::string& archetype) const {

    auto r(make_full_path_to_implementation_directory());

    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto extension(ppp.implementation_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    BOOST_LOG_SEV(lg, trace) << "Full path tests c++ implementation: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path_for_include_cmakelists(
    const logical_name& n, const std::string& /*archetype*/) const {
    /*
     * Note that we are placing the "include" CMake file with the
     * project directory rather than the project headers directory.
     */
    auto r(project_path_);
    r /= n.simple() + ".txt";
    return r;
}

boost::filesystem::path locator::make_full_path_for_source_cmakelists(
    const logical_name& n, const std::string& /*archetype*/) const {
    auto r(make_full_path_to_implementation_directory());
    r /= n.simple() + ".txt";
    return r;
}

boost::filesystem::path locator::make_full_path_for_tests_cmakelists(
    const logical_name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path_temp(archetype,
            n.simple() + ".txt", n));
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::
make_full_path_for_msbuild_targets(const logical_name& n,
    const std::string& /*archetype*/) const {
    auto r(make_full_path_to_implementation_directory());
    r /= n.simple() + ".targets";
    return r;
}

boost::filesystem::path locator::make_relative_path_for_odb_options(
    const logical_name& n, const std::string& archetype,
    const bool include_source_directory) const {

    boost::filesystem::path r;
    const auto& mmp(physical_model_.meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    if (include_source_directory)
        r /= ppp.source_directory_name();

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& ap(archetype_properties_for_archetype(archetype));
    if (!ap.facet_properties().computed_directory_name().empty()
        && !ppp.disable_facet_directories())
        r /= ap.facet_properties().computed_directory_name();

    /*
     * Add the module path of all the modules that contain this name.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    std::ostringstream stream;
    stream << n.simple();

    if (!ap.computed_postfix().empty())
        stream << underscore << ap.computed_postfix();

    if (!ap.facet_properties().computed_postfix().empty())
        stream << underscore << "options";

    const auto extension("odb");
    stream << dot << extension;
    r /= stream.str();

    return r;
}

boost::filesystem::path locator::make_full_path_for_odb_options(
    const logical_name& n, const std::string& archetype) const {
    auto r(project_path_);
    r /= make_relative_path_for_odb_options(n, archetype);
    return r;
}

boost::filesystem::path locator::make_full_path_for_project(
    const logical_name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, empty, n));
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::make_full_path_for_solution(
    const logical_name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, empty, n));
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::make_full_path_for_visual_studio_project(
    const logical_name& n, const std::string& archetype) const {
    auto temp(n);
    using boost::algorithm::join;
    temp.simple(join(n.location().model_modules(), ".") + ".vcxproj");
    return make_full_path_for_project(temp, archetype);
}

boost::filesystem::path locator::make_full_path_for_visual_studio_solution(
    const logical_name& n, const std::string& archetype) const {
    auto temp(n);
    using boost::algorithm::join;
    temp.simple(join(n.location().model_modules(), ".") + ".sln");
    return make_full_path_for_project(temp, archetype);
}

std::unordered_map<std::string, std::string>
locator::facet_directories() const {
    std::unordered_map<std::string, std::string> r;

    const auto& mmp(physical_model_.meta_model_properties());
    for (const auto& pair : mmp.facet_properties()) {
        const auto& id(pair.first);
        const auto& fp(pair.second);
        r[id.value()] = fp.computed_directory_name();
    }

    return r;
}

}
