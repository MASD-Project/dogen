import seaborn as sns

palette = sns.light_palette("#F0E68C", 2)
print("note_palette = ", palette.as_hex())

palette = sns.light_palette("gray", 20)
print("package_palette = ", palette.as_hex()[:10])

palette = sns.light_palette("#5768FF", 10)
print("manually_gen_palette = ", palette.as_hex()[:10])

palette = sns.light_palette("#FBA5A5", 1)
print("testing_palette = ", palette.as_hex())

palette = sns.light_palette("#00ff7f", 10)
print("orm_palette = ", palette.as_hex())

palette = sns.light_palette("#A0522D", 6)
print("decoration_palette = ", palette.as_hex())

palette = sns.light_palette("#529999", 10)
print("variability_palette = ", palette.as_hex())

palette = sns.light_palette("#FFFF00", 5)
print("mapping_palette = ", palette.as_hex())

palette = sns.light_palette("#ff8c00", 3)
print("templating_palette = ", palette.as_hex())

palette = sns.light_palette("#00FF00", 2)
print("serialization_palette = ", palette.as_hex())

palette = sns.light_palette("#006400", 10)
print("visual_studio_palette = ", palette.as_hex())

palette = sns.light_palette("#9400d3", 20)
print("core_palette = ", palette.as_hex())

palette = sns.light_palette("#43cd80", 10)
print("physical_palette = ", palette.as_hex())
