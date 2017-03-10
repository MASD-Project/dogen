using System;

namespace dogen.test_models.lam_model.package1
{
    /// <summary>
    /// Generates sequences of class_in_package.
    /// </summary>
    public static class class_in_packageDumper
    {
        static internal void Dump(AssistantDumper assistant, class_in_package value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("dogen.test_models.lam_model.package1.class_in_package", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.Add("prop_0", value.prop_0);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(class_in_package value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}
