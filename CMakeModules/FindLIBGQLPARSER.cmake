find_path(GQLPARSER_INCLUDE_DIR graphqlparser/Ast.h PATHS /usr/local/include)
find_library (GQLPARSER_LIBRARY graphqlparser PATHS /usr/local/lib)

if (GQLPARSER_INCLUDE_DIR AND GQLPARSER_LIBRARY)
   SET (GQLPARSER_FOUND TRUE)
   MESSAGE ("GQLPARSER found.")
else (GQLPARSER_INCLUDE_DIR AND GQLPARSER_LIBRARY)
   SET (GQLPARSER_FOUND FALSE)
   MESSAGE ("GQLPARSER not found...")
endif (GQLPARSER_INCLUDE_DIR AND GQLPARSER_LIBRARY)