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
#include <sstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/yarn/types/resolution_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/io/attribute_io.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/separators.hpp"
#include "dogen/yarn/types/pretty_printer.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/identifiable_and_qualified_builder.hpp"
#include "dogen/yarn/types/resolver.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.resolver"));

const std::string empty;
const std::string orphan_object("Object's parent could not be located: ");
const std::string orphan_concept("Refined concept could not be located: ");
const std::string undefined_type("Object has attribute with undefined type: ");
const std::string invalid_underlying_element(
    "Could not find enumeration's underlying element: ");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace yarn {

bool resolver::
is_floating_point(const intermediate_model& im, const name& n) const {
    auto i(im.builtins().find(n.id()));
    return i != im.builtins().end() && i->second.is_floating_point();
}

bool resolver::is_builtin(const intermediate_model& im, const name& n) const {
    auto i(im.builtins().find(n.id()));
    if (i != im.builtins().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a built-in in model.";
        return true;
    }
    return false;
}

bool resolver::is_primitive(const intermediate_model& im, const name& n) const {
    auto i(im.primitives().find(n.id()));
    if (i != im.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }
    return false;
}

bool
resolver::is_enumeration(const intermediate_model& im, const name& n) const {
    auto i(im.enumerations().find(n.id()));
    if (i != im.enumerations().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an enumeration in model.";
        return true;
    }
    return false;
}

bool resolver::is_object(const intermediate_model& im, const name& n) const {
    auto i(im.objects().find(n.id()));
    if (i != im.objects().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an object in model.";
        return true;
    }
    return false;
}

bool resolver:: is_concept(const intermediate_model& im, const name& n) const {
    auto i(im.concepts().find(n.id()));
    if (i != im.concepts().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a concept in model.";
        return true;
    }
    return false;
}

bool resolver::is_name_referable(const indices& idx, const name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Checking to see if name is referable:" << n;

    const auto i(idx.elements_referable_by_attributes().find(n.id()));
    if (i != idx.elements_referable_by_attributes().end())
        return true;

    BOOST_LOG_SEV(lg, debug) << "Name not found in model or its not referable.";
    return false;
}

name resolver::
resolve_name(const intermediate_model& im, const indices& idx,
    const name& context, const name& n) const {

    BOOST_LOG_SEV(lg, debug) << "Resolving name: " << n.id();
    BOOST_LOG_SEV(lg, debug) << "Initial state: " << n;
    BOOST_LOG_SEV(lg, debug) << "Context: " << context;

    name_factory nf;
    const auto& l(n.location());
    const bool has_model_modules(!l.model_modules().empty());
    if (has_model_modules) {
        BOOST_LOG_SEV(lg, debug) << "Name has model modules.";

        /*
         * If the user has explicitly asked for a set of model
         * modules, the name is either correct as-is or it can only be
         * missing the external module path from either the context or
         * the references. Note that we always assume the types are
         * fully qualified when the user has populated the model
         * modules.
         */

        /*
         * First we try as-is.
         */
        BOOST_LOG_SEV(lg, debug) << "Resolving as is.";
        if (is_name_referable(idx, n)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return n;
        }

        /*
         * Now we try using the context's external modules.
         */
        {
            BOOST_LOG_SEV(lg, debug) << "Resolving using context: " << context;
            auto r(nf.build_combined_element_name(context, n));
            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        }

        /*
         * Does the name must belong to a reference?
         */
        for (const auto& pair : im.references()) {
            const auto& ref(pair.first);
            BOOST_LOG_SEV(lg, debug) << "Resolving using reference: " << ref;
            const auto r(nf.build_combined_element_name(ref, n));

            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        }

        /*
         * FIXME: the next two rules are really a bug. At present, if
         * we have a module in a model say "A" and the user refers to
         * a type like "A::B", we assume that A must mean module A and
         * we set the model modules of this property to the model that
         * contains A (say M). However, let's imagine that there also
         * is a model called A. Because of this we are now forced to
         * override the model M with A - which is what the two rules
         * below do - and see if it matches. This is not very
         * nice. This means for example that if a user specifically
         * asks for a type in model A but mistypes it and it happens
         * that this type also exists in model M, we incorrectly
         * resolve it.
         *
         * An alternative is to not set the model module in cases
         * where there is a potential conflict and leave it up to
         * resolver.
         */

        /*
         * Now we handle the case where a model has a package with the
         * same name as a model. In this case, we have mis-classified
         * a model module into an internal path. We must take the
         * model's external module path. Let's first try it with the
         * main model.
         */
        {
            BOOST_LOG_SEV(lg, debug) << "Resolving using model: " << im.name();

            auto r(nf.build_promoted_module_name(im.name(), n));
            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        }

        /*
         * Let's try the same thing but for the references. Note that
         * we do not need to go through all of this, we could simply
         * slot the references into a set and see if the internal
         * module path maps any of the references.
         */
        BOOST_LOG_SEV(lg, debug) << "Resolving as module collision with"
                                 << " model name.";

        for (const auto& pair : im.references()) {
            const auto& ref(pair.first);
            BOOST_LOG_SEV(lg, debug) << "Resolving using reference: "
                                     << ref;

            auto r(nf.build_promoted_module_name(context, n));
            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        }

        /*
         * The name cannot be resolved.
         */
        BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
        BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
    }

    /*
     * If the user has not supplied model modules, there are only two
     * possibilities: it is either referring to a name in the current
     * context or a name in the global module. The current context
     * takes precedence.
     */
    BOOST_LOG_SEV(lg, debug) << "Name does not have model modules.";
    const bool has_internal_modules(!l.internal_modules().empty());
    if (has_internal_modules) {
        BOOST_LOG_SEV(lg, debug) << "Name has internal modules.";

        /*
         * First we handle the case where a model has a package with
         * the same name as a model. In this case, we have
         * mis-classified a model module into an internal path. We
         * must take the model's external module path. Let's first try
         * it with the main model.
         */
        {
            BOOST_LOG_SEV(lg, debug) << "Resolving using model: " << im.name();

            auto r(nf.build_promoted_module_name(im.name(), n));
            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        }

        /*
         * Now let's try the same thing but for the references. Note
         * that we do not need to go through all of this, we could
         * simply slot the references into a set and see if the
         * internal module path maps any of the references.
         */
        BOOST_LOG_SEV(lg, debug) << "Resolving as module collision with"
                                 << " model name.";

        for (const auto& pair : im.references()) {
            const auto& ref(pair.first);
            BOOST_LOG_SEV(lg, debug) << "Resolving using reference: "
                                     << ref;

            auto r(nf.build_promoted_module_name(context, n));
            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        }

        /*
         * Now we know it's a "real" internal module path. Since the
         * user has bothered to provide an internal module path, we
         * should just go with what we got and not worry. This caters
         * for the case of the user providing an absolute internal
         * path, either to the current package or to elsewhere in the
         * same model as the context. Note that we do not support
         * relative paths from the context (e.g. add the user path to
         * the context path); we simply assume all provided paths are
         * absolute.
         *
         * We also handle the case where the context does not have an
         * internal module path - there is not much else we can do.
         */
        auto r(nf.build_combined_element_name(context, n,
                true/*populate_model_modules_if_blank*/));

        BOOST_LOG_SEV(lg, debug) << "With internal modules supplied: " << r;

        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }

        /*
         * The name cannot cannot be resolved.
         */
        BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
        BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
    }

    BOOST_LOG_SEV(lg, debug) << "Name does not have internal modules.";

    const bool context_has_internal_modules(
        !context.location().internal_modules().empty());
    if (context_has_internal_modules) {
        BOOST_LOG_SEV(lg, debug) << "Context has internal modules.";

        /*
         * If we do not have an internal module path set but the
         * context does, we need to traverse it all the way up to
         * the model module, and see if anything matches. This
         * allows us to refer to types inside a package without
         * having to fully qualify them.
         *
         * We start at the outermost internal module and make our
         * way upwards.
         */
        auto context_copy(context);
        auto r(nf.build_combined_element_name(context_copy, n,
                true/*populate_model_modules_if_blank*/,
                true/*populate_internal_modules_if_blank*/));

        BOOST_LOG_SEV(lg, debug) << "Internal modules descent: " << r;

        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }

        do {
            context_copy.location().internal_modules().pop_back();
            r.location().internal_modules().clear();
            r = nf.build_combined_element_name(context_copy, r,
                true/*populate_model_modules_if_blank*/,
                true/*populate_internal_modules_if_blank*/);

            BOOST_LOG_SEV(lg, debug) << "Internal modules descent: " << r;

            if (is_name_referable(idx, r)) {
                BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
                return r;
            }
        } while (!context_copy.location().internal_modules().empty());
    } else
        BOOST_LOG_SEV(lg, debug) << "Context does not have internal modules.";

    /*
     * If the name has no internal or external modules, and the
     * context hasn't got them either (or it did, but it didn't help),
     * then perhaps the user just wants to refer to a type in the
     * model.
     */
    {
        auto r(nf.build_combined_element_name(context, n,
                true/*populate_model_modules_if_blank*/));

        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    }

    /*
     * Finally, the only other possibility is that the name is on
     * the global module.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying global module.";
    if (is_name_referable(idx, n)) {
        BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
        return n;
    }

    /*
     * The name cannot cannot be resolved.
     */
    BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
}

