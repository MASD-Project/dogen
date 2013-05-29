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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/types/workflow_failure.hpp"
#include "dogen/cpp/types/formatters/factory.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"
#include "dogen/cpp/types/formatters/src_cmakelists.hpp"
#include "dogen/cpp/types/formatters/include_cmakelists.hpp"
#include "dogen/cpp/types/formatters/odb_options.hpp"
#include "dogen/cpp/types/extractor.hpp"
#include "dogen/cpp/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.workflow"));

const std::string includer_name("all");
const std::string registrar_name("registrar");
const std::string cmakelists_file_name("CMakeLists.txt");
const std::string odb_options_file_name("options.odb");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string could_not_find_pod("Could not find pod: ");
const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet");

}

namespace dogen {
namespace cpp {

workflow::
workflow(const sml::model& model, const config::cpp_settings& settings) :
    model_(model), settings_(settings), locator_(model.name(), settings_),
    includer_(model_, locator_, settings_),
    file_info_factory_(locator_),
    transformer_(model_),
    descriptor_factory_(settings_.enabled_facets()), extractor_(model_.pods()) {

    validate_settings();
}

void workflow::validate_settings() const {
    if (settings_.use_integrated_io()) {
        const auto f(settings_.enabled_facets());
        const bool has_io_facet(f.find(config::cpp_facet_types::io) != f.end());
        if (has_io_facet) {
            BOOST_LOG_SEV(lg, error)
                << integrated_io_incompatible_with_io_facet;
            BOOST_THROW_EXCEPTION(workflow_failure(
                    integrated_io_incompatible_with_io_facet));
        }
    }

    const auto f(settings_.enabled_facets());
    if (f.find(config::cpp_facet_types::types) == f.end()) {
        BOOST_LOG_SEV(lg, error) << domain_facet_must_be_enabled;
        BOOST_THROW_EXCEPTION(workflow_failure(domain_facet_must_be_enabled));
    }
}

workflow::result_entry_type workflow::format(const file_info& fi) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting:" << fi.file_path().string();
    formatters::factory factory(settings_);
    formatters::file_formatter::shared_ptr ff;
    std::ostringstream s;
    ff = factory.create(s, fi.facet_type(), fi.file_type(), fi.aspect_type());
    ff->format(fi);
    return std::make_pair(fi.file_path(), s.str());
}

class_info workflow::
generate_class_info_recursive(std::unordered_map<sml::qname, class_info>& infos,
    const sml::qname& qn) const {

    const auto i(model_.pods().find(qn));
    if (i == model_.pods().end()) {
        BOOST_LOG_SEV(lg, error) << could_not_find_pod << qn;
        BOOST_THROW_EXCEPTION(workflow_failure(could_not_find_pod +
                boost::lexical_cast<std::string>(qn)));
    }

    boost::optional<class_info> pci;
    const auto p(i->second);
    const auto pn(p.parent_name());
    if (pn) {
        auto j(infos.find(*pn));
        if (j == infos.end()) {
            pci = generate_class_info_recursive(infos, *pn);
            infos.insert(std::make_pair(*p.parent_name(), *pci));
        } else
            pci = j->second;
    }

    boost::optional<class_info> opci;
    const auto opn(p.original_parent_name());
    if (opn) {
        auto j(infos.find(*opn));
        if (j == infos.end()) {
            opci = generate_class_info_recursive(infos, *opn);
            infos.insert(std::make_pair(*p.original_parent_name(), *opci));
        } else
            opci = j->second;
    }

    return transformer_.transform(p, pci, opci);
}

workflow::result_type workflow::generate_classes_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate classes activity.";

