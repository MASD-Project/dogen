using System;
using NUnit.Framework;

namespace Dogen.TestModels.CSharpModel.Tests
{
    [TestFixture]
    class TypesTests
    {
        [Test]
        public void CreatingTypesSucceeds()
        {
            var seq = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator();
            var t = seq.Current;

            // var baseDir = PathUtils.ResolveRelative("TestData/TestCases/ExtendedDataStore");
            // var store = new ExtendedDataStore(new FileBasedDataStore(baseDir));
            // Assert.That(store.Contains("afile.xml"), Is.True);
            // Assert.That(store.Contains("nonexistent"), Is.False);
            // string content = store.GetContent("afile.xml");
            // Assert.That(content, Is.EqualTo("<root/>"));
        }
    }
}
