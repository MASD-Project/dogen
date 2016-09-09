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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_factory.hpp"
#include "dogen/quilt.cpp/types/properties/factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formatters.factory"));

const std::string namespace_separator("::");
const std::string registrar_name("registrar");
const std::string cmakelists_name("CMakeLists.txt");
const std::string odb_options_name("options.odb");
const std::string settings_not_found_for_formatter(
    "Settings not found for formatter: ");
const std::string element_settings_not_found_for_name(
    "Element settings not found for name: ");
const std::string derivatives_not_found_for_formatter(
    "Path derivatives not found for formatter: ");
const std::string properties_not_found(
    "Formatter properties not found for: ");
const std::string cast_failure("Failed to cast type: ");
const std::string empty_formatter_name("Formatter name is empty.");
const std::string cmake_modeline_name("cmake");
const std::string odb_modeline_name("odb");
const std::string cpp_modeline_name("cpp");

const std::string underscore("_");
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

const std::string empty_include_directive("Include directive is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

template<typename YarnConcreteElement>
inline const YarnConcreteElement& convert(const yarn::element& e) {
    auto ptr(dynamic_cast<YarnConcreteElement const*>(&e));
    if (!ptr) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, error) << cast_failure << id;
        BOOST_THROW_EXCEPTION(building_error(cast_failure + id));
    }
    return *ptr;
}

template<typename YarnConcreteElement>
inline bool is(const boost::shared_ptr<yarn::element> e) {
    auto ptr(boost::dynamic_pointer_cast<YarnConcreteElement>(e));
    return ptr != nullptr;
}

template<typename YarnConcreteElement>
inline bool is(const yarn::model& m, const yarn::name& n) {
    const auto i(m.elements().find(n.id()));
    if (i == m.elements().end())
        return false;

    return is<YarnConcreteElement>(i->second);
}

std::unordered_map<std::string, settings::path_settings>
factory::clone_path_settings(
    const std::unordered_map<std::string, settings::path_settings>& source,
    const std::string& source_formatter_name,
    const std::string& destination_formatter_name) const {

    const auto i(source.find(source_formatter_name));
    if (i == source.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << source_formatter_name;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + source_formatter_name));
    }

    std::unordered_map<std::string, settings::path_settings> r;
    r.insert(std::make_pair(destination_formatter_name, i->second));
    return r;
}

yarn::name factory::create_name(const yarn::name& model_name,
    const std::string& simple_name) const {
    yarn::name_factory nf;
    return nf.build_element_in_model(model_name, simple_name);
}

path_derivatives factory::create_path_derivatives(
    const config::cpp_options& opts, const yarn::model& m,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const yarn::name& n,
    const std::string& formatter_name) const {

    path_derivatives_factory pdf(opts, m, ps);
    const auto pd(pdf.make(n));
    const auto i(pd.find(formatter_name));
    if (i == pd.end()) {
        BOOST_LOG_SEV(lg, error) << derivatives_not_found_for_formatter
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(building_error(
                derivatives_not_found_for_formatter + formatter_name));
    }
    return i->second;
}

bool factory::is_enabled(const formatter_properties_repository& fprp,
    const yarn::name& n, const std::string& formatter_name) const {

    const auto i(fprp.by_id().find(n.id()));
    if (i == fprp.by_id().end()) {
        BOOST_LOG_SEV(lg, error) << properties_not_found << n.id();
        BOOST_THROW_EXCEPTION(building_error(properties_not_found + n.id()));
    }

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + formatter_name));
    }
    return j->second.enabled();
}

