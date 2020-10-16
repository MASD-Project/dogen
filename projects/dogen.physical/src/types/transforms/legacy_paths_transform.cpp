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
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/legacy_archetype_kind_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/legacy_paths_transform.hpp"

using dogen::identification::entities::physical_meta_id;

namespace {

const std::string transform_id("physical.transforms.legacy_paths_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

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
const std::string invalid_archetype("Archetype does not have a kind: ");
const std::string invalid_archetype_kind("Archetype kind is not supported: ");

const std::string archetype_class_header_factory_ak(
    "archetype_class_header_factory");
const std::string archetype_class_header_transform_ak(
    "archetype_class_header_transform");
const std::string archetype_kind_class_header_factory_ak(
    "archetype_kind_class_header_factory");
const std::string backend_class_header_factory_ak(
    "backend_class_header_factory");
const std::string backend_class_header_transform_ak(
    "backend_class_header_transform");
const std::string builtin_header_ak("builtin_header");
const std::string class_header_ak("class_header");
const std::string enum_header_ak("enum_header");
const std::string exception_header_ak("exception_header");
const std::string facet_class_header_factory_ak("facet_class_header_factory");
const std::string facet_class_header_transform_ak(
    "facet_class_header_transform");
const std::string feature_bundle_header_ak("feature_bundle_header");
const std::string feature_template_bundle_header_ak(
    "feature_template_bundle_header");
const std::string namespace_header_ak("namespace_header");
const std::string part_class_header_factory_ak("part_class_header_factory");
const std::string part_class_header_transform_ak("part_class_header_transform");
const std::string primitive_header_ak("primitive_header");
const std::string type_registrar_header_ak("type_registrar_header");
const std::string visitor_header_ak("visitor_header");
const std::string class_forward_declarations_ak("class_forward_declarations");
const std::string primitive_forward_declarations_ak(
    "primitive_forward_declarations");
const std::string visitor_forward_declarations_ak(
    "visitor_forward_declarations");
const std::string variability_initializer_header_ak(
    "variability_initializer_header");
const std::string variability_initializer_implementation_ak(
    "variability_initializer_implementation");

const std::string archetype_class_implementation_factory_ak(
    "archetype_class_implementation_factory");
const std::string archetype_class_implementation_transform_ak(
    "archetype_class_implementation_transform");
const std::string archetype_kind_class_implementation_factory_ak(
    "archetype_kind_class_implementation_factory");
const std::string backend_class_implementation_factory_ak(
    "backend_class_implementation_factory");
const std::string backend_class_implementation_transform_ak(
    "backend_class_implementation_transform");
const std::string class_implementation_ak("class_implementation");
const std::string enum_implementation_ak("enum_implementation");
const std::string facet_class_implementation_factory_ak(
    "facet_class_implementation_factory");
const std::string facet_class_implementation_transform_ak(
    "facet_class_implementation_transform");
const std::string feature_bundle_implementation_ak(
    "feature_bundle_implementation");
const std::string feature_template_bundle_implementation_ak(
    "feature_template_bundle_implementation");
const std::string part_class_implementation_factory_ak(
    "part_class_implementation_factory");
const std::string part_class_implementation_transform_ak(
    "part_class_implementation_transform");
const std::string primitive_implementation_ak("primitive_implementation");
const std::string type_registrar_implementation_ak(
    "type_registrar_implementation");

const std::string tests_cmakelists_ak("cmakelists");
const std::string include_cmakelists_ak("include_cmakelists");
const std::string source_cmakelists_ak("source_cmakelists");
const std::string common_odb_options_ak("common_odb_options");
const std::string logic_less_template_ak("logic_less_template");
const std::string main_ak("main");
const std::string msbuild_targets_ak("msbuild_targets");
const std::string object_odb_options_ak("object_odb_options");
const std::string primitive_odb_options_ak("primitive_odb_options");
const std::string project_ak("project");
const std::string solution_ak("solution");

const std::string class_ak("class");
const std::string enum_ak("enum");
const std::string exception_ak("exception");
const std::string primitive_ak("primitive");
const std::string builtin_ak("builtin");
const std::string assistant_ak("assistant");

}

namespace dogen::physical::transforms {

/**
 * @brief Generates paths for project items, given qualified name.
 */
class locator {
public:
    explicit locator(const physical::entities::model& pm);

private:
    static boost::filesystem::path
    make_headers_path(const boost::filesystem::path& project_path,
        const physical::entities::model& pm);