    workflow::result_type r;
    std::unordered_map<sml::qname, class_info> infos;
    for (const auto& pair : model_.pods()) {
        const auto p(pair.second);

        if (p.generation_type() == sml::generation_types::no_generation)
            continue;

        const auto pt(p.pod_type());
        const auto ct(p.category_type());
        const auto ci(generate_class_info_recursive(infos, p.name()));
        const auto rel(extractor_.extract_dependency_graph(p));
        for (const auto& cd : descriptor_factory_.create(p.name(), ct, pt)) {
            const auto il(includer_.includes_for_pod(cd, rel));
            auto fi(file_info_factory_.create(ci, cd, il));

            // we want to make sure we do not actually generate code
            // for partial generation, so override the output of the
            // factory. however, as we still want to create forward
            // declarations, ignore those.
            using sml::generation_types;
            if (cd.aspect_type() != aspect_types::forward_decls &&
                p.generation_type() == generation_types::partial_generation) {
                fi.aspect_type(aspect_types::null_aspect);
            }
            r.insert(format(fi));

            const auto registrable_aspect(
                fi.aspect_type() == aspect_types::main ||
                fi.aspect_type() == aspect_types::null_aspect);
            const auto header(file_types::header);
            if (fi.file_type() == header && registrable_aspect)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate classes activity";
    return r;
}

workflow::result_type workflow::generate_namespaces_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate namespaces activity.";

    const auto header(file_types::header);
    const auto doc(aspect_types::namespace_doc);

    workflow::result_type r;
    if (!model_.documentation().empty()) {
        const auto ni(transformer_.transform_model_into_namespace());
        for (const auto& cd : descriptor_factory_.create(model_)) {
            const auto fi(file_info_factory_.create(ni, cd));
            r.insert(format(fi));

            if (fi.file_type() == header && fi.aspect_type() == doc)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    for (const auto& pair : model_.packages()) {
        const auto& p(pair.second);

        if (p.documentation().empty())
            continue;

        const auto ni(transformer_.transform(p));
        for (const auto& cd : descriptor_factory_.create(p.name())) {
            const auto fi(file_info_factory_.create(ni, cd));
            r.insert(format(fi));

            if (fi.file_type() == header && fi.aspect_type() == doc)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate namespaces activity.";
    return r;
}

workflow::result_type workflow::generate_registrars_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate registrars activity.";

    sml::qname qn;
    qn.model_name(model_.name());
    qn.external_package_path(model_.external_package_path());
    qn.type_name(registrar_name);

    // FIXME: we should probably have "a not SML type" instead of lying
    qn.meta_type(sml::meta_types::pod);

    workflow::result_type r;
    const auto ri(transformer_.transform_model_into_registrar());
    for (const auto& cd : descriptor_factory_.create_registrar(qn)) {
        const auto il(includer_.includes_for_registrar(cd));
        const auto fi(file_info_factory_.create_registrar(ri, cd, il));
        r.insert(format(fi));

        const auto header(file_types::header);
        const auto registrar(aspect_types::registrar);
        if (fi.file_type() == header && fi.aspect_type() == registrar)
            includer_.register_header(fi.facet_type(), fi.relative_path());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate registrars activity";
    return r;
}

workflow::result_type workflow::generate_includers_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate includers activity.";

    sml::qname qn;
    qn.type_name(includer_name);
    qn.external_package_path(model_.external_package_path());
    qn.model_name(model_.name());

    // FIXME: we should probably have "a not SML type" instead of lying
    qn.meta_type(sml::meta_types::pod);

    workflow::result_type r;
    for (const auto& cd : descriptor_factory_.create_includer(qn)) {
        const auto il(includer_.includes_for_includer_files(cd));
        r.insert(format(file_info_factory_.create_includer(cd, il)));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate includers activity.";
    return r;
}

workflow::result_type workflow::generate_visitors_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate visitors activity.";

    workflow::result_type r;
    for (const auto& pair : model_.pods()) {
        const auto p(pair.second);

        if (!p.is_visitable())
            continue;

        const auto vi(transformer_.transform_into_visitor(p));
        const auto rel(extractor_.extract_inheritance_graph(p.name()));
        for (const auto& cd : descriptor_factory_.create_visitor(p.name())) {
            const auto il(includer_.includes_for_visitor(cd, rel));
            const auto fi(file_info_factory_.create_visitor(vi, cd, il));
            r.insert(format(fi));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate visitors activity.";
    return r;
}

workflow::result_type workflow::generate_enums_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate enums activity.";

    workflow::result_type r;
    for (const auto& pair : model_.enumerations()) {
        const auto& e(pair.second);
        if (e.generation_type() == sml::generation_types::no_generation)
            continue;

        const auto ei(transformer_.transform(e));

        const auto ct(sml::category_types::user_defined);
        for (const auto& cd : descriptor_factory_.create(e.name(), ct)) {
            const auto il(includer_.includes_for_enumeration(cd));
            const auto fi(file_info_factory_.create(ei, cd, il));
            r.insert(format(fi));

            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate enums activity.";
    return r;
}

workflow::result_type workflow::generate_exceptions_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Started generate exceptions activity.";

    workflow::result_type r;
    for (const auto& pair : model_.exceptions()) {
        const auto& e(pair.second);
        if (e.generation_type() == sml::generation_types::no_generation)
            continue;

        const auto ei(transformer_.transform(e));

        const auto ct(sml::category_types::user_defined);
        for (const auto& cd : descriptor_factory_.create(e.name(), ct)) {
            const auto il(includer_.includes_for_exception(cd));
            const auto fi(file_info_factory_.create(ei, cd, il));
            r.insert(format(fi));

            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate exceptions activity";
    return r;
}

workflow::result_type workflow::generate_file_infos_activity() const {
    const auto a(generate_enums_activity());
    const auto b(generate_exceptions_activity());
    const auto c(generate_classes_activity());
    const auto d(generate_namespaces_activity());
    const auto e(generate_registrars_activity());
    const auto f(generate_includers_activity());
    const auto g(generate_visitors_activity());

    workflow::result_type r;
    r.insert(a.begin(), a.end());
    r.insert(b.begin(), b.end());
    r.insert(c.begin(), c.end());
    r.insert(d.begin(), d.end());
    r.insert(e.begin(), e.end());
    r.insert(f.begin(), f.end());
    r.insert(g.begin(), g.end());
    return r;
}

workflow::result_type workflow::generate_cmakelists_activity() const {
    cmakelists_info ci;
    ci.model_name(model_.name());
    ci.file_name(cmakelists_file_name);
    ci.file_path(locator_.absolute_path_to_src(ci.file_name()));
    BOOST_LOG_SEV(lg, debug) << "Formatting: " << ci.file_path().string();

    if (!model_.external_package_path().empty())
        ci.product_name(model_.external_package_path().front());

    std::ostringstream stream;
    formatters::src_cmakelists src(stream);
    src.format(ci);

    workflow::result_type r;
    r.insert(std::make_pair(ci.file_path(), stream.str()));

    if (!settings_.split_project()) {
        const auto f(settings_.enabled_facets());
        const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
        stream.str("");
        ci.file_path(locator_.absolute_path(ci.file_name()));
        BOOST_LOG_SEV(lg, debug) << "Formatting: " << ci.file_path().string();

        formatters::include_cmakelists inc(stream, odb_enabled,
            settings_.odb_facet_folder());
        inc.format(ci);
        r.insert(std::make_pair(ci.file_path(), stream.str()));
    }

    return r;
}

workflow::result_entry_type workflow::generate_odb_options_activity() const {
    BOOST_LOG_SEV(lg, info) << "Generating ODB options file.";

    odb_options_info ooi;
    ooi.file_name(odb_options_file_name);
    ooi.file_path(locator_.absolute_path_to_src(ooi.file_name()));
    ooi.model_name(model_.name());
    ooi.odb_folder(settings_.odb_facet_folder());

    if (!model_.external_package_path().empty())
        ooi.product_name(model_.external_package_path().front());

    BOOST_LOG_SEV(lg, debug) << "Formatting:" << ooi.file_path().string();
    std::ostringstream stream;
    formatters::odb_options f(stream);
    f.format(ooi);

    return std::make_pair(ooi.file_path(), stream.str());
}

std::vector<boost::filesystem::path> workflow::managed_directories() const {
    return locator_.managed_directories();
}

workflow::result_type workflow::execute() {
    BOOST_LOG_SEV(lg, info) << "C++ backend started.";

    workflow::result_type r(generate_file_infos_activity());
    if (settings_.disable_cmakelists())
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
    else {
        const auto cm(generate_cmakelists_activity());
        r.insert(cm.begin(), cm.end());
    }

    const auto f(settings_.enabled_facets());
    const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
    if (odb_enabled)
        r.insert(generate_odb_options_activity());
    else
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";

    BOOST_LOG_SEV(lg, info) << "C++ backend finished.";
    return r;
}

} }