std::shared_ptr<formattable> factory::make_registrar_info(
    const config::cpp_options& opts,
    const settings::element_settings_repository& esrp,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    formatter_properties_repository& fprp,
    const yarn::model& m) const {

    const auto n(create_name(m.name(), registrar_name));
    BOOST_LOG_SEV(lg, debug) << "Making registrar: " << n.id();

    name_builder b;
    auto r(std::make_shared<registrar_info>());
    r->namespaces(b.namespace_list(n));
    r->id(n.id());

    const auto i(esrp.by_id().find(n.id()));
    if (i == esrp.by_id().end()) {
        const auto id(n.id());
        BOOST_LOG_SEV(lg, error) << element_settings_not_found_for_name << id;
        BOOST_THROW_EXCEPTION(
            building_error(element_settings_not_found_for_name + id));
    }

    for (const auto& pair : m.references()) {
        if (pair.second != yarn::origin_types::system) {
            /* we want the model name to contribute to the list of
             * namespaces so we must disable model name detection.
             */
            const bool detect_model_name(false);
            const auto l(b.namespace_list(pair.first, detect_model_name));
            const auto s(boost::algorithm::join(l, namespace_separator));
            r->model_dependencies().push_back(s);
        }
    }

    for (const auto& l : m.leaves())
        r->leaves().push_back(b.qualified_name(l));
    r->leaves().sort();

    const auto lambda([&](const std::string& src, const std::string& dst) {
            const auto cloned_ps(clone_path_settings(ps, src, dst));
            const auto pd(create_path_derivatives(opts, m, cloned_ps, n, dst));

            formatter_properties r;
            r.file_path(pd.file_path());
            r.header_guard(pd.header_guard());
            r.enabled(is_enabled(fprp, m.name(), src));
            return r;
        });

    using formatters::serialization::traits;
    const auto ch_fn(traits::class_header_formatter_name());
    const auto rh_fn(traits::registrar_header_formatter_name());
    const auto fp1(lambda(ch_fn, rh_fn));
    fprp.by_id()[r->id()][rh_fn] = fp1;

    const auto ci_fn(traits::class_implementation_formatter_name());
    const auto ri_fn(traits::registrar_implementation_formatter_name());
    auto fp2(lambda(ci_fn, ri_fn));

    const auto j(fprp.by_id().find(n.id()));
    if (j == fprp.by_id().end()) {
        const auto id(n.id());
        BOOST_LOG_SEV(lg, error) << properties_not_found << id;
        BOOST_THROW_EXCEPTION(building_error(properties_not_found + id));
    }

    const auto k(j->second.find(ri_fn));
    if (k == j->second.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter << ri_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + ri_fn));
    }
    fp2.inclusion_dependencies(k->second.inclusion_dependencies());
    fprp.by_id()[r->id()][ri_fn] = fp2;

    BOOST_LOG_SEV(lg, debug) << "Made registrar: " << n.id();
    return r;
}

std::forward_list<std::shared_ptr<formattable> > factory::
make_cmakelists(const config::cpp_options& opts,
    const dogen::formatters::file_properties_workflow& fpwf,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formatter_properties_repository& fprp,
    const yarn::model& m) const
{
    std::forward_list<std::shared_ptr<formattable> > r;
    if (opts.disable_cmakelists()) {
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Generating source CMakeLists.";
    using boost::algorithm::join;
    const auto mn(join(m.name().location().model_modules(), underscore));

    auto cm(std::make_shared<cmakelists_info>());
    cm->model_name(mn);
    cm->file_name(cmakelists_name);

    const auto fp(fpwf.execute(cmake_modeline_name));
    cm->file_properties(fp);

    if (!m.name().location().external_modules().empty())
        cm->product_name(m.name().location().external_modules().front());

    using namespace formatters::types;
    const auto ch_fn(traits::class_header_formatter_name());
    const auto i(ps.find(ch_fn));
    if (i == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << ch_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + ch_fn));
    }

    auto base(opts.project_directory_path());
    for (const auto& p : m.name().location().model_modules())
        base /= p;

    cm->source_file_path(base / i->second.source_directory_name() /
        cmakelists_name);
    cm->include_file_path(base / cmakelists_name);

    const auto odb_ch_fn(
        formatters::odb::traits::class_header_formatter_name());
    cm->odb_enabled(is_enabled(fprp, m.name(), odb_ch_fn));
    const auto j(ps.find(odb_ch_fn));
    if (j == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << odb_ch_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + odb_ch_fn));
    }
    cm->odb_folder(j->second.facet_directory());

    r.push_front(cm);
    return r;
}

std::shared_ptr<formattable>
factory::make_odb_options(const config::cpp_options& opts,
    const dogen::formatters::file_properties_workflow& fpwf,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formatter_properties_repository& fprp,
    const yarn::model& m) const {

    using namespace formatters::odb;
    const auto ch_fn(traits::class_header_formatter_name());
    if (!is_enabled(fprp, m.name(), ch_fn)) {
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";
        return std::shared_ptr<formattable>();
    }

    BOOST_LOG_SEV(lg, debug) << "Generating ODB options.";

    auto r(std::make_shared<odb_options_info>());
    r->file_name(odb_options_name);

    using boost::algorithm::join;
    const auto mn(join(m.name().location().model_modules(), underscore));
    r->model_name(mn);

    const auto fp(fpwf.execute(odb_modeline_name));
    r->file_properties(fp);

    const auto i(ps.find(ch_fn));
    if (i == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << ch_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + ch_fn));
    }
    r->odb_folder(i->second.facet_directory());

    boost::filesystem::path file_path(opts.project_directory_path());
    for (const auto& module : m.name().location().model_modules())
        file_path /= module;

    file_path /= i->second.source_directory_name();
    file_path /= odb_options_name;
    r->file_path(file_path);

    const auto epp(m.name().location().external_modules());
    if (!epp.empty())
        r->product_name(epp.front());

    return r;
}

} } } }
