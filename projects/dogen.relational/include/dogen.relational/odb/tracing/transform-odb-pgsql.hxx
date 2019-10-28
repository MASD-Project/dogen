// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_ODB_PGSQL_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_ODB_PGSQL_HXX

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

#include "dogen.relational/types/tracing/transform.hpp"

#include "dogen.relational/odb/tracing/run_id-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/transform_id-odb-pgsql.hxx"

#include "dogen.relational/odb/tracing/transform-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // transform
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >
  {
    // start
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::boost::posix_time::ptime,
        pgsql::id_timestamp >::query_type,
      pgsql::id_timestamp >
    start_type_;

    static const start_type_ start;

    // end
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::boost::posix_time::ptime,
        pgsql::id_timestamp >::query_type,
      pgsql::id_timestamp >
    end_type_;

    static const end_type_ end;

    // id
    //
    struct id_class_
    {
      id_class_ ()
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

    static const id_class_ id;

    // name
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::std::string,
        pgsql::id_string >::query_type,
      pgsql::id_string >
    name_type_;

    static const name_type_ name;

    // description
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::std::string,
        pgsql::id_string >::query_type,
      pgsql::id_string >
    description_type_;

    static const description_type_ description;

    // run_id
    //
    struct run_id_class_
    {
      run_id_class_ ()
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

    static const run_id_class_ run_id;

    // type
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::dogen::relational::tracing::transform_type,
        pgsql::id_integer >::query_type,
      pgsql::id_integer >
    type_type_;

    static const type_type_ type;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::start_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::
  start (A::table_name, "\"START\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::end_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::
  end (A::table_name, "\"END\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::id_class_::value_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::id_class_::
  value (A::table_name, "\"ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::id_class_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::name_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::
  name (A::table_name, "\"NAME\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::description_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::
  description (A::table_name, "\"DESCRIPTION\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::run_id_class_::value_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::run_id_class_::
  value (A::table_name, "\"RUN_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::run_id_class_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::run_id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::type_type_
  query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >::
  type (A::table_name, "\"TYPE\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >:
    query_columns< ::dogen::relational::tracing::transform, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::transform, id_pgsql >:
    public access::object_traits< ::dogen::relational::tracing::transform >
  {
    public:
    struct image_type
    {
      // start_
      //
      long long start_value;
      bool start_null;

      // end_
      //
      long long end_value;
      bool end_null;

      // id_
      //
      composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::image_type id_value;

      // name_
      //
      details::buffer name_value;
      std::size_t name_size;
      bool name_null;

      // description_
      //
      details::buffer description_value;
      std::size_t description_size;
      bool description_null;

      // run_id_
      //
      composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::image_type run_id_value;

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

    static const std::size_t column_count = 7UL;
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

  // transform
  //
}

#include "dogen.relational/odb/tracing/transform-odb-pgsql.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_ODB_PGSQL_HXX