    static boost::filesystem::path
    make_templates_path(const physical::entities::model& pm);

    /**
     * @brief Given a facet, returns its configuration.
     *
     * @pre Facet must have a configuration.
     */
    const physical::entities::facet_properties&
    facet_properties_for_facet(const std::string& facet) const;

    /**
     * @brief Given an archetype, returns its properties.
     *
     * @pre Archetype must have a properties.
     */
    const physical::entities::archetype_properties&
    archetype_properties_for_archetype(const std::string& archetype) const;

public:
    /**
     * @brief Returns the extension used for header files.
     */
    std::string header_file_extension() const;

    /**
     * @brief Returns the extension used for implementation files.
     */
    std::string implementation_file_extension() const;

    /**
     * @brief Returns the postfix for the supplied facet.
     */
    std::string postfix_for_facet(const std::string& facet) const;

private:
    /**
     * @brief Returns the absolute path to the project folder.
     */
    static boost::filesystem::path
    make_project_path(const boost::filesystem::path output_directory_path,
        const physical::entities::model& pm);

    /**
     * @brief Generates the facet path segment of a file path.
     *
     * The facet path segment is the same for both include and source
     * folders; it starts at the facet and includes the file name.
     */
    boost::filesystem::path
    make_facet_path(const std::string& archetype, const std::string& extension,
        const identification::entities::logical_name& n,
        const bool is_csharp = false) const;
    boost::filesystem::path make_facet_path_temp(const std::string& archetype,
        const std::string& file_name,
        const identification::entities::logical_name& n) const;

    /**
     * @brief Makes the first part of the inclusion path.
     */
    boost::filesystem::path
    make_inclusion_path_prefix(
        const identification::entities::logical_name& n) const;

    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_inclusion_path(const std::string& archetype,
        const std::string& extension,
        const identification::entities::logical_name& n) const;

public:
    /**
     * @brief Top-level project directory.
     */
    boost::filesystem::path project_path() const;

    /**
     * @brief Top-level headers project directory.
     */
    boost::filesystem::path headers_project_path() const;

    /**
     * @brief Top-level templates project directory.
     */
    boost::filesystem::path templates_project_path() const;

    /**
     * @brief Top-level headers model directory.
     */
    boost::filesystem::path headers_model_path() const;

public:
    /**
     * @brief Name of the include directory.
     */
    std::string include_directory_name() const;

    /**
     * @brief Name of the source directory.
     */
    std::string source_directory_name() const;

    /**
     * @brief Name of the tests directory.
     */
    std::string tests_directory_name() const;

    /**
     * @brief Name of the templates directory.
     */
    std::string templates_directory_name() const;

public:
    /**
     * @brief Generate the relative path to the include directory.
     */
    boost::filesystem::path make_relative_include_path(
        bool for_include_statement) const;

    /**
     * @brief Generate the relative path to the include directory for
     * a given facet.
     */
    boost::filesystem::path make_relative_include_path_for_facet(
        const std::string& facet, bool for_include_statement = false) const;

    /**
     * @brief Generate the inclusion path for C++ headers.
     */
    boost::filesystem::path make_inclusion_path_for_cpp_header(
        const identification::entities::logical_name&
        n, const std::string& archetype) const;

    /**
     * @brief Generate the full path to the include directory
     */
    boost::filesystem::path make_full_path_to_include_directory() const;

