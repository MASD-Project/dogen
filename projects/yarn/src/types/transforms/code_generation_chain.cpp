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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.code_generation_chain"));

const std::string unsupported_language(
    "Could not find kernel for language: ");
const std::string disabled_kernel(
    "Kernel for requested language is disabled: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

std::shared_ptr<kernel_registrar> code_generation_chain::registrar_;

code_generation_chain::type_group code_generation_chain::
make_type_group(const annotations::type_repository& atrp,
    const std::list<annotations::archetype_location>& als) {
    type_group r;

    const annotations::type_repository_selector rs(atrp);
    const auto ekd(traits::enable_kernel_directories());
    r.enable_kernel_directories = rs.select_type_by_name(ekd);

    const auto en(traits::enabled());
    for (const auto al : als) {
        type_group tg;
        const auto kernel(al.kernel());
        r.enabled.push_back(rs.select_type_by_name(kernel, en));
    }

    return r;
}

std::unordered_set<std::string>
code_generation_chain::obtain_enabled_kernels(const type_group& tg,
    const annotations::annotation& ra) {

    std::unordered_set<std::string> r;
    const annotations::entry_selector s(ra);
    for (const auto& t : tg.enabled) {
        const bool enabled(s.get_boolean_content_or_default(t));
        if (!enabled)
            continue;

        r.insert(t.archetype_location().kernel());
    }

    return r;
}

bool code_generation_chain::obtain_enable_kernel_directories(
    const type_group& tg, const annotations::annotation& ra) {
    const annotations::entry_selector s(ra);
    return s.get_boolean_content_or_default(tg.enable_kernel_directories);
}

configuration code_generation_chain::make_configuration(
    const context& ctx, const std::list<annotations::archetype_location>& als,
    const annotations::annotation& ra) {

    configuration r;
    const auto tg(make_type_group(ctx.type_repository(), als));
    r.enabled_kernels(obtain_enabled_kernels(tg, ra));
    if (r.enabled_kernels().size() > 1) {
        BOOST_LOG_SEV(lg, warn) << "More than one kernel is enabled: "
                                << r.enabled_kernels().size()
                                << ". Forcing enable_kernel_directories.";
        r.enable_kernel_directories(true);
    } else
        r.enable_kernel_directories(obtain_enable_kernel_directories(tg, ra));

    return r;
}

kernel_registrar& code_generation_chain::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<kernel_registrar>();

    return *registrar_;
}

void code_generation_chain::
merge(code_generation_output&& src, code_generation_output& dst) {
    dst.artefacts().splice(dst.artefacts().end(), src.artefacts());
    dst.managed_directories().splice(dst.managed_directories().end(),
        src.managed_directories());
}

code_generation_output code_generation_chain::
transform(const context& ctx, const meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Transforming model: " << m.name().id();

    /*
     * No point in proceeding if the model has not types to
     * transform to text.
     */
    if (!m.has_generatable_types()) {
        BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
        return code_generation_output();
    }

    /*
     * Look for the kernel to perform this transformation. If none
     * is available, throw to let the user know it requested an
     * unsupported transformation.
     */
    const auto ol(m.output_language());
    BOOST_LOG_SEV(lg, debug) << "Looking for a kernel for language: " << ol;
    const auto ptr(registrar().kernel_for_language(ol));
    if (!ptr) {
        const auto s(boost::lexical_cast<std::string>(ol));
        BOOST_LOG_SEV(lg, error) << unsupported_language << s;
        BOOST_THROW_EXCEPTION(transformation_error(unsupported_language + s));
    }

    const auto& k(*ptr);
    const auto id(k.id());
    BOOST_LOG_SEV(lg, debug) << "Found kernel: " << id;

    /*
     * Ensure the kernel for the requested language is marked as
     * enabled. If it is disabled, the user has requested
     * conflicting options - output on language X but disable
     * kernel for language X - so we need to throw to let it know.
     */
    const auto& ra(m.root_module().annotation());
    const auto& als(registrar().archetype_locations());
    const auto cfg(make_configuration(ctx, als, ra));
    const auto& ek(cfg.enabled_kernels());
    const auto is_enabled(ek.find(id) != ek.end());
    if (!is_enabled) {
        BOOST_LOG_SEV(lg, error) << disabled_kernel << k.id();
        BOOST_THROW_EXCEPTION(transformation_error(disabled_kernel + id));
    }

    /*
     * Generate artefacts for all elements in model.
     */
    const bool ekd(cfg.enable_kernel_directories());
    auto r(k.generate(ctx, ekd, m));
    BOOST_LOG_SEV(lg, debug) << "Generated files for : " << id
                             << ". Total files: "
                             << std::distance(r.artefacts().begin(),
                                 r.artefacts().end());

    BOOST_LOG_SEV(lg, debug) << "Transformed model.";
    return r;
}

code_generation_output code_generation_chain::
transform(const context& ctx, const std::list<meta_model::model>& models) {
    BOOST_LOG_SEV(lg, debug) << "Transforming models: " << models.size();

    code_generation_output r;
    for (const auto& m : models)
        merge(transform(ctx, m), r);

    BOOST_LOG_SEV(lg, debug) << "Transformed models.";
    return r;
}

} } }