void resolver::resolve_name_tree(const intermediate_model& im,
    const indices& idx, const name& owner, name_tree& nt) const {
    const name n(resolve_name(im, idx, owner, nt.current()));

    BOOST_LOG_SEV(lg, debug) << "Resolved name: " << nt.current().id()
                             << " to: " << n.id();
    nt.current(n);
    if (is_builtin(im, n)) {
        nt.is_current_simple_type(true);
        nt.is_floating_point(is_floating_point(im, n));
    } else
        nt.is_current_simple_type(is_enumeration(im, n));

    const auto i(idx.objects_always_in_heap().find(n.id()));
    nt.are_children_opaque(i != idx.objects_always_in_heap().end());

    identifiable_and_qualified_builder iqb;
    iqb.add(n);

    /*
     * Strictly speaking this is not directly related to
     * resolution. However, we can only find circular dependencies
     * after we have resolved all names and since we're already here
     * might as well mark them.
     */
    if (owner == nt.current()) {
        nt.is_circular_dependency(true);
        BOOST_LOG_SEV(lg, debug) << "Found circular dependency. Owner: "
                                 << owner.id();
    }

    for (auto& c : nt.children()) {
        resolve_name_tree(im, idx, owner, c);
        iqb.add(c);
    }

    const auto iq(iqb.build());
    nt.identifiable(iq.first);
    nt.qualified(iq.second);
}