    /**
     * @brief Generate the full path to the implementation directory
     */
    boost::filesystem::path make_full_path_to_implementation_directory() const;

    /**
     * @brief Generate the full path to the facet include directory.
     */
    boost::filesystem::path make_full_path_to_include_facet_directory(
        const std::string& facet) const;

    /**
     * @brief Generate the full path for C++ headers.
     */
    boost::filesystem::path make_full_path_for_cpp_header(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the relative implementation path for a facet.
     */
    boost::filesystem::path make_relative_implementation_path_for_facet(
        const std::string& facet) const;

    /**
     * @brief Generate the full path for templates.
     */
    boost::filesystem::path make_full_path_for_templates(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for C++ implementation for tests
     */
    boost::filesystem::path make_full_path_for_tests_cpp_implementation(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for entry point under tests.
     */
    boost::filesystem::path make_full_path_for_tests_cpp_main(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for C++ implementation.
     */
    boost::filesystem::path make_full_path_for_cpp_implementation(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in include.
     */
    boost::filesystem::path make_full_path_for_include_cmakelists(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in source.
     */
    boost::filesystem::path make_full_path_for_source_cmakelists(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in tests.
     */
    boost::filesystem::path make_full_path_for_tests_cmakelists(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in source.
     */
    boost::filesystem::path make_full_path_for_msbuild_targets(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the relatvie path for odb options.
     */
    boost::filesystem::path make_relative_path_for_odb_options(
        const identification::entities::logical_name& n,
        const std::string& archetype,
        bool include_source_directory = true) const;

    /**
     * @brief Generate the full path for odb options.
     */
    boost::filesystem::path make_full_path_for_odb_options(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_project(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_solution(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_visual_studio_project(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_visual_studio_solution(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

    /**
     * @brief Generate the full path for C# files.
     */
    boost::filesystem::path make_full_path_for_csharp(
        const identification::entities::logical_name& n,
        const std::string& archetype) const;

public:
    std::unordered_map<std::string, std::string> facet_directories() const;

private:
    const physical::entities::model& physical_model_;
    const identification::entities::logical_name& model_name_;
    const boost::filesystem::path project_path_;
    const boost::filesystem::path headers_project_path_;
    const boost::filesystem::path output_directory_path_;
    const boost::filesystem::path templates_project_path_;
    const bool split_mode_;
};

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
        BOOST_THROW_EXCEPTION(transform_exception(missing_facet_configuration));
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
            transform_exception(missing_archetype_configuration + archetype));
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
                transform_exception(missing_backend + backend_id.value()));
        }

        const auto dn(i->second.computed_directory_name());
        if (dn.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_backend_directory;
            BOOST_THROW_EXCEPTION(
                transform_exception(missing_backend_directory));
        }
        r /= dn;
    }

    BOOST_LOG_SEV(lg, trace) << "Project path: " << r;
    return r;
}

boost::filesystem::path locator::make_facet_path(const std::string& archetype,
    const std::string& extension, const logical_name& n,
    const bool is_csharp) const {
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
    if (n != model_name_ && n.is_container()) {
        BOOST_LOG_SEV(lg, trace) << "Adding module name.";
        r /= n.simple();
    } else {
        BOOST_LOG_SEV(lg, trace) << "NOT adding module name. Container: "
                                 << n.is_container();
    }

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << n.simple();

    if (!ap.computed_postfix().empty()) {
        if (!is_csharp)
            stream << underscore;
        stream<< ap.computed_postfix();
    }

    if (!ap.facet_properties().computed_postfix().empty()) {
        if (!is_csharp)
            stream << underscore;

        stream << ap.facet_properties().computed_postfix();
    }

    if (!extension.empty())
        stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, trace) << "Done making the facet path. Result: " << r;
    return r;
}

boost::filesystem::path
locator::make_facet_path_temp(const std::string& archetype,
    const std::string& file_name, const logical_name& n) const {
    BOOST_LOG_SEV(lg, trace) << "Making facet path TEMP for: "
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
    if (n != model_name_ && n.is_container()) {
        BOOST_LOG_SEV(lg, trace) << "Adding module name.";
        r /= n.simple();
    } else {
        BOOST_LOG_SEV(lg, trace) << "NOT adding module name. Container: "
                                 << n.is_container();
    }

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

boost::filesystem::path locator::make_full_path_for_csharp(
    const logical_name& n, const std::string& archetype) const {

    auto r(project_path_);
    const auto extension("cs");
    const auto facet_path(make_facet_path(archetype, extension, n,
            true/*is_csharp*/));
    r /= facet_path;

    BOOST_LOG_SEV(lg, trace) << "Full path c#: " << r;
    return r;
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

using entities::legacy_archetype_kind;

legacy_archetype_kind legacy_paths_transform::
get_archetye_kind(const std::string& archetype_name, const bool is_tests) {
    if (archetype_name == archetype_class_header_factory_ak ||
        archetype_name == archetype_class_header_transform_ak ||
        archetype_name == archetype_kind_class_header_factory_ak ||
        archetype_name == backend_class_header_factory_ak ||
        archetype_name == backend_class_header_transform_ak ||
        archetype_name == builtin_header_ak ||
        archetype_name == class_header_ak ||
        archetype_name == enum_header_ak ||
        archetype_name == exception_header_ak ||
        archetype_name == facet_class_header_factory_ak ||
        archetype_name == facet_class_header_transform_ak ||
        archetype_name == feature_bundle_header_ak ||
        archetype_name == feature_template_bundle_header_ak ||
        archetype_name == namespace_header_ak ||
        archetype_name == part_class_header_factory_ak ||
        archetype_name == part_class_header_transform_ak ||
        archetype_name == primitive_header_ak ||
        archetype_name == type_registrar_header_ak ||
        archetype_name == visitor_header_ak ||
        archetype_name == class_forward_declarations_ak ||
        archetype_name == primitive_forward_declarations_ak ||
        archetype_name == visitor_forward_declarations_ak ||
        archetype_name == variability_initializer_header_ak)
        return legacy_archetype_kind::cpp_header;
    else if (archetype_name == archetype_class_implementation_factory_ak ||
        archetype_name == archetype_class_implementation_transform_ak ||
        archetype_name == archetype_kind_class_implementation_factory_ak ||
        archetype_name == backend_class_implementation_factory_ak ||
        archetype_name == backend_class_implementation_transform_ak ||
        archetype_name == class_implementation_ak ||
        archetype_name == enum_implementation_ak ||
        archetype_name == facet_class_implementation_factory_ak ||
        archetype_name == facet_class_implementation_transform_ak ||
        archetype_name == feature_bundle_implementation_ak ||
        archetype_name == feature_template_bundle_implementation_ak ||
        archetype_name == part_class_implementation_factory_ak ||
        archetype_name == part_class_implementation_transform_ak ||
        archetype_name == primitive_implementation_ak ||
        archetype_name == type_registrar_implementation_ak ||
        archetype_name == variability_initializer_implementation_ak)
        return is_tests ?
            legacy_archetype_kind::tests_cpp_implementation :
            legacy_archetype_kind::cpp_implementation;
    else if (archetype_name == include_cmakelists_ak)
        return legacy_archetype_kind::include_cmakelists;
    else if (archetype_name == source_cmakelists_ak)
        return legacy_archetype_kind::source_cmakelists;
    else if (archetype_name == tests_cmakelists_ak)
        return legacy_archetype_kind::tests_cmakelists;
    else if (archetype_name == logic_less_template_ak)
        return legacy_archetype_kind::templates;
    else if (archetype_name == main_ak)
        return is_tests ?
            legacy_archetype_kind::tests_cpp_main :
            legacy_archetype_kind::cpp_implementation;
    else if (archetype_name == msbuild_targets_ak)
        return legacy_archetype_kind::msbuild_targets;
    else if (archetype_name == common_odb_options_ak ||
        archetype_name == object_odb_options_ak ||
        archetype_name == primitive_odb_options_ak)
        return legacy_archetype_kind::odb_options;
    else if (archetype_name == project_ak)
        return legacy_archetype_kind::visual_studio_project;
    else if (archetype_name == solution_ak)
        return legacy_archetype_kind::visual_studio_solution;
    else if (archetype_name == class_ak || archetype_name == enum_ak ||
        archetype_name == exception_ak || archetype_name == primitive_ak ||
        archetype_name == builtin_ak || archetype_name == assistant_ak)
        return legacy_archetype_kind::csharp_implementation;

    BOOST_LOG_SEV(lg, error) << invalid_archetype << archetype_name;
    BOOST_THROW_EXCEPTION(
        transform_exception(invalid_archetype + archetype_name));
}

boost::filesystem::path legacy_paths_transform::
get_path_for_archetype(const identification::entities::logical_name& ln,
    const identification::entities::physical_meta_name& pmn,
    const locator& l) {

    const auto& pmid(pmn.id());
    const auto an(pmn.location().archetype());
    const bool is_tests(pmn.location().facet() == "tests");
    const auto ak(get_archetye_kind(an, is_tests));

    BOOST_LOG_SEV(lg, debug) << "Processing archetype. ID: "
                             << pmid.value() << " Name: " << an;

    switch (ak) {
    case legacy_archetype_kind::visual_studio_solution:
        return l.make_full_path_for_visual_studio_solution(ln, pmid.value());
    case legacy_archetype_kind::visual_studio_project:
        return l.make_full_path_for_visual_studio_project(ln, pmid.value());
    case legacy_archetype_kind::odb_options:
        return l.make_full_path_for_odb_options(ln, pmid.value());
    case legacy_archetype_kind::msbuild_targets:
        return l.make_full_path_for_msbuild_targets(ln, pmid.value());
    case legacy_archetype_kind::tests_cmakelists:
        return l.make_full_path_for_tests_cmakelists(ln, pmid.value());
    case legacy_archetype_kind::source_cmakelists:
        return l.make_full_path_for_source_cmakelists(ln, pmid.value());
    case legacy_archetype_kind::include_cmakelists:
        return l.make_full_path_for_include_cmakelists(ln, pmid.value());
    case legacy_archetype_kind::cpp_header:
        return l.make_full_path_for_cpp_header(ln, pmid.value());
    case legacy_archetype_kind::cpp_implementation:
        return l.make_full_path_for_cpp_implementation(ln, pmid.value());
    case legacy_archetype_kind::tests_cpp_main:
    case legacy_archetype_kind::tests_cpp_implementation:
        return l.make_full_path_for_tests_cpp_implementation(ln, pmid.value());
    case legacy_archetype_kind::templates:
        return l.make_full_path_for_templates(ln, pmid.value());
    case legacy_archetype_kind::csharp_implementation:
        return l.make_full_path_for_csharp(ln, pmid.value());
    default: {
        std::ostringstream os;
        os << invalid_archetype_kind << ak;
        const auto msg(os.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(transform_exception(msg));
    } }
}

void legacy_paths_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "legacy paths",
        transform_id, m.name().id().value(), *ctx.tracer(), m);

    const locator l(m);
    for (auto& region_pair : m.regions_by_logical_id()) {
        auto& region(region_pair.second);
        for (auto& artefact_pair : region.artefacts_by_archetype()) {
            auto& a(artefact_pair.second);
            const auto& ln(region.provenance().logical_name());
            const auto fp(get_path_for_archetype(ln, a->meta_name(), l));
            a->path_properties().file_path(fp);
        }
    }

    stp.end_transform(m);
}

}
