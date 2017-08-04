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
#include <list>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/origin_types.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/upsilon/types/type_visitor.hpp"
#include "dogen/upsilon/io/target_types_io.hpp"
#include "dogen/upsilon/io/name_io.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"
#include "dogen/yarn.upsilon/types/workflow_error.hpp"
#include "dogen/yarn.upsilon/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.upsilon.workflow"));

const std::string incorrect_number_of_outputs(
    "Upsilon moodel does not have expected number of outputs (1): ");
const std::string unspported_target("Target is not supported: ");
const std::string duplicate_id("Duplicate id: ");
const std::string duplicate_schema_name("Duplicate schema name: ");

}

namespace dogen {
namespace yarn {
namespace upsilon {

class collection_accumulator : public dogen::upsilon::type_visitor {
public:
    using dogen::upsilon::type_visitor::visit;
    void visit(const dogen::upsilon::collection& c);

public:
    const std::unordered_map<std::string, dogen::upsilon::name>& result() const;

private:
    std::unordered_map<std::string, dogen::upsilon::name> result_;
};

void collection_accumulator::visit(const dogen::upsilon::collection& c) {
    const auto id(c.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing: " << id;

    const auto pair(std::make_pair(id, c.type_name()));
    const auto inserted(result_.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_id + id));
    }
}

const std::unordered_map<std::string, dogen::upsilon::name>&
collection_accumulator::result() const {
    return result_;
}

class model_populator : public dogen::upsilon::type_visitor {
public:
    model_populator(
        const std::unordered_map<std::string, yarn::meta_model::name>&
        schema_name_to_model_name,
        const std::unordered_map<std::string, dogen::upsilon::name>&
        collection_names, yarn::meta_model::intermediate_model& im);

private:
    template<typename Nameable>
    void insert(const boost::shared_ptr<Nameable>& nbl,
        std::unordered_map<std::string,
        boost::shared_ptr<Nameable>>& target) const {
        const auto id(nbl->name().id());
        const auto pair(std::make_pair(id, nbl));
        const auto inserted(target.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_id << id;
            BOOST_THROW_EXCEPTION(workflow_error(duplicate_id + id));
        }
    }

public:
    using dogen::upsilon::type_visitor::visit;
    void visit(const dogen::upsilon::compound& c);
    void visit(const dogen::upsilon::enumeration& e);
    void visit(const dogen::upsilon::primitive& p);

private:
    yarn::meta_model::intermediate_model& model_;
    const transformer transformer_;
};

model_populator::
model_populator(const std::unordered_map<std::string, yarn::meta_model::name>&
    schema_name_to_model_name,
    const std::unordered_map<std::string, dogen::upsilon::name>&
    collection_names, yarn::meta_model::intermediate_model& im)
    : model_(im),
      transformer_(im.name(), schema_name_to_model_name, collection_names) {}

void model_populator::visit(const dogen::upsilon::compound& c) {
    const auto o(transformer_.to_object(c));
    insert(o, model_.objects());
}

void model_populator::visit(const dogen::upsilon::enumeration& e) {
    const auto ye(transformer_.to_enumeration(e));
    insert(ye, model_.enumerations());
}

void model_populator::visit(const dogen::upsilon::primitive& p) {
    const auto b(transformer_.to_builtin(p));
    insert(b, model_.builtins());
}

std::list<yarn::meta_model::languages> workflow::obtain_output_languages(
    const std::vector<dogen::upsilon::output>& outputs) const {
    std::list<yarn::meta_model::languages> r;
    using dogen::upsilon::target_types;
    for (const auto& o : outputs) {
        for (const auto& rep : o.representations()) {
            if (rep.target() == target_types::cpp)
                r.push_back(yarn::meta_model::languages::cpp);
            else if (rep.target() == target_types::cs)
                r.push_back(meta_model::languages::csharp);
            else if (rep.target() == target_types::java) {
                // FIXME: skip java for now as we do not have a model
                // FIXME: or mappings for it.
                // r.push_back(languages::java);
            }
            else {
                const auto tg(boost::lexical_cast<std::string>(rep.target()));
                BOOST_LOG_SEV(lg, error) << unspported_target << tg;
                BOOST_THROW_EXCEPTION(workflow_error(unspported_target + tg));
            }
        }
    }

    return r;
}

std::unordered_map<std::string, dogen::upsilon::name> workflow::
obtain_collection_names(const dogen::upsilon::model& um) const {
    BOOST_LOG_SEV(lg, debug) << "Started accumulating collection names.";

    collection_accumulator ca;
    for (const auto& pair : um.schemas()) {
        const auto& schema(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Processing Schema: "
                                 << schema.file_name().generic_string();

        const auto& types(schema.types());
        for (const auto& ptr : types) {
            const auto& t(*ptr);
            t.accept(ca);
        }

        BOOST_LOG_SEV(lg, debug) << "Finished processing Schema.";
    }
    BOOST_LOG_SEV(lg, debug) << "Finished accumulating collection names."
                             << " Result: " << ca.result();
    return ca.result();
}

std::unordered_map<std::string, yarn::meta_model::name>
workflow::map_schema_name_to_model_name(const dogen::upsilon::model& um) const {
    std::unordered_map<std::string, yarn::meta_model::name> r;

    yarn::helpers::name_factory nf;
    for (const auto& pair : um.schemas()) {
        const auto& schema(pair.second);
        const auto sn(schema.name());
        const auto n(nf.build_model_name(sn));
        const auto inserted(r.insert(std::make_pair(sn, n)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_schema_name << sn;
            BOOST_THROW_EXCEPTION(workflow_error(duplicate_schema_name + sn));
        }
    }

    return r;
}

yarn::meta_model::intermediate_model
workflow::create_model(const dogen::upsilon::model& um) const {
    if (um.config().outputs().size() != 1) {
        const auto gs(um.config().file_name().generic_string());
        BOOST_LOG_SEV(lg, error) << incorrect_number_of_outputs << gs;
        BOOST_THROW_EXCEPTION(workflow_error(incorrect_number_of_outputs + gs));
    }

    yarn::meta_model::intermediate_model r;
    r.input_language(yarn::meta_model::languages::upsilon);

    const auto& outputs(um.config().outputs());
    const auto& output(outputs[0]);

    yarn::helpers::name_factory nf;
    const auto n(nf.build_model_name(output.schema_name()));
    r.name(n);
    r.origin_type(yarn::meta_model::origin_types::target);
    r.output_languages(obtain_output_languages(outputs));

    auto root_module(boost::make_shared<yarn::meta_model::module>());
    root_module->name(n);
    root_module->origin_type(yarn::meta_model::origin_types::target);
    r.modules()[n.id()] = root_module;

    return r;
}

void workflow::populate_model(const dogen::upsilon::model& um,
    const std::unordered_map<std::string, yarn::meta_model::name>&
    schema_name_to_model_name,
    const std::unordered_map<std::string, dogen::upsilon::name>&
    collection_names, yarn::meta_model::intermediate_model& im) const {

    model_populator mp(schema_name_to_model_name, collection_names, im);
    for (const auto& pair : um.schemas()) {
        const auto& schema(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Populating from Schema: "
                                 << schema.file_name().generic_string();

        const auto& types(schema.types());
        for (const auto& ptr : types) {
            const auto& t(*ptr);
            t.accept(mp);
        }

        BOOST_LOG_SEV(lg, debug) << "Finished populating from Schema.";
    }
}

yarn::meta_model::intermediate_model
workflow::execute(const dogen::upsilon::model& um) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow on upsilon model. Config: "
                             << um.config().file_name().generic_string();

    const auto cn(obtain_collection_names(um));
    const auto snmn(map_schema_name_to_model_name(um));
    auto r(create_model(um));
    populate_model(um, snmn, cn, r);

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow on upsilon model.";
    return r;
}

} } }
