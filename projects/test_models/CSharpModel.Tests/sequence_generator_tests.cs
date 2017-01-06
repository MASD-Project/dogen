// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using log4net;
using NUnit.Framework;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace Dogen.TestModels.CSharpModel.Tests
{
    [TestFixture]
    // Analysis disable once InconsistentNaming
    public class sequence_generator_tests
    {
        #region Properties
        private static readonly ILog Log = LogManager.GetLogger(typeof(equality_tests));
        private static readonly string FixtureName = typeof(sequence_generator_tests).Name;
        #endregion

        #region Helpers
        static bool ValidateJson(string jsonString)
        {
            Log.DebugFormat("JSON: {0}", jsonString);
            try
            {
                JToken.Parse(jsonString);
                return true;
            }
            catch (JsonReaderException ex)
            {
                Log.ErrorFormat("String is not valid JSON: {0}", ex);
                return false;
            }
        }
        #endregion

        #region Tests
        [Test]
        // Analysis disable once InconsistentNaming
        public void dumping_objects_with_properties_produces_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                /*
                 * Class without any properties.
                */
                var a = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(NoPropertiesDumper.Dump(a)), Is.True);

                /*
                 * Class with only one primitive property.
                 */
                var b = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(OnePropertyDumper.Dump(b)), Is.True);

                /*
                 * Class with multiple primitive properties.
                 */
                var c = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(PrimitiveBuiltinsDumper.Dump(c)), Is.True);

                /*
                 * Class with multiple object properties.
                 */
                var d = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(ComplexBuiltinsDumper.Dump(d)), Is.True);

                /*
                 * Class with an object property that is code generated.
                 */
                var e = AssociationSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(AssociationDumper.Dump(e)), Is.True);
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void dumping_objects_without_properties_produces_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var a = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(NoPropertiesDumper.Dump(a)), Is.True);
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void dumping_enumerations_produces_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                /*
                 * First value of the enumeration is "invalid".
                 */
                var e = BookTypesSequenceGenerator.Sequence().GetEnumerator();
                Assert.That(ValidateJson(BookTypesDumper.Dump(e.Current)), Is.True);

                /*
                 * Do second value as well.
                 */
                e.MoveNext();
                Assert.That(ValidateJson(BookTypesDumper.Dump(e.Current)), Is.True);
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void dumping_classes_in_namespaces_produces_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var a = Package1.Class1SequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Package1.Class1Dumper.Dump(a)), Is.True);

                var b = Package1.ShapeTypesSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Package1.ShapeTypesDumper.Dump(b)), Is.True);

                var c = Package1.AssociationInPackageSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Package1.AssociationInPackageDumper.Dump(c)), Is.True);
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void dumping_classes_in_inheritance_relationships_produce_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var a = Descendant1SequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Descendant1Dumper.Dump(a)), Is.True);

                var b = BaseSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(BaseDumper.Dump(b)), Is.True);

                var c = Descendant2SequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Descendant2Dumper.Dump(c)), Is.True);

                /*
                 * Classes in different namespaces.
                 */
                var d = Package2.ChildSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Package2.ChildDumper.Dump(d)), Is.True);

                var e = Package4.ChildSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Package4.ChildDumper.Dump(e)), Is.True);

                var f = Package5.ChildSequenceGenerator.Sequence().GetEnumerator().Current;
                Assert.That(ValidateJson(Package5.ChildDumper.Dump(f)), Is.True);
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void dumping_null_objects_produces_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                NoProperties a = null;
                Assert.That(ValidateJson(NoPropertiesDumper.Dump(a)), Is.True);

                var b = new ComplexBuiltins() { StringProperty = "test" };
                Assert.That(ValidateJson(ComplexBuiltinsDumper.Dump(b)), Is.True);

                var c = new ComplexBuiltins() { ObjectProperty = "test" };
                Assert.That(ValidateJson(ComplexBuiltinsDumper.Dump(c)), Is.True);
            }
        }
        #endregion
    }
}
