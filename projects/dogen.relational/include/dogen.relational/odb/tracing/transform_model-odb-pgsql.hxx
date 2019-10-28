// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_MODEL_ODB_PGSQL_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_MODEL_ODB_PGSQL_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2046500 // 2.5.0-b.15
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/pgsql/gregorian-traits.hxx>
#include <odb/boost/date-time/pgsql/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/pgsql/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20465UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen.relational/types/tracing/transform_model.hpp"

#include "dogen.relational/odb/tracing/model_id-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/transform_id-odb-pgsql.hxx"

#include "dogen.relational/odb/tracing/transform_model-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // transform_model
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >
  {
    // transform_id
    //
    struct transform_id_class_
    {
      transform_id_class_ ()
      {
      }

      // value
      //
      typedef
      pgsql::query_column<
        pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::query_type,
        pgsql::id_string >
      value_type_;

      static const value_type_ value;
    };

    static const transform_id_class_ transform_id;

    // model_id
    //
    struct model_id_class_
    {
      model_id_class_ ()
      {
      }

      // value
      //
      typedef
      pgsql::query_column<
        pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::query_type,
        pgsql::id_string >
      value_type_;

      static const value_type_ value;
    };

    static const model_id_class_ model_id;

    // type
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::dogen::relational::tracing::io_type,
        pgsql::id_integer >::query_type,
      pgsql::id_integer >
    type_type_;

    static const type_type_ type;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::transform_id_class_::value_type_
  query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::transform_id_class_::
  value (A::table_name, "\"TRANSFORM_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::transform_id_class_
  query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::transform_id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::model_id_class_::value_type_
  query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::model_id_class_::
  value (A::table_name, "\"MODEL_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::model_id_class_
  query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::model_id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::type_type_
  query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >::
  type (A::table_name, "\"TYPE\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >:
    query_columns< ::dogen::relational::tracing::transform_model, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::transform_model, id_pgsql >:
    public access::object_traits< ::dogen::relational::tracing::transform_model >
  {
    public:
    struct image_type
    {
      // transform_id_
      //
      composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::image_type transform_id_value;

      // model_id_
      //
      composite_value_traits< ::dogen::relational::tracing::model_id, id_pgsql >::image_type model_id_value;

      // type_
      //
      int type_value;
      bool type_null;

      std::size_t version;
    };

    using object_traits<object_type>::id;

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (pgsql::bind*,
          image_type&,
          pgsql::statement_kind);

    static bool
    init (image_type&,
          const object_type&,
          pgsql::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef pgsql::no_id_object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 3UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static const char persist_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];

    public:
  };

  // transform_model
  //
}

#include "dogen.relational/odb/tracing/transform_model-odb-pgsql.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_MODEL_ODB_PGSQL_HXX
