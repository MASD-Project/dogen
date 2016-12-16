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

namespace Dogen.TestModels.CSharpModel.Tests
{
    [TestFixture]
    class equality_tests
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(equality_tests));
        private static readonly string FixtureName = typeof(equality_tests).Name;

        [Test]
        // Analysis disable once InconsistentNaming
        public void identical_objects_are_equal()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var a = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                var b = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("a: {0}", ComplexBuiltinsDumper.Dump(a));
                Log.DebugFormat("b: {0}", ComplexBuiltinsDumper.Dump(b));

                Assert.That(object.ReferenceEquals(a, b), Is.False);
                Assert.That(object.Equals(a, b), Is.True);

                var c = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                var d = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("c: {0}", PrimitiveBuiltinsDumper.Dump(c));
                Log.DebugFormat("d: {0}", PrimitiveBuiltinsDumper.Dump(d));

                Assert.That(object.ReferenceEquals(c, d), Is.False);
                Assert.That(object.Equals(c, d), Is.True);

                var e = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                var f = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("e: {0}", NoPropertiesDumper.Dump(e));
                Log.DebugFormat("f: {0}", NoPropertiesDumper.Dump(f));

                Assert.That(object.ReferenceEquals(e, f), Is.False);
                Assert.That(object.Equals(e, f), Is.True);

                var g = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                var h = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("g: {0}", OnePropertyDumper.Dump(g));
                Log.DebugFormat("h: {0}", OnePropertyDumper.Dump(h));

                Assert.That(object.ReferenceEquals(g, h), Is.False);
                Assert.That(object.Equals(g, h), Is.True);
            }
        }

        [Test]
        public void GeneratingComplexBuiltinsResultsInExpectedDump()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var seq = ComplexBuiltinsSequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", ComplexBuiltinsDumper.Dump(c));
            }
        }

        [Test]
        public void GeneratingPrimitiveBuiltinsResultsInExpectedDump()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var seq = PrimitiveBuiltinsSequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", PrimitiveBuiltinsDumper.Dump(c));
            }
        }

        [Test]
        public void GeneratingOnePropertyResultsInExpectedDump()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var seq = OnePropertySequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", OnePropertyDumper.Dump(c));
            }
        }

        [Test]
        public void GeneratingNoPropertiesResultsInExpectedDump()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var seq = NoPropertiesSequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", NoPropertiesDumper.Dump(c));
            }
        }
    }
}