void resolver::resolve_attribute(const intermediate_model& im,
    const indices& idx, const name& owner, attribute& attr) const {
    try {
        resolve_name_tree(im, idx, owner, attr.parsed_type());

        /*
         * We must rely on simple names as attribute expansion has not
         * yet been performed.
         */
        BOOST_LOG_SEV(lg, debug) << "Resolved attribute: "
                                 << attr.name().simple();
    } catch (boost::exception& e) {
        std::ostringstream s;
        s << "Owner type name: " << owner.id()
          << " Attribute name: " << attr.name()
          << " Attribute type: " << attr.parsed_type();
        e << errmsg_info(s.str());
        throw;
    }
}

void resolver::resolve_attributes(const intermediate_model& im,
    const indices& idx, const name& owner,
    std::list<attribute>& attributes) const {
    for (auto& attr : attributes)
        resolve_attribute(im, idx, owner, attr);
}

void resolver::validate_inheritance_graph(const intermediate_model& im,
    const object& o) const {

    /*
     * Ensure that all parents and original parents exist as objects.
     */
    const auto id(o.name().id());
    for (const auto& pn : o.parents()) {
        if (is_object(im, pn))
            continue;

        std::ostringstream s;
        s << orphan_object << ": " << id << ". Parent: " << pn.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(resolution_error(s.str()));
    }

    for (const auto& rp : o.root_parents()) {
        if (is_object(im, rp))
            continue;

        std::ostringstream s;
        s << orphan_object << ": " << id << ". Root parent: " << rp.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(resolution_error(s.str()));
    }
}

void resolver::validate_refinements(const intermediate_model& im,
    const concept& c) const {

    /*
     * Ensure that all refined concepts exist as concepts.
     */
    const auto id(c.name().id());
    for (const auto& n : c.refines()) {
        if (is_concept(im, n))
            continue;

        std::ostringstream stream;
        stream << orphan_concept << ". Concept: " << id
               << ". Refined concept: " << n.id();

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
    }
}

