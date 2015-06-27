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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formattables/name_builder.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_factory.hpp"
#include "dogen/cpp/types/formattables/factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.factory"));

const std::string namespace_separator("::");
const std::string registrar_name("registrar");
const std::string settings_not_found_for_formatter(
    "Settings not found for formatter: ");
const std::string derivatives_not_found_for_formatter(
    "Path derivatives not found for formatter: ");
const std::string properties_not_found_for_root(
    "Formatter properties not found for root object.");
const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::shared_ptr<formattable> factory::make_registrar_info(
    const config::cpp_options& opts,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formatter_properties_repository& fprp,
    const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Making a registrar for model: "
                             << sml::string_converter::convert(m.name());

    name_builder b;
    auto r(std::make_shared<registrar_info>());
    r->namespaces(b.namespace_list(m, m.name()));

    for (const auto& pair : m.references()) {
        if (pair.second != sml::origin_types::system) {
            const auto l(b.namespace_list(m, pair.first));
            const auto s(boost::algorithm::join(l, namespace_separator));
            r->model_dependencies().push_back(s);
        }
    }

    for (const auto& l : m.leaves())
        r->leaves().push_back(b.qualified_name(m, l));
    r->leaves().sort();

    using formatters::serialization::traits;
    const auto ch_fn(traits::class_header_formatter_name());
    const auto i(ps.find(ch_fn));
    if (i == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter << ch_fn;
        BOOST_THROW_EXCEPTION(
            building_error(settings_not_found_for_formatter + ch_fn));
    }

    std::unordered_map<std::string, settings::path_settings> ps2;
    const auto rh_fn(traits::registrar_header_formatter_name());
    ps2.insert(std::make_pair(rh_fn, i->second));

    sml::qname qn;
    qn.simple_name(registrar_name);
    qn.model_name(m.name().model_name());
    qn.external_module_path(m.name().external_module_path());

    path_derivatives_factory pdf(opts, m, ps2);
    const auto pd(pdf.make(qn));

    formatter_properties p;
    const auto j(pd.find(rh_fn));
    if (j == pd.end()) {
        BOOST_LOG_SEV(lg, error) << derivatives_not_found_for_formatter
                                 << rh_fn;
        BOOST_THROW_EXCEPTION(
            building_error(derivatives_not_found_for_formatter + rh_fn));
    }
    p.file_path(j->second.file_path());
    p.header_guard(j->second.header_guard());

    const auto k(fprp.formatter_properties_by_qname().find(m.name()));
    if (k == fprp.formatter_properties_by_qname().end()) {
        BOOST_LOG_SEV(lg, error) << properties_not_found_for_root;
        BOOST_THROW_EXCEPTION(building_error(properties_not_found_for_root));
    }

    const auto l(k->second.find(ch_fn));
    if (l == k->second.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter << ch_fn;
        BOOST_THROW_EXCEPTION(
            building_error(settings_not_found_for_formatter + ch_fn));
    }
    p.enabled(l->second.enabled());

    r->formatter_properties().insert(std::make_pair(rh_fn, p));

    BOOST_LOG_SEV(lg, debug) << "Made registrar.";

    return r;
}

std::forward_list<std::shared_ptr<formattable> > factory::
make_includers(const formattables::path_derivatives_repository& /*pdrp*/,
    const std::forward_list<
    std::shared_ptr<formatters::formatter_interface>>& /*formatters*/,
    const sml::model& /*m*/) const {
    /*std::unordered_map<std::string, std::list<std::string> >
        includes_by_formatter_name;

    for (const auto& qn_pair : pdrp.path_derivatives_by_qname()) {
        const auto qn(qn_pair.first);

        if (qn.model_name() != m.name().model_name())
            continue;

        for (const auto& fmt_pair : qn_pair.second) {
            const auto fn(fmt_pair.first);
            const auto pd(fmt_pair.second);

            const auto id(pd.inclusion_directive());
            if (id)
                includes_by_formatter_name[fn].push_back(*id);
        }
    }

    std::unordered_map<std::string, std::list<std::string> >
        includes_by_facet_name;
    for(const auto f : formatters) {
        const auto& oh(f->ownership_hierarchy());
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        const auto i(includes_by_formatter_name.find(oh.formatter_name()));
        if (i == includes_by_formatter_name.end())
            continue;

        auto& ifn(includes_by_facet_name[oh.facet_name()]);
        ifn.splice(ifn.begin(), i->second);
    }
    */
    std::forward_list<std::shared_ptr<formattable> > r;
    /*    for(const auto& pair : includes_by_facet_name) {
        auto inc(std::make_shared<includers_info>());
        // FIXME: formatter properties, etc.


        r.push_front(inc);
        }*/
    return r;
}

std::forward_list<std::shared_ptr<formattable> > factory::
make_cmakelists(const config::cpp_options& /*o*/, const sml::model& /*m*/) const
{
    /*
    std::forward_list<formatters::file> r;
    if (options_.cpp().disable_cmakelists()) {
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
        return r;
    }

    {
        const auto path(p.src_cmakelists().file_path());
        BOOST_LOG_SEV(lg, debug) << "Formatting: " << path.string();

        std::ostringstream s;
        cpp_formatters::src_cmakelists fmt(s);
        fmt.format(p.src_cmakelists());

        formatters::file file;
        file.path(path);
        file.content(s.str());
        r.push_front(file);
    }

    if (p.include_cmakelists()) {
        const auto path(p.include_cmakelists()->file_path());
        BOOST_LOG_SEV(lg, debug) << "Formatting: " << path.string();

        const auto fct(options_.cpp().enabled_facets());
        const auto i(fct.find(config::cpp_facet_types::odb));
        const bool is_odb_enabled(i != fct.end());
        const auto fct_folder(options_.cpp().odb_facet_folder());

        std::ostringstream s;
        cpp_formatters::include_cmakelists fmt(s, is_odb_enabled, fct_folder);
        fmt.format(*p.include_cmakelists());

        formatters::file file;
        file.path(path);
        file.content(s.str());
        r.push_front(file);
    }

    return r;

    */
    std::shared_ptr<cmakelists_info> cm(new cmakelists_info());
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(cm);
    return r;
}

std::shared_ptr<formattable> factory::make_odb_options(
    const config::cpp_options& /*o*/, const sml::model& /*m*/) const {
    /*
      const auto fcts(options_.cpp().enabled_facets());
      const auto i(fcts.find(config::cpp_facet_types::odb));
      const bool is_odb_enabled(i != fcts.end());
      if (!is_odb_enabled) {
      BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";
      return r;
      }

      const auto path(p.odb_options().file_path());
      BOOST_LOG_SEV(lg, debug) << "Formatting:" << path.string();

      std::ostringstream s;
      cpp_formatters::odb_options f(s);
      f.format(p.odb_options());

      formatters::file file;
      file.path(path);
      file.content(s.str());
      r.push_front(file);


     */
    std::shared_ptr<odb_options_info> r(new odb_options_info());
    return r;
}

} } }
