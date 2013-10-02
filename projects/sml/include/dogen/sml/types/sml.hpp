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
#ifndef DOGEN_SML_TYPES_SML_HPP
#define DOGEN_SML_TYPES_SML_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {

/**
 * @brief SML is the Simplified Modeling Language.
 *
 * @section sml_0 Core Ideas
 *
 * SML has at its core the ideas explained by Eric Evans in Domain Driven
 * Design (DDD), and it is mainly a domain model to model the DDD domian.
 * However, it also contains some influences from Java's EMF - more precisely
 * eCore, which was the first meta-model we looked at. eCore is itself rooted
 * in UML. We also took some ideas from Stepanov and Jones, in Programming
 * Elements (those which we could just about understand).
 *
 * In more general terms, SML is a meta-model - that is a model that models
 * models - but we are not too hang-up on the classic terminology of meta-modeling
 * because a lot of people find it confusing. Instead, we chose to use the
 * @e ubiquitous @e language defined in th DDD book because its very clear, but
 * avoids the complexity of the terms usually associated with meta-modeling.
 *
 * The objective of SML is to provide the required scaffoling to represent domain
 * models, and to do so in a way that is programming language neutral. Thus is
 * should provide a representation that is suitable for further transformations
 * into models representing programing languages, and from there, to code
 * generation.
 *
 * At the root of SML is the @ref model, short for domain model. It is the root
 * of an aggregate containing a number of @e modeling @elements which together
 * make up the software representation of a given domain model. The key types of
 * modeling elements in SML are:
 *
 * @li @b model: the model itself, modeling domain models
 * @li @b modules: packaging unit; logical sub-division of the model.
 * @li @b concepts: not present in DDD; models the C++ notion of a concept.
 * @li @b enumeration: value type that models enumerations
 * @li @b primitive: value type that models primitive types such as int, etc.
 * @li @b object: models the notion of an @e object as defined in object oriented
 * languages.
 *
 * The remaining ideas are refinements of these core concepts.
 *
 * @section sml_1 Merging and Resolving
 *
 * SML models are expected to begin their life as disjointed models with lots of
 * missing @e references to types. This expectation arises from the fact that we
 * have most likely transformed some kind of external model into SML - a dia diagram,
 * say - and that the tools used for working on that model are not aware of SML or
 * its dependencies.
 *
 * Thus, in order to become useful, an SML model needs to be merged with all of its
 * dependencies. This is done by providing the @e target model - i.e. that which one
 * intends to really work on - and its @e references - i.e. any models which are
 * picked up due to being referenced from within the tatget model - and pass them
 * over to the @ref merger. It is the merger's job to create a @e merged model.
 *
 * A further step is still required, which is to @e resolve all of the references,
 * to ensure we do not have any missing dependencies. This is the job of the
 * @ref resolver.
 *
 * All of these steps are encompassed in the SML @ref workflow.
 *
 */
namespace sml {
} }

#endif