void resolver::
resolve_concepts(const indices& idx, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving concepts. Size: "
                             << im.concepts().size();

    for (auto& pair : im.concepts()) {
        concept& c(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving concept: " << c.name().id();
        resolve_attributes(im, idx, c.name(), c.local_attributes());
        validate_refinements(im, c);
        BOOST_LOG_SEV(lg, debug) << "Resolved concept.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved concepts.";
}

void resolver::
resolve_objects(const indices& idx, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving objects. Size: "
                             << im.objects().size();

    for (auto& pair : im.objects()) {
        auto& o(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving object: " << o.name().id();
        validate_inheritance_graph(im, o);
        resolve_attributes(im, idx, o.name(), o.local_attributes());
        BOOST_LOG_SEV(lg, debug) << "Resolved object.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved objects.";
}

void resolver::resolve_enumerations(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving enumerations. Size: "
                             << im.enumerations().size();

    for (auto& pair : im.enumerations()) {
        auto& e(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving enumeration: " << e.name().id();

        /*
         * If we're not relying on the underlying element, we don't
         * need to worry about resolving it.
         */
        if (e.use_implementation_defined_underlying_element())
            continue;

        const auto ue(e.underlying_element());
        const auto id(ue.id());
        BOOST_LOG_SEV(lg, debug) << "Underlying element: '" << id << "'";

        if (!is_builtin(im, ue)) {
            BOOST_LOG_SEV(lg, error) << invalid_underlying_element << id;
            BOOST_THROW_EXCEPTION(
                resolution_error(invalid_underlying_element + id));
        }
        BOOST_LOG_SEV(lg, debug) << "Resolved enumeration.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved enumerations.";
}

void resolver::
resolve_primitives(const indices& idx, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving primitives. Size: "
                             << im.primitives().size();

    for (auto& pair : im.primitives()) {
        auto& p(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving primitive: " << p.name().id();
        resolve_attribute(im, idx, p.name(), p.value_attribute());
        BOOST_LOG_SEV(lg, debug) << "Resolved primitive.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved primitives.";
}

void resolver::resolve(const indices& idx, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving model: " << im.name().id();

    resolve_concepts(idx, im);
    resolve_objects(idx, im);
    resolve_enumerations(im);
    resolve_primitives(idx, im);

    BOOST_LOG_SEV(lg, debug) << "Resolved model.";
}

name resolver::resolve(const intermediate_model& im, const indices& idx,
    const name& context, const name& n) const {

    const auto r(resolve_name(im, idx, context, n));
    BOOST_LOG_SEV(lg, debug) << "Resolved name: " << n.id()
                             << " to: " << r.id();
    return r;
}

boost::optional<name> resolver::try_resolve_concept_name(const std::string& s,
    const intermediate_model& im) const {
    /*
     * Compute a tentative yarn name based on the model.
     */
    name_factory nf;
    const auto n(nf.build_element_in_model(im.name(), s));
    BOOST_LOG_SEV(lg, debug) << "Tentative concept name: " << n;

    /*
     * If we can locate a concept with that name, the stereotype is
     * deemed to be referring to it.
     */
    const auto i(im.concepts().find(n.id()));
    if (i != im.concepts().end()) {
        BOOST_LOG_SEV(lg, debug) << "Found concept with tentative name.";
        return i->second.name();
    }

    /*
     * Lets try using the references instead.
     */
    for (const auto& pair : im.references()) {
        const auto& ref(pair.first);
        const auto n(nf.build_element_in_model(ref, s));
        BOOST_LOG_SEV(lg, debug) << "Tentative concept name: " << n;

        const auto i(im.concepts().find(n.id()));
        if (i != im.concepts().end()) {
            BOOST_LOG_SEV(lg, debug) << "Found concept with tentative name.";
            return i->second.name();
        }
    }

    /*
     * There are no concepts in this model which match the stereotype name.
     */
    BOOST_LOG_SEV(lg, debug) << "Could not find a concept with tentative name.";
    return boost::optional<name>();
}

} }
