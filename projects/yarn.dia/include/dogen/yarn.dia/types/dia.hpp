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
#ifndef DOGEN_YARN_DIA_TYPES_DIA_HPP
#define DOGEN_YARN_DIA_TYPES_DIA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace yarn {

/**
 * @brief Yarn Dia is a unidirectional transformation model that transforms a
 * Dia @e diagram into an yarn @e model.
 *
 * By that we mean that it is a model designed to transform a representation of
 * a user model in Dia diagram format to its counterpart in yarn format, taking
 * into account any special yarn meta-data which the user may have encoded into
 * the Dia diagram. Note that the Dia diagram format contains a representation
 * of UML.
 *
 * @section yarn_dia_0 Dia diagrams as DAGs
 *
 * Dia diagrams are made up of @e objects, identified by IDs. These objects
 * contain a number of UML model elements, which we are interested in. For
 * instance:
 *
 * @li UML class
 * @li UML generalisation
 * @li UML notes
 *
 * and so on. Each of these objects will contribute to a yarn object; but note
 * that the mapping is not one-to-one.For example, in order to process an
 * yarn object, one needs to have both the UML class as well as any
 * generalisations it may be involved in (both as a child or as a parent). To
 * make our life easier we created a DAG of Dia objects that provides us with
 * the information in dependency order. That is, we process dia objects in
 * such a way that when a dependency exists, we know that the object in which
 * we depend on has already been processed. Please note that to ensure no
 * cycles we had to ignore some of the UML objects such as UML aggregation -
 * but fortunately, these objects do not provide sufficient information for
 * an yarn transformation anyway so not much was lost (instead, one must
 * manually declare attributes in a class).
 *
 * See @ref grapher for details on how the the DAG is built.
 *
 * @section yarn_dia_1 Intermediate processing
 *
 * To make the code easier to read and maintain, we created a numeber of
 * intermediate stages between a Dia diagram and yarn:
 *
 * @li Dia object -> processed object -> profile -> Yarn
 *
 * This may look a bit excessive at first glance, but it was done because
 * the shape of the Dia objects is a bit too generic for our purposes, and
 * the resulting processing code was full of loops and look-ups. Instead,
 * we make the generic Dia object into a very concrete processed object -
 * still preserving most of the semantics of Dia - and then from those we
 * build a profile. A profile allows us to quickly scan for UML and yarn
 * type information without getting lost in the intricacies of the generic
 * Dia structure. With these in hand, the @ref transformer is able to
 * create the corresponding yarn entity, and the transformation code is
 * not obscured.
 *
 * @section yarn_dia_2 Dia meta-data
 *
 * There are a couple of conventions on how to model in Dia that one
 * needs to follow in order to comply with Dogen:
 *
 * @li any public attribute in a class is automatically converted into a
 * yarn property rather than a member variable. This means that it is
 * expected that a getter and a setter will be generated.
 *
 * @li a number of DDD stereotypes were added:@e service, @e value and @e
 * object. These all map directly to the DDD ideas defined by Eric Evans
 * in the Domain Driven Design book.
 *
 * @li a number of yarn specific stereotypes were added: @e exception,
 * @e enumeration, @e concept, @e visitable, @e fluent, @e immutable,
 * @e comparable. These we describe below.
 *
 * @li any type without any stereotype defaults to @e value @e object.
 *
 * @li any UML Note with the marker #DOGEN yarn.dia.comment=true will be
 * used as the documentation of the current package - or the model, if
 * place at the top-level. Only one such note is expected per containing
 * entity.
 *
 * The yarn stereotypes have the following behaviours:
 *
 * @li @b exception: an exception class will be code generated. This is still
 * a value object but it will have any additional machinery related to
 * exceptions attached to it.
 *
 * @li @b enumeration: Can only have attributes, and the attributes must not
 * have types. Type defaults to unsigned int.
 *
 * @li @b concept: Very similar to a C++ concept. Defines new stereotypes on
 * the fly; that is, if you create a UML class @e MyConcept with property
 * @e a and mark it as a concept, you can then create a UML class @e my_class
 * with a stereotype of @e MyConcept; the result will be that my_class will
 * have a property @@e a too.
 *
 * @li @b visitable: a visitor service will be create for the type. Must be
 * the root of an inheritance tree.
 *
 * @li @b fluent: a fluent interface will be generated for all properties.
 *
 * @li @b immutable: only getters will be generated for each property.
 *
 * @li @b comparable: unused as of yet.
 */
namespace dia {
}

} }

#endif
