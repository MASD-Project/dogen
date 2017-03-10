using System;

namespace dogen.test_models.lam_model
{
    /// <summary>
    /// Generates sequences of builtins.
    /// </summary>
    public static class builtinsDumper
    {
        static internal void Dump(AssistantDumper assistant, builtins value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("dogen.test_models.lam_model.builtins", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.Add("prop_0", value.prop_0, true/*withSeparator*/);
            assistant.Add("prop_1", value.prop_1, true/*withSeparator*/);
            assistant.Add("prop_2", value.prop_2, true/*withSeparator*/);
            assistant.Add("prop_3", value.prop_3, true/*withSeparator*/);
            assistant.Add("prop_4", value.prop_4, true/*withSeparator*/);
            assistant.Add("prop_5", value.prop_5, true/*withSeparator*/);
            assistant.Add("prop_6", value.prop_6, true/*withSeparator*/);
            assistant.Add("prop_7", value.prop_7, true/*withSeparator*/);
            assistant.Add("prop_8", value.prop_8, true/*withSeparator*/);
            assistant.Add("prop_9", value.prop_9);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(builtins value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}
