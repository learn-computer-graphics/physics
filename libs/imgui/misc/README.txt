
misc/cpp/
  InputText() wrappers for C++ standard library (STL) type: std::string.
  This is also an example of how you may wrap your own similar types.

misc/debuggers/
  Helper files for popular debuggers.
  With the .natvis file, types like ImVector<> will be displayed nicely in Visual Studio debugger.

misc/fonts/
  Fonts loading/merging instructions (e.g. How to handle glyph ranges, how to merge icons fonts).
  Command line tool "binary_to_compressed_c" to create compressed arrays to embed data in source code.
  Suggested fonts and links.

misc/freetype/
  Font atlas builder/rasterizer using FreeType instead of stb_truetype.
  Benefit from better FreeType rasterization, in particular for small fonts.
