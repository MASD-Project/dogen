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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/language_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.language_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string cpp_language("cpp");
const std::string csharp_language("csharp");
const std::string la_language("language_agnostic");

const std::string lanugage_not_set("Input language must be set.");
const std::string unsupported_lanugage("Language is not supported: ");

}

namespace masd::dogen::coding::transforms {

meta_model::languages language_transform::to_language(const std::string& s) {
    using meta_model::languages;
    if (s == cpp_language)
        return languages::cpp;
    else if (s == csharp_language)
        return languages::csharp;
    else if (s == la_language)
        return languages::language_agnostic;

    BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
    BOOST_THROW_EXCEPTION(transformation_error(unsupported_lanugage + s));
}

language_transform::type_group language_transform::
make_type_group(const annotations::type_repository& atrp) {
    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.output_language = s.select_type_by_name(traits::output_language());
    return r;
}

std::list<meta_model::languages>
language_transform::make_output_languages(const type_group& tg,
    const annotations::annotation& a) {
    const annotations::entry_selector s(a);

    std::list<meta_model::languages> r;
    if (!s.has_entry(tg.output_language))
        return r;

    const auto lang_str(s.get_text_collection_content(tg.output_language));
    for (const auto s : lang_str)
        r.push_back(to_language(s));

    return r;
}

void language_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "language transform",
        transform_id, m.name().id(), *ctx.tracer(), m);

    /*
     * Ensure the input language has been set by now.
     */
    using meta_model::languages;
    const bool has_input_language(m.input_language() != languages::invalid);
    if (!has_input_language) {
        BOOST_LOG_SEV(lg, error) << lanugage_not_set;
        BOOST_THROW_EXCEPTION(transformation_error(lanugage_not_set));
    }

    /*
     * If we've already got output languages, there is no work
     * required.
     */
    if (!m.output_languages().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model already has output languages: "
                                 << m.output_languages();
        return; // not ending tracing by design as there are no changes.
    }

    /*
     * Read the output languages requested by the user.
     */
    const auto ra(m.root_module()->annotation());
    const auto tg(make_type_group(*ctx.type_repository()));
    const auto ol(make_output_languages(tg, ra));

    /*
     * If the user did not set an output language, assume the input as
     * output. Validator will ensure this language is legal (e.g. the
     * output language does not result in a PIM).
     */
    if (ol.empty()) {
        m.output_languages().push_back(m.input_language());
        BOOST_LOG_SEV(lg, debug) << "No output language overrides found. "
                                 << "Defaulting to input languae: "
                                 << m.output_languages();
    } else {
        m.output_languages(ol);
        BOOST_LOG_SEV(lg, debug) << "Expanded output languages to: "
                                 << m.output_languages();
    }

    stp.end_transform(m);
}

}
